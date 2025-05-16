/* reg_ecm-r04-3000-0000-a-v02 */
/************************************************************************************************/
/*																								*/
/*		ECM register definition (for RH850U2A)													*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef REG_ECM_H
#define REG_ECM_H


/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	register type definition																	*/
/*==============================================================================================*/
/* ECMM&ECMC */
/* ============================================================================ */
/* ============================ Module: ECMM & ECMC =========================== */
/* ============================================================================ */
typedef	struct													/* ECMm , m=M/C */
{
	union														/* ECMmESET , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xEST					:1;						/* EST */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMESET;												/* OFFSET +0 */

	union														/* ECMmECLR , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECT					:1;						/* ECT */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMECLR;												/* OFFSET +4 */

	union														/* ECMmESET0 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xEST					:1;						/* EST */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMESET0;												/* OFFSET +8 */

	union														/* ECMmECLR0 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECT					:1;						/* ECT */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMECLR0;												/* OFFSET +C */

	union														/* ECMmESET1 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xEST					:1;						/* EST */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMESET1;												/* OFFSET +10 */

	union														/* ECMmECLR1 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECT					:1;						/* ECT */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMECLR1;												/* OFFSET +14 */

	union														/* ECMmESET2 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xEST					:1;						/* EST */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMESET2;												/* OFFSET +18 */

	union														/* ECMmECLR2 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECT					:1;						/* ECT */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMECLR2;												/* OFFSET +1C */

	union														/* ECMmESET3 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xEST					:1;						/* EST */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMESET3;												/* OFFSET +20 */

	union														/* ECMmECLR3 , m=M/C */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECT					:1;						/* ECT */
			U4	b31Dummy1				:31;
		} stBit;
	} unECMECLR3;												/* OFFSET +24 */

	U1	u1Dummy1[32];	/* 0xFFD39028 - 0xFFD39047 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMmESSTR0 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE000					:1;				/* ECMmSSE000 */
					U4	xSSE001					:1;				/* ECMmSSE001 */
					U4	xSSE002					:1;				/* ECMmSSE002 */
					U4	xSSE003					:1;				/* ECMmSSE003 */
					U4	xSSE004					:1;				/* ECMmSSE004 */
					U4	xSSE005					:1;				/* ECMmSSE005 */
					U4	xSSE006					:1;				/* ECMmSSE006 */
					U4	xSSE007					:1;				/* ECMmSSE007 */
					U4	xSSE008					:1;				/* ECMmSSE008 */
					U4	xSSE009					:1;				/* ECMmSSE009 */
					U4	xSSE010					:1;				/* ECMmSSE010 */
					U4	xSSE011					:1;				/* ECMmSSE011 */
					U4	xSSE012					:1;				/* ECMmSSE012 */
					U4	xSSE013					:1;				/* ECMmSSE013 */
					U4	xSSE014					:1;				/* ECMmSSE014 */
					U4	xSSE015					:1;				/* ECMmSSE015 */
					U4	xSSE016					:1;				/* ECMmSSE016 */
					U4	xSSE017					:1;				/* ECMmSSE017 */
					U4	xSSE018					:1;				/* ECMmSSE018 */
					U4	xSSE019					:1;				/* ECMmSSE019 */
					U4	xSSE020					:1;				/* ECMmSSE020 */
					U4	xSSE021					:1;				/* ECMmSSE021 */
					U4	xSSE022					:1;				/* ECMmSSE022 */
					U4	xSSE023					:1;				/* ECMmSSE023 */
					U4	xSSE024					:1;				/* ECMmSSE024 */
					U4	xSSE025					:1;				/* ECMmSSE025 */
					U4	xSSE026					:1;				/* ECMmSSE026 */
					U4	xSSE027					:1;				/* ECMmSSE027 */
					U4	xSSE028					:1;				/* ECMmSSE028 */
					U4	xSSE029					:1;				/* ECMmSSE029 */
					U4	xSSE030					:1;				/* ECMmSSE030 */
					U4	xSSE031					:1;				/* ECMmSSE031 */
				} stBit;
			} unECMESSTR0;										/* OFFSET +48 */

			union												/* ECMmESSTR1 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE032					:1;				/* ECMmSSE032 */
					U4	xSSE033					:1;				/* ECMmSSE033 */
					U4	xSSE034					:1;				/* ECMmSSE034 */
					U4	xSSE035					:1;				/* ECMmSSE035 */
					U4	xSSE036					:1;				/* ECMmSSE036 */
					U4	xSSE037					:1;				/* ECMmSSE037 */
					U4	xSSE038					:1;				/* ECMmSSE038 */
					U4	xSSE039					:1;				/* ECMmSSE039 */
					U4	xSSE040					:1;				/* ECMmSSE040 */
					U4	xSSE041					:1;				/* ECMmSSE041 */
					U4	xSSE042					:1;				/* ECMmSSE042 */
					U4	xSSE043					:1;				/* ECMmSSE043 */
					U4	xSSE044					:1;				/* ECMmSSE044 */
					U4	xSSE045					:1;				/* ECMmSSE045 */
					U4	xSSE046					:1;				/* ECMmSSE046 */
					U4	xSSE047					:1;				/* ECMmSSE047 */
					U4	xSSE048					:1;				/* ECMmSSE048 */
					U4	xSSE049					:1;				/* ECMmSSE049 */
					U4	xSSE050					:1;				/* ECMmSSE050 */
					U4	xSSE051					:1;				/* ECMmSSE051 */
					U4	xSSE052					:1;				/* ECMmSSE052 */
					U4	xSSE053					:1;				/* ECMmSSE053 */
					U4	xSSE054					:1;				/* ECMmSSE054 */
					U4	xSSE055					:1;				/* ECMmSSE055 */
					U4	xSSE056					:1;				/* ECMmSSE056 */
					U4	xSSE057					:1;				/* ECMmSSE057 */
					U4	xSSE058					:1;				/* ECMmSSE058 */
					U4	xSSE059					:1;				/* ECMmSSE059 */
					U4	xSSE060					:1;				/* ECMmSSE060 */
					U4	xSSE061					:1;				/* ECMmSSE061 */
					U4	xSSE062					:1;				/* ECMmSSE062 */
					U4	xSSE063					:1;				/* ECMmSSE063 */
				} stBit;
			} unECMESSTR1;										/* OFFSET +4C */

			union												/* ECMmESSTR2 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE064					:1;				/* ECMmSSE064 */
					U4	xSSE065					:1;				/* ECMmSSE065 */
					U4	xSSE066					:1;				/* ECMmSSE066 */
					U4	xSSE067					:1;				/* ECMmSSE067 */
					U4	xSSE068					:1;				/* ECMmSSE068 */
					U4	xSSE069					:1;				/* ECMmSSE069 */
					U4	xSSE070					:1;				/* ECMmSSE070 */
					U4	xSSE071					:1;				/* ECMmSSE071 */
					U4	xSSE072					:1;				/* ECMmSSE072 */
					U4	xSSE073					:1;				/* ECMmSSE073 */
					U4	xSSE074					:1;				/* ECMmSSE074 */
					U4	xSSE075					:1;				/* ECMmSSE075 */
					U4	xSSE076					:1;				/* ECMmSSE076 */
					U4	xSSE077					:1;				/* ECMmSSE077 */
					U4	xSSE078					:1;				/* ECMmSSE078 */
					U4	xSSE079					:1;				/* ECMmSSE079 */
					U4	xSSE080					:1;				/* ECMmSSE080 */
					U4	xSSE081					:1;				/* ECMmSSE081 */
					U4	xSSE082					:1;				/* ECMmSSE082 */
					U4	xSSE083					:1;				/* ECMmSSE083 */
					U4	xSSE084					:1;				/* ECMmSSE084 */
					U4	xSSE085					:1;				/* ECMmSSE085 */
					U4	xSSE086					:1;				/* ECMmSSE086 */
					U4	xSSE087					:1;				/* ECMmSSE087 */
					U4	xSSE088					:1;				/* ECMmSSE088 */
					U4	xSSE089					:1;				/* ECMmSSE089 */
					U4	xSSE090					:1;				/* ECMmSSE090 */
					U4	xSSE091					:1;				/* ECMmSSE091 */
					U4	xSSE092					:1;				/* ECMmSSE092 */
					U4	xSSE093					:1;				/* ECMmSSE093 */
					U4	xSSE094					:1;				/* ECMmSSE094 */
					U4	xSSE095					:1;				/* ECMmSSE095 */
				} stBit;
			} unECMESSTR2;										/* OFFSET +50 */

			union												/* ECMmESSTR3 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE096					:1;				/* ECMmSSE096 */
					U4	xSSE097					:1;				/* ECMmSSE097 */
					U4	xSSE098					:1;				/* ECMmSSE098 */
					U4	xSSE099					:1;				/* ECMmSSE099 */
					U4	xSSE100					:1;				/* ECMmSSE100 */
					U4	xSSE101					:1;				/* ECMmSSE101 */
					U4	xSSE102					:1;				/* ECMmSSE102 */
					U4	xSSE103					:1;				/* ECMmSSE103 */
					U4	xSSE104					:1;				/* ECMmSSE104 */
					U4	xSSE105					:1;				/* ECMmSSE105 */
					U4	xSSE106					:1;				/* ECMmSSE106 */
					U4	xSSE107					:1;				/* ECMmSSE107 */
					U4	xSSE108					:1;				/* ECMmSSE108 */
					U4	xSSE109					:1;				/* ECMmSSE109 */
					U4	xSSE110					:1;				/* ECMmSSE110 */
					U4	xSSE111					:1;				/* ECMmSSE111 */
					U4	xSSE112					:1;				/* ECMmSSE112 */
					U4	xSSE113					:1;				/* ECMmSSE113 */
					U4	xSSE114					:1;				/* ECMmSSE114 */
					U4	xSSE115					:1;				/* ECMmSSE115 */
					U4	xSSE116					:1;				/* ECMmSSE116 */
					U4	xSSE117					:1;				/* ECMmSSE117 */
					U4	xSSE118					:1;				/* ECMmSSE118 */
					U4	xSSE119					:1;				/* ECMmSSE119 */
					U4	xSSE120					:1;				/* ECMmSSE120 */
					U4	xSSE121					:1;				/* ECMmSSE121 */
					U4	xSSE122					:1;				/* ECMmSSE122 */
					U4	xSSE123					:1;				/* ECMmSSE123 */
					U4	xSSE124					:1;				/* ECMmSSE124 */
					U4	xSSE125					:1;				/* ECMmSSE125 */
					U4	xSSE126					:1;				/* ECMmSSE126 */
					U4	xSSE127					:1;				/* ECMmSSE127 */
				} stBit;
			} unECMESSTR3;										/* OFFSET +54 */

			union												/* ECMmESSTR4 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE128					:1;				/* ECMmSSE128 */
					U4	xSSE129					:1;				/* ECMmSSE129 */
					U4	xSSE130					:1;				/* ECMmSSE130 */
					U4	xSSE131					:1;				/* ECMmSSE131 */
					U4	xSSE132					:1;				/* ECMmSSE132 */
					U4	xSSE133					:1;				/* ECMmSSE133 */
					U4	xSSE134					:1;				/* ECMmSSE134 */
					U4	xSSE135					:1;				/* ECMmSSE135 */
					U4	xSSE136					:1;				/* ECMmSSE136 */
					U4	xSSE137					:1;				/* ECMmSSE137 */
					U4	xSSE138					:1;				/* ECMmSSE138 */
					U4	xSSE139					:1;				/* ECMmSSE139 */
					U4	xSSE140					:1;				/* ECMmSSE140 */
					U4	xSSE141					:1;				/* ECMmSSE141 */
					U4	xSSE142					:1;				/* ECMmSSE142 */
					U4	xSSE143					:1;				/* ECMmSSE143 */
					U4	xSSE144					:1;				/* ECMmSSE144 */
					U4	xSSE145					:1;				/* ECMmSSE145 */
					U4	xSSE146					:1;				/* ECMmSSE146 */
					U4	xSSE147					:1;				/* ECMmSSE147 */
					U4	xSSE148					:1;				/* ECMmSSE148 */
					U4	xSSE149					:1;				/* ECMmSSE149 */
					U4	xSSE150					:1;				/* ECMmSSE150 */
					U4	xSSE151					:1;				/* ECMmSSE151 */
					U4	xSSE152					:1;				/* ECMmSSE152 */
					U4	xSSE153					:1;				/* ECMmSSE153 */
					U4	xSSE154					:1;				/* ECMmSSE154 */
					U4	xSSE155					:1;				/* ECMmSSE155 */
					U4	xSSE156					:1;				/* ECMmSSE156 */
					U4	xSSE157					:1;				/* ECMmSSE157 */
					U4	xSSE158					:1;				/* ECMmSSE158 */
					U4	xSSE159					:1;				/* ECMmSSE159 */
				} stBit;
			} unECMESSTR4;										/* OFFSET +58 */

			union												/* ECMmESSTR5 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE160					:1;				/* ECMmSSE160 */
					U4	xSSE161					:1;				/* ECMmSSE161 */
					U4	xSSE162					:1;				/* ECMmSSE162 */
					U4	xSSE163					:1;				/* ECMmSSE163 */
					U4	xSSE164					:1;				/* ECMmSSE164 */
					U4	xSSE165					:1;				/* ECMmSSE165 */
					U4	xSSE166					:1;				/* ECMmSSE166 */
					U4	xSSE167					:1;				/* ECMmSSE167 */
					U4	xSSE168					:1;				/* ECMmSSE168 */
					U4	xSSE169					:1;				/* ECMmSSE169 */
					U4	xSSE170					:1;				/* ECMmSSE170 */
					U4	xSSE171					:1;				/* ECMmSSE171 */
					U4	xSSE172					:1;				/* ECMmSSE172 */
					U4	xSSE173					:1;				/* ECMmSSE173 */
					U4	xSSE174					:1;				/* ECMmSSE174 */
					U4	xSSE175					:1;				/* ECMmSSE175 */
					U4	xSSE176					:1;				/* ECMmSSE176 */
					U4	xSSE177					:1;				/* ECMmSSE177 */
					U4	xSSE178					:1;				/* ECMmSSE178 */
					U4	xSSE179					:1;				/* ECMmSSE179 */
					U4	xSSE180					:1;				/* ECMmSSE180 */
					U4	xSSE181					:1;				/* ECMmSSE181 */
					U4	xSSE182					:1;				/* ECMmSSE182 */
					U4	xSSE183					:1;				/* ECMmSSE183 */
					U4	xSSE184					:1;				/* ECMmSSE184 */
					U4	xSSE185					:1;				/* ECMmSSE185 */
					U4	xSSE186					:1;				/* ECMmSSE186 */
					U4	xSSE187					:1;				/* ECMmSSE187 */
					U4	xSSE188					:1;				/* ECMmSSE188 */
					U4	xSSE189					:1;				/* ECMmSSE189 */
					U4	xSSE190					:1;				/* ECMmSSE190 */
					U4	xSSE191					:1;				/* ECMmSSE191 */
				} stBit;
			} unECMESSTR5;										/* OFFSET +5C */

			union												/* ECMmESSTR6 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE192					:1;				/* ECMmSSE192 */
					U4	xSSE193					:1;				/* ECMmSSE193 */
					U4	xSSE194					:1;				/* ECMmSSE194 */
					U4	xSSE195					:1;				/* ECMmSSE195 */
					U4	xSSE196					:1;				/* ECMmSSE196 */
					U4	xSSE197					:1;				/* ECMmSSE197 */
					U4	xSSE198					:1;				/* ECMmSSE198 */
					U4	xSSE199					:1;				/* ECMmSSE199 */
					U4	xSSE200					:1;				/* ECMmSSE200 */
					U4	xSSE201					:1;				/* ECMmSSE201 */
					U4	xSSE202					:1;				/* ECMmSSE202 */
					U4	xSSE203					:1;				/* ECMmSSE203 */
					U4	xSSE204					:1;				/* ECMmSSE204 */
					U4	xSSE205					:1;				/* ECMmSSE205 */
					U4	xSSE206					:1;				/* ECMmSSE206 */
					U4	xSSE207					:1;				/* ECMmSSE207 */
					U4	xSSE208					:1;				/* ECMmSSE208 */
					U4	xSSE209					:1;				/* ECMmSSE209 */
					U4	xSSE210					:1;				/* ECMmSSE210 */
					U4	xSSE211					:1;				/* ECMmSSE211 */
					U4	xSSE212					:1;				/* ECMmSSE212 */
					U4	xSSE213					:1;				/* ECMmSSE213 */
					U4	xSSE214					:1;				/* ECMmSSE214 */
					U4	xSSE215					:1;				/* ECMmSSE215 */
					U4	xSSE216					:1;				/* ECMmSSE216 */
					U4	xSSE217					:1;				/* ECMmSSE217 */
					U4	xSSE218					:1;				/* ECMmSSE218 */
					U4	xSSE219					:1;				/* ECMmSSE219 */
					U4	xSSE220					:1;				/* ECMmSSE220 */
					U4	xSSE221					:1;				/* ECMmSSE221 */
					U4	xSSE222					:1;				/* ECMmSSE222 */
					U4	xSSE223					:1;				/* ECMmSSE223 */
				} stBit;
			} unECMESSTR6;										/* OFFSET +60 */

			union												/* ECMmESSTR7 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE224					:1;				/* ECMmSSE224 */
					U4	xSSE225					:1;				/* ECMmSSE225 */
					U4	xSSE226					:1;				/* ECMmSSE226 */
					U4	xSSE227					:1;				/* ECMmSSE227 */
					U4	xSSE228					:1;				/* ECMmSSE228 */
					U4	xSSE229					:1;				/* ECMmSSE229 */
					U4	xSSE230					:1;				/* ECMmSSE230 */
					U4	xSSE231					:1;				/* ECMmSSE231 */
					U4	xSSE232					:1;				/* ECMmSSE232 */
					U4	xSSE233					:1;				/* ECMmSSE233 */
					U4	xSSE234					:1;				/* ECMmSSE234 */
					U4	xSSE235					:1;				/* ECMmSSE235 */
					U4	xSSE236					:1;				/* ECMmSSE236 */
					U4	xSSE237					:1;				/* ECMmSSE237 */
					U4	xSSE238					:1;				/* ECMmSSE238 */
					U4	xSSE239					:1;				/* ECMmSSE239 */
					U4	xSSE240					:1;				/* ECMmSSE240 */
					U4	xSSE241					:1;				/* ECMmSSE241 */
					U4	xSSE242					:1;				/* ECMmSSE242 */
					U4	xSSE243					:1;				/* ECMmSSE243 */
					U4	xSSE244					:1;				/* ECMmSSE244 */
					U4	xSSE245					:1;				/* ECMmSSE245 */
					U4	xSSE246					:1;				/* ECMmSSE246 */
					U4	xSSE247					:1;				/* ECMmSSE247 */
					U4	xSSE248					:1;				/* ECMmSSE248 */
					U4	xSSE249					:1;				/* ECMmSSE249 */
					U4	xSSE250					:1;				/* ECMmSSE250 */
					U4	xSSE251					:1;				/* ECMmSSE251 */
					U4	xSSE252					:1;				/* ECMmSSE252 */
					U4	xSSE253					:1;				/* ECMmSSE253 */
					U4	xSSE254					:1;				/* ECMmSSE254 */
					U4	xSSE255					:1;				/* ECMmSSE255 */
				} stBit;
			} unECMESSTR7;										/* OFFSET +64 */

			union												/* ECMmESSTR8 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE256					:1;				/* ECMmSSE256 */
					U4	xSSE257					:1;				/* ECMmSSE257 */
					U4	xSSE258					:1;				/* ECMmSSE258 */
					U4	xSSE259					:1;				/* ECMmSSE259 */
					U4	xSSE260					:1;				/* ECMmSSE260 */
					U4	xSSE261					:1;				/* ECMmSSE261 */
					U4	xSSE262					:1;				/* ECMmSSE262 */
					U4	xSSE263					:1;				/* ECMmSSE263 */
					U4	xSSE264					:1;				/* ECMmSSE264 */
					U4	xSSE265					:1;				/* ECMmSSE265 */
					U4	xSSE266					:1;				/* ECMmSSE266 */
					U4	xSSE267					:1;				/* ECMmSSE267 */
					U4	xSSE268					:1;				/* ECMmSSE268 */
					U4	xSSE269					:1;				/* ECMmSSE269 */
					U4	xSSE270					:1;				/* ECMmSSE270 */
					U4	xSSE271					:1;				/* ECMmSSE271 */
					U4	xSSE272					:1;				/* ECMmSSE272 */
					U4	xSSE273					:1;				/* ECMmSSE273 */
					U4	xSSE274					:1;				/* ECMmSSE274 */
					U4	xSSE275					:1;				/* ECMmSSE275 */
					U4	xSSE276					:1;				/* ECMmSSE276 */
					U4	xSSE277					:1;				/* ECMmSSE277 */
					U4	xSSE278					:1;				/* ECMmSSE278 */
					U4	xSSE279					:1;				/* ECMmSSE279 */
					U4	xSSE280					:1;				/* ECMmSSE280 */
					U4	xSSE281					:1;				/* ECMmSSE281 */
					U4	xSSE282					:1;				/* ECMmSSE282 */
					U4	xSSE283					:1;				/* ECMmSSE283 */
					U4	xSSE284					:1;				/* ECMmSSE284 */
					U4	xSSE285					:1;				/* ECMmSSE285 */
					U4	xSSE286					:1;				/* ECMmSSE286 */
					U4	xSSE287					:1;				/* ECMmSSE287 */
				} stBit;
			} unECMESSTR8;										/* OFFSET +68 */

			union												/* ECMmESSTR9 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE288					:1;				/* ECMmSSE288 */
					U4	xSSE289					:1;				/* ECMmSSE289 */
					U4	xSSE290					:1;				/* ECMmSSE290 */
					U4	xSSE291					:1;				/* ECMmSSE291 */
					U4	xSSE292					:1;				/* ECMmSSE292 */
					U4	xSSE293					:1;				/* ECMmSSE293 */
					U4	xSSE294					:1;				/* ECMmSSE294 */
					U4	xSSE295					:1;				/* ECMmSSE295 */
					U4	xSSE296					:1;				/* ECMmSSE296 */
					U4	xSSE297					:1;				/* ECMmSSE297 */
					U4	xSSE298					:1;				/* ECMmSSE298 */
					U4	xSSE299					:1;				/* ECMmSSE299 */
					U4	xSSE300					:1;				/* ECMmSSE300 */
					U4	xSSE301					:1;				/* ECMmSSE301 */
					U4	xSSE302					:1;				/* ECMmSSE302 */
					U4	xSSE303					:1;				/* ECMmSSE303 */
					U4	xSSE304					:1;				/* ECMmSSE304 */
					U4	xSSE305					:1;				/* ECMmSSE305 */
					U4	xSSE306					:1;				/* ECMmSSE306 */
					U4	xSSE307					:1;				/* ECMmSSE307 */
					U4	xSSE308					:1;				/* ECMmSSE308 */
					U4	xSSE309					:1;				/* ECMmSSE309 */
					U4	xSSE310					:1;				/* ECMmSSE310 */
					U4	xSSE311					:1;				/* ECMmSSE311 */
					U4	xSSE312					:1;				/* ECMmSSE312 */
					U4	xSSE313					:1;				/* ECMmSSE313 */
					U4	xSSE314					:1;				/* ECMmSSE314 */
					U4	xSSE315					:1;				/* ECMmSSE315 */
					U4	xSSE316					:1;				/* ECMmSSE316 */
					U4	xSSE317					:1;				/* ECMmSSE317 */
					U4	xSSE318					:1;				/* ECMmSSE318 */
					U4	xSSE319					:1;				/* ECMmSSE319 */
				} stBit;
			} unECMESSTR9;										/* OFFSET +6C */

			union												/* ECMmESSTR10 , m=M/C */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xSSE320					:1;				/* ECMmSSE320 */
					U4	xSSE321					:1;				/* ECMmSSE321 */
					U4	xSSE322					:1;				/* ECMmSSE322 */
					U4	xSSE323					:1;				/* ECMmSSE323 */
					U4	xSSE324					:1;				/* ECMmSSE324 */
					U4	xSSE325					:1;				/* ECMmSSE325 */
					U4	xSSE326					:1;				/* ECMmSSE326 */
					U4	xSSE327					:1;				/* ECMmSSE327 */
					U4	xSSE328					:1;				/* ECMmSSE328 */
					U4	xSSE329					:1;				/* ECMmSSE329 */
					U4	xSSE330					:1;				/* ECMmSSE330 */
					U4	xSSE331					:1;				/* ECMmSSE331 */
					U4	xSSE332					:1;				/* ECMmSSE332 */
					U4	xSSE333					:1;				/* ECMmSSE333 */
					U4	xSSE334					:1;				/* ECMmSSE334 */
					U4	xSSE335					:1;				/* ECMmSSE335 */
					U4	xSSE336					:1;				/* ECMmSSE336 */
					U4	xSSE337					:1;				/* ECMmSSE337 */
					U4	xSSE338					:1;				/* ECMmSSE338 */
					U4	xSSE339					:1;				/* ECMmSSE339 */
					U4	xSSE340					:1;				/* ECMmSSE340 */
					U4	xSSE341					:1;				/* ECMmSSE341 */
					U4	xSSE342					:1;				/* ECMmSSE342 */
					U4	xSSE343					:1;				/* ECMmSSE343 */
					U4	xSSE344					:1;				/* ECMmSSE344 */
					U4	xSSE345					:1;				/* ECMmSSE345 */
					U4	xSSE346					:1;				/* ECMmSSE346 */
					U4	xSSE347					:1;				/* ECMmSSE347 */
					U4	xSSE348					:1;				/* ECMmSSE348 */
					U4	xSSE349					:1;				/* ECMmSSE349 */
					U4	xSSE350					:1;				/* ECMmSSE350 */
					U4	xSSE351					:1;				/* ECMmSSE351 */
				} stBit;
			} unECMESSTR10;										/* OFFSET +70 */
		} stECMESSTRn;
	} unECMESSTRn;

}	Reg_Ecm_EcmmType;

/* ECM */
/* ============================================================================ */
/* =============================== Module: ECM ================================ */
/* ============================================================================ */
typedef	struct													/* ECM */
{
	union														/* ECMEPCFG */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECMSL0					:1;						/* ECMSL0 */
			U4	b7Dummy1				:31;
		} stBit;
	} unECMEPCFG;												/* 0xFFD38000 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{

			union												/* ECMISCFG0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS000					:1;				/* ECMIS000 */
					U4	xIS001					:1;				/* ECMIS001 */
					U4	xIS002					:1;				/* ECMIS002 */
					U4	xIS003					:1;				/* ECMIS003 */
					U4	xIS004					:1;				/* ECMIS004 */
					U4	xIS005					:1;				/* ECMIS005 */
					U4	xIS006					:1;				/* ECMIS006 */
					U4	xIS007					:1;				/* ECMIS007 */
					U4	xIS008					:1;				/* ECMIS008 */
					U4	xIS009					:1;				/* ECMIS009 */
					U4	xIS010					:1;				/* ECMIS010 */
					U4	xIS011					:1;				/* ECMIS011 */
					U4	xIS012					:1;				/* ECMIS012 */
					U4	xIS013					:1;				/* ECMIS013 */
					U4	xIS014					:1;				/* ECMIS014 */
					U4	xIS015					:1;				/* ECMIS015 */
					U4	xIS016					:1;				/* ECMIS016 */
					U4	xIS017					:1;				/* ECMIS017 */
					U4	xIS018					:1;				/* ECMIS018 */
					U4	xIS019					:1;				/* ECMIS019 */
					U4	xIS020					:1;				/* ECMIS020 */
					U4	xIS021					:1;				/* ECMIS021 */
					U4	xIS022					:1;				/* ECMIS022 */
					U4	xIS023					:1;				/* ECMIS023 */
					U4	xIS024					:1;				/* ECMIS024 */
					U4	xIS025					:1;				/* ECMIS025 */
					U4	xIS026					:1;				/* ECMIS026 */
					U4	xIS027					:1;				/* ECMIS027 */
					U4	xIS028					:1;				/* ECMIS028 */
					U4	xIS029					:1;				/* ECMIS029 */
					U4	xIS030					:1;				/* ECMIS030 */
					U4	xIS031					:1;				/* ECMIS031 */
				} stBit;
			} unECMISCFG0;										/* 0xFFD38004 */

			union												/* ECMISCFG1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS032					:1;				/* ECMIS032 */
					U4	xIS033					:1;				/* ECMIS033 */
					U4	xIS034					:1;				/* ECMIS034 */
					U4	xIS035					:1;				/* ECMIS035 */
					U4	xIS036					:1;				/* ECMIS036 */
					U4	xIS037					:1;				/* ECMIS037 */
					U4	xIS038					:1;				/* ECMIS038 */
					U4	xIS039					:1;				/* ECMIS039 */
					U4	xIS040					:1;				/* ECMIS040 */
					U4	xIS041					:1;				/* ECMIS041 */
					U4	xIS042					:1;				/* ECMIS042 */
					U4	xIS043					:1;				/* ECMIS043 */
					U4	xIS044					:1;				/* ECMIS044 */
					U4	xIS045					:1;				/* ECMIS045 */
					U4	xIS046					:1;				/* ECMIS046 */
					U4	xIS047					:1;				/* ECMIS047 */
					U4	xIS048					:1;				/* ECMIS048 */
					U4	xIS049					:1;				/* ECMIS049 */
					U4	xIS050					:1;				/* ECMIS050 */
					U4	xIS051					:1;				/* ECMIS051 */
					U4	xIS052					:1;				/* ECMIS052 */
					U4	xIS053					:1;				/* ECMIS053 */
					U4	xIS054					:1;				/* ECMIS054 */
					U4	xIS055					:1;				/* ECMIS055 */
					U4	xIS056					:1;				/* ECMIS056 */
					U4	xIS057					:1;				/* ECMIS057 */
					U4	xIS058					:1;				/* ECMIS058 */
					U4	xIS059					:1;				/* ECMIS059 */
					U4	xIS060					:1;				/* ECMIS060 */
					U4	xIS061					:1;				/* ECMIS061 */
					U4	xIS062					:1;				/* ECMIS062 */
					U4	xIS063					:1;				/* ECMIS063 */
				} stBit;
			} unECMISCFG1;										/* 0xFFD38008 */

			union												/* ECMISCFG2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS064					:1;				/* ECMIS064 */
					U4	xIS065					:1;				/* ECMIS065 */
					U4	xIS066					:1;				/* ECMIS066 */
					U4	xIS067					:1;				/* ECMIS067 */
					U4	xIS068					:1;				/* ECMIS068 */
					U4	xIS069					:1;				/* ECMIS069 */
					U4	xIS070					:1;				/* ECMIS070 */
					U4	xIS071					:1;				/* ECMIS071 */
					U4	xIS072					:1;				/* ECMIS072 */
					U4	xIS073					:1;				/* ECMIS073 */
					U4	xIS074					:1;				/* ECMIS074 */
					U4	xIS075					:1;				/* ECMIS075 */
					U4	xIS076					:1;				/* ECMIS076 */
					U4	xIS077					:1;				/* ECMIS077 */
					U4	xIS078					:1;				/* ECMIS078 */
					U4	xIS079					:1;				/* ECMIS079 */
					U4	xIS080					:1;				/* ECMIS080 */
					U4	xIS081					:1;				/* ECMIS081 */
					U4	xIS082					:1;				/* ECMIS082 */
					U4	xIS083					:1;				/* ECMIS083 */
					U4	xIS084					:1;				/* ECMIS084 */
					U4	xIS085					:1;				/* ECMIS085 */
					U4	xIS086					:1;				/* ECMIS086 */
					U4	xIS087					:1;				/* ECMIS087 */
					U4	xIS088					:1;				/* ECMIS088 */
					U4	xIS089					:1;				/* ECMIS089 */
					U4	xIS090					:1;				/* ECMIS090 */
					U4	xIS091					:1;				/* ECMIS091 */
					U4	xIS092					:1;				/* ECMIS092 */
					U4	xIS093					:1;				/* ECMIS093 */
					U4	xIS094					:1;				/* ECMIS094 */
					U4	xIS095					:1;				/* ECMIS095 */
				} stBit;
			} unECMISCFG2;										/* 0xFFD3800C*/

			union												/* ECMISCFG3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS096					:1;				/* ECMIS096 */
					U4	xIS097					:1;				/* ECMIS097 */
					U4	xIS098					:1;				/* ECMIS098 */
					U4	xIS099					:1;				/* ECMIS099 */
					U4	xIS100					:1;				/* ECMIS100 */
					U4	xIS101					:1;				/* ECMIS101 */
					U4	xIS102					:1;				/* ECMIS102 */
					U4	xIS103					:1;				/* ECMIS103 */
					U4	xIS104					:1;				/* ECMIS104 */
					U4	xIS105					:1;				/* ECMIS105 */
					U4	xIS106					:1;				/* ECMIS106 */
					U4	xIS107					:1;				/* ECMIS107 */
					U4	xIS108					:1;				/* ECMIS108 */
					U4	xIS109					:1;				/* ECMIS109 */
					U4	xIS110					:1;				/* ECMIS110 */
					U4	xIS111					:1;				/* ECMIS111 */
					U4	xIS112					:1;				/* ECMIS112 */
					U4	xIS113					:1;				/* ECMIS113 */
					U4	xIS114					:1;				/* ECMIS114 */
					U4	xIS115					:1;				/* ECMIS115 */
					U4	xIS116					:1;				/* ECMIS116 */
					U4	xIS117					:1;				/* ECMIS117 */
					U4	xIS118					:1;				/* ECMIS118 */
					U4	xIS119					:1;				/* ECMIS119 */
					U4	xIS120					:1;				/* ECMIS120 */
					U4	xIS121					:1;				/* ECMIS121 */
					U4	xIS122					:1;				/* ECMIS122 */
					U4	xIS123					:1;				/* ECMIS123 */
					U4	xIS124					:1;				/* ECMIS124 */
					U4	xIS125					:1;				/* ECMIS125 */
					U4	xIS126					:1;				/* ECMIS126 */
					U4	xIS127					:1;				/* ECMIS127 */
				} stBit;
			} unECMISCFG3;										/* 0xFFD38010 */

			union												/* ECMISCFG4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS128					:1;				/* ECMIS128 */
					U4	xIS129					:1;				/* ECMIS129 */
					U4	xIS130					:1;				/* ECMIS130 */
					U4	xIS131					:1;				/* ECMIS131 */
					U4	xIS132					:1;				/* ECMIS132 */
					U4	xIS133					:1;				/* ECMIS133 */
					U4	xIS134					:1;				/* ECMIS134 */
					U4	xIS135					:1;				/* ECMIS135 */
					U4	xIS136					:1;				/* ECMIS136 */
					U4	xIS137					:1;				/* ECMIS137 */
					U4	xIS138					:1;				/* ECMIS138 */
					U4	xIS139					:1;				/* ECMIS139 */
					U4	xIS140					:1;				/* ECMIS140 */
					U4	xIS141					:1;				/* ECMIS141 */
					U4	xIS142					:1;				/* ECMIS142 */
					U4	xIS143					:1;				/* ECMIS143 */
					U4	xIS144					:1;				/* ECMIS144 */
					U4	xIS145					:1;				/* ECMIS145 */
					U4	xIS146					:1;				/* ECMIS146 */
					U4	xIS147					:1;				/* ECMIS147 */
					U4	xIS148					:1;				/* ECMIS148 */
					U4	xIS149					:1;				/* ECMIS149 */
					U4	xIS150					:1;				/* ECMIS150 */
					U4	xIS151					:1;				/* ECMIS151 */
					U4	xIS152					:1;				/* ECMIS152 */
					U4	xIS153					:1;				/* ECMIS153 */
					U4	xIS154					:1;				/* ECMIS154 */
					U4	xIS155					:1;				/* ECMIS155 */
					U4	xIS156					:1;				/* ECMIS156 */
					U4	xIS157					:1;				/* ECMIS157 */
					U4	xIS158					:1;				/* ECMIS158 */
					U4	xIS159					:1;				/* ECMIS159 */
				} stBit;
			} unECMISCFG4;										/* 0xFFD38014 */

			union												/* ECMISCFG5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS160					:1;				/* ECMIS160 */
					U4	xIS161					:1;				/* ECMIS161 */
					U4	xIS162					:1;				/* ECMIS162 */
					U4	xIS163					:1;				/* ECMIS163 */
					U4	xIS164					:1;				/* ECMIS164 */
					U4	xIS165					:1;				/* ECMIS165 */
					U4	xIS166					:1;				/* ECMIS166 */
					U4	xIS167					:1;				/* ECMIS167 */
					U4	xIS168					:1;				/* ECMIS168 */
					U4	xIS169					:1;				/* ECMIS169 */
					U4	xIS170					:1;				/* ECMIS170 */
					U4	xIS171					:1;				/* ECMIS171 */
					U4	xIS172					:1;				/* ECMIS172 */
					U4	xIS173					:1;				/* ECMIS173 */
					U4	xIS174					:1;				/* ECMIS174 */
					U4	xIS175					:1;				/* ECMIS175 */
					U4	xIS176					:1;				/* ECMIS176 */
					U4	xIS177					:1;				/* ECMIS177 */
					U4	xIS178					:1;				/* ECMIS178 */
					U4	xIS179					:1;				/* ECMIS179 */
					U4	xIS180					:1;				/* ECMIS180 */
					U4	xIS181					:1;				/* ECMIS181 */
					U4	xIS182					:1;				/* ECMIS182 */
					U4	xIS183					:1;				/* ECMIS183 */
					U4	xIS184					:1;				/* ECMIS184 */
					U4	xIS185					:1;				/* ECMIS185 */
					U4	xIS186					:1;				/* ECMIS186 */
					U4	xIS187					:1;				/* ECMIS187 */
					U4	xIS188					:1;				/* ECMIS188 */
					U4	xIS189					:1;				/* ECMIS189 */
					U4	xIS190					:1;				/* ECMIS190 */
					U4	xIS191					:1;				/* ECMIS191 */
				} stBit;
			} unECMISCFG5;										/* 0xFFD38018 */

			union												/* ECMISCFG6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS192					:1;				/* ECMIS192 */
					U4	xIS193					:1;				/* ECMIS193 */
					U4	xIS194					:1;				/* ECMIS194 */
					U4	xIS195					:1;				/* ECMIS195 */
					U4	xIS196					:1;				/* ECMIS196 */
					U4	xIS197					:1;				/* ECMIS197 */
					U4	xIS198					:1;				/* ECMIS198 */
					U4	xIS199					:1;				/* ECMIS199 */
					U4	xIS200					:1;				/* ECMIS200 */
					U4	xIS201					:1;				/* ECMIS201 */
					U4	xIS202					:1;				/* ECMIS202 */
					U4	xIS203					:1;				/* ECMIS203 */
					U4	xIS204					:1;				/* ECMIS204 */
					U4	xIS205					:1;				/* ECMIS205 */
					U4	xIS206					:1;				/* ECMIS206 */
					U4	xIS207					:1;				/* ECMIS207 */
					U4	xIS208					:1;				/* ECMIS208 */
					U4	xIS209					:1;				/* ECMIS209 */
					U4	xIS210					:1;				/* ECMIS210 */
					U4	xIS211					:1;				/* ECMIS211 */
					U4	xIS212					:1;				/* ECMIS212 */
					U4	xIS213					:1;				/* ECMIS213 */
					U4	xIS214					:1;				/* ECMIS214 */
					U4	xIS215					:1;				/* ECMIS215 */
					U4	xIS216					:1;				/* ECMIS216 */
					U4	xIS217					:1;				/* ECMIS217 */
					U4	xIS218					:1;				/* ECMIS218 */
					U4	xIS219					:1;				/* ECMIS219 */
					U4	xIS220					:1;				/* ECMIS220 */
					U4	xIS221					:1;				/* ECMIS221 */
					U4	xIS222					:1;				/* ECMIS222 */
					U4	xIS223					:1;				/* ECMIS223 */
				} stBit;
			} unECMISCFG6;										/* 0xFFD3801C */

			union												/* ECMISCFG7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS224					:1;				/* ECMIS224 */
					U4	xIS225					:1;				/* ECMIS225 */
					U4	xIS226					:1;				/* ECMIS226 */
					U4	xIS227					:1;				/* ECMIS227 */
					U4	xIS228					:1;				/* ECMIS228 */
					U4	xIS229					:1;				/* ECMIS229 */
					U4	xIS230					:1;				/* ECMIS230 */
					U4	xIS231					:1;				/* ECMIS231 */
					U4	xIS232					:1;				/* ECMIS232 */
					U4	xIS233					:1;				/* ECMIS233 */
					U4	xIS234					:1;				/* ECMIS234 */
					U4	xIS235					:1;				/* ECMIS235 */
					U4	xIS236					:1;				/* ECMIS236 */
					U4	xIS237					:1;				/* ECMIS237 */
					U4	xIS238					:1;				/* ECMIS238 */
					U4	xIS239					:1;				/* ECMIS239 */
					U4	xIS240					:1;				/* ECMIS240 */
					U4	xIS241					:1;				/* ECMIS241 */
					U4	xIS242					:1;				/* ECMIS242 */
					U4	xIS243					:1;				/* ECMIS243 */
					U4	xIS244					:1;				/* ECMIS244 */
					U4	xIS245					:1;				/* ECMIS245 */
					U4	xIS246					:1;				/* ECMIS246 */
					U4	xIS247					:1;				/* ECMIS247 */
					U4	xIS248					:1;				/* ECMIS248 */
					U4	xIS249					:1;				/* ECMIS249 */
					U4	xIS250					:1;				/* ECMIS250 */
					U4	xIS251					:1;				/* ECMIS251 */
					U4	xIS252					:1;				/* ECMIS252 */
					U4	xIS253					:1;				/* ECMIS253 */
					U4	xIS254					:1;				/* ECMIS254 */
					U4	xIS255					:1;				/* ECMIS255 */
				} stBit;
			} unECMISCFG7;										/* 0xFFD38020*/

			union												/* ECMISCFG8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS256					:1;				/* ECMIS256 */
					U4	xIS257					:1;				/* ECMIS257 */
					U4	xIS258					:1;				/* ECMIS258 */
					U4	xIS259					:1;				/* ECMIS259 */
					U4	xIS260					:1;				/* ECMIS260 */
					U4	xIS261					:1;				/* ECMIS261 */
					U4	xIS262					:1;				/* ECMIS262 */
					U4	xIS263					:1;				/* ECMIS263 */
					U4	xIS264					:1;				/* ECMIS264 */
					U4	xIS265					:1;				/* ECMIS265 */
					U4	xIS266					:1;				/* ECMIS266 */
					U4	xIS267					:1;				/* ECMIS267 */
					U4	xIS268					:1;				/* ECMIS268 */
					U4	xIS269					:1;				/* ECMIS269 */
					U4	xIS270					:1;				/* ECMIS270 */
					U4	xIS271					:1;				/* ECMIS271 */
					U4	xIS272					:1;				/* ECMIS272 */
					U4	xIS273					:1;				/* ECMIS273 */
					U4	xIS274					:1;				/* ECMIS274 */
					U4	xIS275					:1;				/* ECMIS275 */
					U4	xIS276					:1;				/* ECMIS276 */
					U4	xIS277					:1;				/* ECMIS277 */
					U4	xIS278					:1;				/* ECMIS278 */
					U4	xIS279					:1;				/* ECMIS279 */
					U4	xIS280					:1;				/* ECMIS280 */
					U4	xIS281					:1;				/* ECMIS281 */
					U4	xIS282					:1;				/* ECMIS282 */
					U4	xIS283					:1;				/* ECMIS283 */
					U4	xIS284					:1;				/* ECMIS284 */
					U4	xIS285					:1;				/* ECMIS285 */
					U4	xIS286					:1;				/* ECMIS286 */
					U4	xIS287					:1;				/* ECMIS287 */
				} stBit;
			} unECMISCFG8;										/* 0xFFD38024 */

			union												/* ECMISCFG9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS288					:1;				/* ECMIS288 */
					U4	xIS289					:1;				/* ECMIS289 */
					U4	xIS290					:1;				/* ECMIS290 */
					U4	xIS291					:1;				/* ECMIS291 */
					U4	xIS292					:1;				/* ECMIS292 */
					U4	xIS293					:1;				/* ECMIS293 */
					U4	xIS294					:1;				/* ECMIS294 */
					U4	xIS295					:1;				/* ECMIS295 */
					U4	xIS296					:1;				/* ECMIS296 */
					U4	xIS297					:1;				/* ECMIS297 */
					U4	xIS298					:1;				/* ECMIS298 */
					U4	xIS299					:1;				/* ECMIS299 */
					U4	xIS300					:1;				/* ECMIS300 */
					U4	xIS301					:1;				/* ECMIS301 */
					U4	xIS302					:1;				/* ECMIS302 */
					U4	xIS303					:1;				/* ECMIS303 */
					U4	xIS304					:1;				/* ECMIS304 */
					U4	xIS305					:1;				/* ECMIS305 */
					U4	xIS306					:1;				/* ECMIS306 */
					U4	xIS307					:1;				/* ECMIS307 */
					U4	xIS308					:1;				/* ECMIS308 */
					U4	xIS309					:1;				/* ECMIS309 */
					U4	xIS310					:1;				/* ECMIS310 */
					U4	xIS311					:1;				/* ECMIS311 */
					U4	xIS312					:1;				/* ECMIS312 */
					U4	xIS313					:1;				/* ECMIS313 */
					U4	xIS314					:1;				/* ECMIS314 */
					U4	xIS315					:1;				/* ECMIS315 */
					U4	xIS316					:1;				/* ECMIS316 */
					U4	xIS317					:1;				/* ECMIS317 */
					U4	xIS318					:1;				/* ECMIS318 */
					U4	xIS319					:1;				/* ECMIS319 */
				} stBit;
			} unECMISCFG9;										/* 0xFFD38028 */

			union												/* ECMISCFG10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIS320					:1;				/* ECMIS320 */
					U4	xIS321					:1;				/* ECMIS321 */
					U4	xIS322					:1;				/* ECMIS322 */
					U4	xIS323					:1;				/* ECMIS323 */
					U4	xIS324					:1;				/* ECMIS324 */
					U4	xIS325					:1;				/* ECMIS325 */
					U4	xIS326					:1;				/* ECMIS326 */
					U4	xIS327					:1;				/* ECMIS327 */
					U4	xIS328					:1;				/* ECMIS328 */
					U4	xIS329					:1;				/* ECMIS329 */
					U4	xIS330					:1;				/* ECMIS330 */
					U4	xIS331					:1;				/* ECMIS331 */
					U4	xIS332					:1;				/* ECMIS332 */
					U4	xIS333					:1;				/* ECMIS333 */
					U4	xIS334					:1;				/* ECMIS334 */
					U4	xIS335					:1;				/* ECMIS335 */
					U4	xIS336					:1;				/* ECMIS336 */
					U4	xIS337					:1;				/* ECMIS337 */
					U4	xIS338					:1;				/* ECMIS338 */
					U4	xIS339					:1;				/* ECMIS339 */
					U4	xIS340					:1;				/* ECMIS340 */
					U4	xIS341					:1;				/* ECMIS341 */
					U4	xIS342					:1;				/* ECMIS342 */
					U4	xIS343					:1;				/* ECMIS343 */
					U4	xIS344					:1;				/* ECMIS344 */
					U4	xIS345					:1;				/* ECMIS345 */
					U4	xIS346					:1;				/* ECMIS346 */
					U4	xIS347					:1;				/* ECMIS347 */
					U4	xIS348					:1;				/* ECMIS348 */
					U4	xIS349					:1;				/* ECMIS349 */
					U4	xIS350					:1;				/* ECMIS350 */
					U4	xIS351					:1;				/* ECMIS351 */
				} stBit;
			} unECMISCFG10;										/* 0xFFD3802C */
		} stECMISCFGn;
	} unECMISCFGn;

	U1	u1Dummy1[16];	/* 0xFFD38030 - 0xFFD3803F */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMINCFG0_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_000					:1;				/* ECMIE0_000 */
					U4	xIE0_001					:1;				/* ECMIE0_001 */
					U4	xIE0_002					:1;				/* ECMIE0_002 */
					U4	xIE0_003					:1;				/* ECMIE0_003 */
					U4	xIE0_004					:1;				/* ECMIE0_004 */
					U4	xIE0_005					:1;				/* ECMIE0_005 */
					U4	xIE0_006					:1;				/* ECMIE0_006 */
					U4	xIE0_007					:1;				/* ECMIE0_007 */
					U4	xIE0_008					:1;				/* ECMIE0_008 */
					U4	xIE0_009					:1;				/* ECMIE0_009 */
					U4	xIE0_010					:1;				/* ECMIE0_010 */
					U4	xIE0_011					:1;				/* ECMIE0_011 */
					U4	xIE0_012					:1;				/* ECMIE0_012 */
					U4	xIE0_013					:1;				/* ECMIE0_013 */
					U4	xIE0_014					:1;				/* ECMIE0_014 */
					U4	xIE0_015					:1;				/* ECMIE0_015 */
					U4	xIE0_016					:1;				/* ECMIE0_016 */
					U4	xIE0_017					:1;				/* ECMIE0_017 */
					U4	xIE0_018					:1;				/* ECMIE0_018 */
					U4	xIE0_019					:1;				/* ECMIE0_019 */
					U4	xIE0_020					:1;				/* ECMIE0_020 */
					U4	xIE0_021					:1;				/* ECMIE0_021 */
					U4	xIE0_022					:1;				/* ECMIE0_022 */
					U4	xIE0_023					:1;				/* ECMIE0_023 */
					U4	xIE0_024					:1;				/* ECMIE0_024 */
					U4	xIE0_025					:1;				/* ECMIE0_025 */
					U4	xIE0_026					:1;				/* ECMIE0_026 */
					U4	xIE0_027					:1;				/* ECMIE0_027 */
					U4	xIE0_028					:1;				/* ECMIE0_028 */
					U4	xIE0_029					:1;				/* ECMIE0_029 */
					U4	xIE0_030					:1;				/* ECMIE0_030 */
					U4	xIE0_031					:1;				/* ECMIE0_031 */
				} stBit;
			} unECMINCFG0_0;										/* 0xFFD38040 */

			union												/* ECMINCFG0_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_032					:1;				/* ECMIE0_032 */
					U4	xIE0_033					:1;				/* ECMIE0_033 */
					U4	xIE0_034					:1;				/* ECMIE0_034 */
					U4	xIE0_035					:1;				/* ECMIE0_035 */
					U4	xIE0_036					:1;				/* ECMIE0_036 */
					U4	xIE0_037					:1;				/* ECMIE0_037 */
					U4	xIE0_038					:1;				/* ECMIE0_038 */
					U4	xIE0_039					:1;				/* ECMIE0_039 */
					U4	xIE0_040					:1;				/* ECMIE0_040 */
					U4	xIE0_041					:1;				/* ECMIE0_041 */
					U4	xIE0_042					:1;				/* ECMIE0_042 */
					U4	xIE0_043					:1;				/* ECMIE0_043 */
					U4	xIE0_044					:1;				/* ECMIE0_044 */
					U4	xIE0_045					:1;				/* ECMIE0_045 */
					U4	xIE0_046					:1;				/* ECMIE0_046 */
					U4	xIE0_047					:1;				/* ECMIE0_047 */
					U4	xIE0_048					:1;				/* ECMIE0_048 */
					U4	xIE0_049					:1;				/* ECMIE0_049 */
					U4	xIE0_050					:1;				/* ECMIE0_050 */
					U4	xIE0_051					:1;				/* ECMIE0_051 */
					U4	xIE0_052					:1;				/* ECMIE0_052 */
					U4	xIE0_053					:1;				/* ECMIE0_053 */
					U4	xIE0_054					:1;				/* ECMIE0_054 */
					U4	xIE0_055					:1;				/* ECMIE0_055 */
					U4	xIE0_056					:1;				/* ECMIE0_056 */
					U4	xIE0_057					:1;				/* ECMIE0_057 */
					U4	xIE0_058					:1;				/* ECMIE0_058 */
					U4	xIE0_059					:1;				/* ECMIE0_059 */
					U4	xIE0_060					:1;				/* ECMIE0_060 */
					U4	xIE0_061					:1;				/* ECMIE0_061 */
					U4	xIE0_062					:1;				/* ECMIE0_062 */
					U4	xIE0_063					:1;				/* ECMIE0_063 */
				} stBit;
			} unECMINCFG0_1;										/* 0xFFD38044 */

			union												/* ECMINCFG0_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_064					:1;				/* ECMIE0_064 */
					U4	xIE0_065					:1;				/* ECMIE0_065 */
					U4	xIE0_066					:1;				/* ECMIE0_066 */
					U4	xIE0_067					:1;				/* ECMIE0_067 */
					U4	xIE0_068					:1;				/* ECMIE0_068 */
					U4	xIE0_069					:1;				/* ECMIE0_069 */
					U4	xIE0_070					:1;				/* ECMIE0_070 */
					U4	xIE0_071					:1;				/* ECMIE0_071 */
					U4	xIE0_072					:1;				/* ECMIE0_072 */
					U4	xIE0_073					:1;				/* ECMIE0_073 */
					U4	xIE0_074					:1;				/* ECMIE0_074 */
					U4	xIE0_075					:1;				/* ECMIE0_075 */
					U4	xIE0_076					:1;				/* ECMIE0_076 */
					U4	xIE0_077					:1;				/* ECMIE0_077 */
					U4	xIE0_078					:1;				/* ECMIE0_078 */
					U4	xIE0_079					:1;				/* ECMIE0_079 */
					U4	xIE0_080					:1;				/* ECMIE0_080 */
					U4	xIE0_081					:1;				/* ECMIE0_081 */
					U4	xIE0_082					:1;				/* ECMIE0_082 */
					U4	xIE0_083					:1;				/* ECMIE0_083 */
					U4	xIE0_084					:1;				/* ECMIE0_084 */
					U4	xIE0_085					:1;				/* ECMIE0_085 */
					U4	xIE0_086					:1;				/* ECMIE0_086 */
					U4	xIE0_087					:1;				/* ECMIE0_087 */
					U4	xIE0_088					:1;				/* ECMIE0_088 */
					U4	xIE0_089					:1;				/* ECMIE0_089 */
					U4	xIE0_090					:1;				/* ECMIE0_090 */
					U4	xIE0_091					:1;				/* ECMIE0_091 */
					U4	xIE0_092					:1;				/* ECMIE0_092 */
					U4	xIE0_093					:1;				/* ECMIE0_093 */
					U4	xIE0_094					:1;				/* ECMIE0_094 */
					U4	xIE0_095					:1;				/* ECMIE0_095 */
				} stBit;
			} unECMINCFG0_2;										/* 0xFFD38048 */

			union												/* ECMINCFG0_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_096					:1;				/* ECMIE0_096 */
					U4	xIE0_097					:1;				/* ECMIE0_097 */
					U4	xIE0_098					:1;				/* ECMIE0_098 */
					U4	xIE0_099					:1;				/* ECMIE0_099 */
					U4	xIE0_100					:1;				/* ECMIE0_100 */
					U4	xIE0_101					:1;				/* ECMIE0_101 */
					U4	xIE0_102					:1;				/* ECMIE0_102 */
					U4	xIE0_103					:1;				/* ECMIE0_103 */
					U4	xIE0_104					:1;				/* ECMIE0_104 */
					U4	xIE0_105					:1;				/* ECMIE0_105 */
					U4	xIE0_106					:1;				/* ECMIE0_106 */
					U4	xIE0_107					:1;				/* ECMIE0_107 */
					U4	xIE0_108					:1;				/* ECMIE0_108 */
					U4	xIE0_109					:1;				/* ECMIE0_109 */
					U4	xIE0_110					:1;				/* ECMIE0_110 */
					U4	xIE0_111					:1;				/* ECMIE0_111 */
					U4	xIE0_112					:1;				/* ECMIE0_112 */
					U4	xIE0_113					:1;				/* ECMIE0_113 */
					U4	xIE0_114					:1;				/* ECMIE0_114 */
					U4	xIE0_115					:1;				/* ECMIE0_115 */
					U4	xIE0_116					:1;				/* ECMIE0_116 */
					U4	xIE0_117					:1;				/* ECMIE0_117 */
					U4	xIE0_118					:1;				/* ECMIE0_118 */
					U4	xIE0_119					:1;				/* ECMIE0_119 */
					U4	xIE0_120					:1;				/* ECMIE0_120 */
					U4	xIE0_121					:1;				/* ECMIE0_121 */
					U4	xIE0_122					:1;				/* ECMIE0_122 */
					U4	xIE0_123					:1;				/* ECMIE0_123 */
					U4	xIE0_124					:1;				/* ECMIE0_124 */
					U4	xIE0_125					:1;				/* ECMIE0_125 */
					U4	xIE0_126					:1;				/* ECMIE0_126 */
					U4	xIE0_127					:1;				/* ECMIE0_127 */
				} stBit;
			} unECMINCFG0_3;										/* 0xFFD3804C */

			union												/* ECMINCFG0_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_128					:1;				/* ECMIE0_128 */
					U4	xIE0_129					:1;				/* ECMIE0_129 */
					U4	xIE0_130					:1;				/* ECMIE0_130 */
					U4	xIE0_131					:1;				/* ECMIE0_131 */
					U4	xIE0_132					:1;				/* ECMIE0_132 */
					U4	xIE0_133					:1;				/* ECMIE0_133 */
					U4	xIE0_134					:1;				/* ECMIE0_134 */
					U4	xIE0_135					:1;				/* ECMIE0_135 */
					U4	xIE0_136					:1;				/* ECMIE0_136 */
					U4	xIE0_137					:1;				/* ECMIE0_137 */
					U4	xIE0_138					:1;				/* ECMIE0_138 */
					U4	xIE0_139					:1;				/* ECMIE0_139 */
					U4	xIE0_140					:1;				/* ECMIE0_140 */
					U4	xIE0_141					:1;				/* ECMIE0_141 */
					U4	xIE0_142					:1;				/* ECMIE0_142 */
					U4	xIE0_143					:1;				/* ECMIE0_143 */
					U4	xIE0_144					:1;				/* ECMIE0_144 */
					U4	xIE0_145					:1;				/* ECMIE0_145 */
					U4	xIE0_146					:1;				/* ECMIE0_146 */
					U4	xIE0_147					:1;				/* ECMIE0_147 */
					U4	xIE0_148					:1;				/* ECMIE0_148 */
					U4	xIE0_149					:1;				/* ECMIE0_149 */
					U4	xIE0_150					:1;				/* ECMIE0_150 */
					U4	xIE0_151					:1;				/* ECMIE0_151 */
					U4	xIE0_152					:1;				/* ECMIE0_152 */
					U4	xIE0_153					:1;				/* ECMIE0_153 */
					U4	xIE0_154					:1;				/* ECMIE0_154 */
					U4	xIE0_155					:1;				/* ECMIE0_155 */
					U4	xIE0_156					:1;				/* ECMIE0_156 */
					U4	xIE0_157					:1;				/* ECMIE0_157 */
					U4	xIE0_158					:1;				/* ECMIE0_158 */
					U4	xIE0_159					:1;				/* ECMIE0_159 */
				} stBit;
			} unECMINCFG0_4;										/* 0xFFD38050 */

			union												/* ECMINCFG0_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_160					:1;				/* ECMIE0_160 */
					U4	xIE0_161					:1;				/* ECMIE0_161 */
					U4	xIE0_162					:1;				/* ECMIE0_162 */
					U4	xIE0_163					:1;				/* ECMIE0_163 */
					U4	xIE0_164					:1;				/* ECMIE0_164 */
					U4	xIE0_165					:1;				/* ECMIE0_165 */
					U4	xIE0_166					:1;				/* ECMIE0_166 */
					U4	xIE0_167					:1;				/* ECMIE0_167 */
					U4	xIE0_168					:1;				/* ECMIE0_168 */
					U4	xIE0_169					:1;				/* ECMIE0_169 */
					U4	xIE0_170					:1;				/* ECMIE0_170 */
					U4	xIE0_171					:1;				/* ECMIE0_171 */
					U4	xIE0_172					:1;				/* ECMIE0_172 */
					U4	xIE0_173					:1;				/* ECMIE0_173 */
					U4	xIE0_174					:1;				/* ECMIE0_174 */
					U4	xIE0_175					:1;				/* ECMIE0_175 */
					U4	xIE0_176					:1;				/* ECMIE0_176 */
					U4	xIE0_177					:1;				/* ECMIE0_177 */
					U4	xIE0_178					:1;				/* ECMIE0_178 */
					U4	xIE0_179					:1;				/* ECMIE0_179 */
					U4	xIE0_180					:1;				/* ECMIE0_180 */
					U4	xIE0_181					:1;				/* ECMIE0_181 */
					U4	xIE0_182					:1;				/* ECMIE0_182 */
					U4	xIE0_183					:1;				/* ECMIE0_183 */
					U4	xIE0_184					:1;				/* ECMIE0_184 */
					U4	xIE0_185					:1;				/* ECMIE0_185 */
					U4	xIE0_186					:1;				/* ECMIE0_186 */
					U4	xIE0_187					:1;				/* ECMIE0_187 */
					U4	xIE0_188					:1;				/* ECMIE0_188 */
					U4	xIE0_189					:1;				/* ECMIE0_189 */
					U4	xIE0_190					:1;				/* ECMIE0_190 */
					U4	xIE0_191					:1;				/* ECMIE0_191 */
				} stBit;
			} unECMINCFG0_5;										/* 0xFFD38054 */

			union												/* ECMINCFG0_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_192					:1;				/* ECMIE0_192 */
					U4	xIE0_193					:1;				/* ECMIE0_193 */
					U4	xIE0_194					:1;				/* ECMIE0_194 */
					U4	xIE0_195					:1;				/* ECMIE0_195 */
					U4	xIE0_196					:1;				/* ECMIE0_196 */
					U4	xIE0_197					:1;				/* ECMIE0_197 */
					U4	xIE0_198					:1;				/* ECMIE0_198 */
					U4	xIE0_199					:1;				/* ECMIE0_199 */
					U4	xIE0_200					:1;				/* ECMIE0_200 */
					U4	xIE0_201					:1;				/* ECMIE0_201 */
					U4	xIE0_202					:1;				/* ECMIE0_202 */
					U4	xIE0_203					:1;				/* ECMIE0_203 */
					U4	xIE0_204					:1;				/* ECMIE0_204 */
					U4	xIE0_205					:1;				/* ECMIE0_205 */
					U4	xIE0_206					:1;				/* ECMIE0_206 */
					U4	xIE0_207					:1;				/* ECMIE0_207 */
					U4	xIE0_208					:1;				/* ECMIE0_208 */
					U4	xIE0_209					:1;				/* ECMIE0_209 */
					U4	xIE0_210					:1;				/* ECMIE0_210 */
					U4	xIE0_211					:1;				/* ECMIE0_211 */
					U4	xIE0_212					:1;				/* ECMIE0_212 */
					U4	xIE0_213					:1;				/* ECMIE0_213 */
					U4	xIE0_214					:1;				/* ECMIE0_214 */
					U4	xIE0_215					:1;				/* ECMIE0_215 */
					U4	xIE0_216					:1;				/* ECMIE0_216 */
					U4	xIE0_217					:1;				/* ECMIE0_217 */
					U4	xIE0_218					:1;				/* ECMIE0_218 */
					U4	xIE0_219					:1;				/* ECMIE0_219 */
					U4	xIE0_220					:1;				/* ECMIE0_220 */
					U4	xIE0_221					:1;				/* ECMIE0_221 */
					U4	xIE0_222					:1;				/* ECMIE0_222 */
					U4	xIE0_223					:1;				/* ECMIE0_223 */
				} stBit;
			} unECMINCFG0_6;										/* 0xFFD38058 */

			union												/* ECMINCFG0_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_224					:1;				/* ECMIE0_224 */
					U4	xIE0_225					:1;				/* ECMIE0_225 */
					U4	xIE0_226					:1;				/* ECMIE0_226 */
					U4	xIE0_227					:1;				/* ECMIE0_227 */
					U4	xIE0_228					:1;				/* ECMIE0_228 */
					U4	xIE0_229					:1;				/* ECMIE0_229 */
					U4	xIE0_230					:1;				/* ECMIE0_230 */
					U4	xIE0_231					:1;				/* ECMIE0_231 */
					U4	xIE0_232					:1;				/* ECMIE0_232 */
					U4	xIE0_233					:1;				/* ECMIE0_233 */
					U4	xIE0_234					:1;				/* ECMIE0_234 */
					U4	xIE0_235					:1;				/* ECMIE0_235 */
					U4	xIE0_236					:1;				/* ECMIE0_236 */
					U4	xIE0_237					:1;				/* ECMIE0_237 */
					U4	xIE0_238					:1;				/* ECMIE0_238 */
					U4	xIE0_239					:1;				/* ECMIE0_239 */
					U4	xIE0_240					:1;				/* ECMIE0_240 */
					U4	xIE0_241					:1;				/* ECMIE0_241 */
					U4	xIE0_242					:1;				/* ECMIE0_242 */
					U4	xIE0_243					:1;				/* ECMIE0_243 */
					U4	xIE0_244					:1;				/* ECMIE0_244 */
					U4	xIE0_245					:1;				/* ECMIE0_245 */
					U4	xIE0_246					:1;				/* ECMIE0_246 */
					U4	xIE0_247					:1;				/* ECMIE0_247 */
					U4	xIE0_248					:1;				/* ECMIE0_248 */
					U4	xIE0_249					:1;				/* ECMIE0_249 */
					U4	xIE0_250					:1;				/* ECMIE0_250 */
					U4	xIE0_251					:1;				/* ECMIE0_251 */
					U4	xIE0_252					:1;				/* ECMIE0_252 */
					U4	xIE0_253					:1;				/* ECMIE0_253 */
					U4	xIE0_254					:1;				/* ECMIE0_254 */
					U4	xIE0_255					:1;				/* ECMIE0_255 */
				} stBit;
			} unECMINCFG0_7;										/* 0xFFD3805C */

			union												/* ECMINCFG0_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_256					:1;				/* ECMIE0_256 */
					U4	xIE0_257					:1;				/* ECMIE0_257 */
					U4	xIE0_258					:1;				/* ECMIE0_258 */
					U4	xIE0_259					:1;				/* ECMIE0_259 */
					U4	xIE0_260					:1;				/* ECMIE0_260 */
					U4	xIE0_261					:1;				/* ECMIE0_261 */
					U4	xIE0_262					:1;				/* ECMIE0_262 */
					U4	xIE0_263					:1;				/* ECMIE0_263 */
					U4	xIE0_264					:1;				/* ECMIE0_264 */
					U4	xIE0_265					:1;				/* ECMIE0_265 */
					U4	xIE0_266					:1;				/* ECMIE0_266 */
					U4	xIE0_267					:1;				/* ECMIE0_267 */
					U4	xIE0_268					:1;				/* ECMIE0_268 */
					U4	xIE0_269					:1;				/* ECMIE0_269 */
					U4	xIE0_270					:1;				/* ECMIE0_270 */
					U4	xIE0_271					:1;				/* ECMIE0_271 */
					U4	xIE0_272					:1;				/* ECMIE0_272 */
					U4	xIE0_273					:1;				/* ECMIE0_273 */
					U4	xIE0_274					:1;				/* ECMIE0_274 */
					U4	xIE0_275					:1;				/* ECMIE0_275 */
					U4	xIE0_276					:1;				/* ECMIE0_276 */
					U4	xIE0_277					:1;				/* ECMIE0_277 */
					U4	xIE0_278					:1;				/* ECMIE0_278 */
					U4	xIE0_279					:1;				/* ECMIE0_279 */
					U4	xIE0_280					:1;				/* ECMIE0_280 */
					U4	xIE0_281					:1;				/* ECMIE0_281 */
					U4	xIE0_282					:1;				/* ECMIE0_282 */
					U4	xIE0_283					:1;				/* ECMIE0_283 */
					U4	xIE0_284					:1;				/* ECMIE0_284 */
					U4	xIE0_285					:1;				/* ECMIE0_285 */
					U4	xIE0_286					:1;				/* ECMIE0_286 */
					U4	xIE0_287					:1;				/* ECMIE0_287 */
				} stBit;
			} unECMINCFG0_8;										/* 0xFFD38060 */

			union												/* ECMINCFG0_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_288					:1;				/* ECMIE0_288 */
					U4	xIE0_289					:1;				/* ECMIE0_289 */
					U4	xIE0_290					:1;				/* ECMIE0_290 */
					U4	xIE0_291					:1;				/* ECMIE0_291 */
					U4	xIE0_292					:1;				/* ECMIE0_292 */
					U4	xIE0_293					:1;				/* ECMIE0_293 */
					U4	xIE0_294					:1;				/* ECMIE0_294 */
					U4	xIE0_295					:1;				/* ECMIE0_295 */
					U4	xIE0_296					:1;				/* ECMIE0_296 */
					U4	xIE0_297					:1;				/* ECMIE0_297 */
					U4	xIE0_298					:1;				/* ECMIE0_298 */
					U4	xIE0_299					:1;				/* ECMIE0_299 */
					U4	xIE0_300					:1;				/* ECMIE0_300 */
					U4	xIE0_301					:1;				/* ECMIE0_301 */
					U4	xIE0_302					:1;				/* ECMIE0_302 */
					U4	xIE0_303					:1;				/* ECMIE0_303 */
					U4	xIE0_304					:1;				/* ECMIE0_304 */
					U4	xIE0_305					:1;				/* ECMIE0_305 */
					U4	xIE0_306					:1;				/* ECMIE0_306 */
					U4	xIE0_307					:1;				/* ECMIE0_307 */
					U4	xIE0_308					:1;				/* ECMIE0_308 */
					U4	xIE0_309					:1;				/* ECMIE0_309 */
					U4	xIE0_310					:1;				/* ECMIE0_310 */
					U4	xIE0_311					:1;				/* ECMIE0_311 */
					U4	xIE0_312					:1;				/* ECMIE0_312 */
					U4	xIE0_313					:1;				/* ECMIE0_313 */
					U4	xIE0_314					:1;				/* ECMIE0_314 */
					U4	xIE0_315					:1;				/* ECMIE0_315 */
					U4	xIE0_316					:1;				/* ECMIE0_316 */
					U4	xIE0_317					:1;				/* ECMIE0_317 */
					U4	xIE0_318					:1;				/* ECMIE0_318 */
					U4	xIE0_319					:1;				/* ECMIE0_319 */
				} stBit;
			} unECMINCFG0_9;										/* 0xFFD38064 */

			union												/* ECMINCFG0_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE0_320					:1;				/* ECMIE0_320 */
					U4	xIE0_321					:1;				/* ECMIE0_321 */
					U4	xIE0_322					:1;				/* ECMIE0_322 */
					U4	xIE0_323					:1;				/* ECMIE0_323 */
					U4	xIE0_324					:1;				/* ECMIE0_324 */
					U4	xIE0_325					:1;				/* ECMIE0_325 */
					U4	xIE0_326					:1;				/* ECMIE0_326 */
					U4	xIE0_327					:1;				/* ECMIE0_327 */
					U4	xIE0_328					:1;				/* ECMIE0_328 */
					U4	xIE0_329					:1;				/* ECMIE0_329 */
					U4	xIE0_330					:1;				/* ECMIE0_330 */
					U4	xIE0_331					:1;				/* ECMIE0_331 */
					U4	xIE0_332					:1;				/* ECMIE0_332 */
					U4	xIE0_333					:1;				/* ECMIE0_333 */
					U4	xIE0_334					:1;				/* ECMIE0_334 */
					U4	xIE0_335					:1;				/* ECMIE0_335 */
					U4	xIE0_336					:1;				/* ECMIE0_336 */
					U4	xIE0_337					:1;				/* ECMIE0_337 */
					U4	xIE0_338					:1;				/* ECMIE0_338 */
					U4	xIE0_339					:1;				/* ECMIE0_339 */
					U4	xIE0_340					:1;				/* ECMIE0_340 */
					U4	xIE0_341					:1;				/* ECMIE0_341 */
					U4	xIE0_342					:1;				/* ECMIE0_342 */
					U4	xIE0_343					:1;				/* ECMIE0_343 */
					U4	xIE0_344					:1;				/* ECMIE0_344 */
					U4	xIE0_345					:1;				/* ECMIE0_345 */
					U4	xIE0_346					:1;				/* ECMIE0_346 */
					U4	xIE0_347					:1;				/* ECMIE0_347 */
					U4	xIE0_348					:1;				/* ECMIE0_348 */
					U4	xIE0_349					:1;				/* ECMIE0_349 */
					U4	xIE0_350					:1;				/* ECMIE0_350 */
					U4	xIE0_351					:1;				/* ECMIE0_351 */
				} stBit;
			} unECMINCFG0_10;										/* 0xFFD38068 */
		} stECMINCFG0_n;
	} unECMINCFG0_n;

	U1	u1Dummy2[16];	/* 0xFFD3806C - 0xFFD3807B */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMINCFG1_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_000					:1;				/* ECMIE1_000 */
					U4	xIE1_001					:1;				/* ECMIE1_001 */
					U4	xIE1_002					:1;				/* ECMIE1_002 */
					U4	xIE1_003					:1;				/* ECMIE1_003 */
					U4	xIE1_004					:1;				/* ECMIE1_004 */
					U4	xIE1_005					:1;				/* ECMIE1_005 */
					U4	xIE1_006					:1;				/* ECMIE1_006 */
					U4	xIE1_007					:1;				/* ECMIE1_007 */
					U4	xIE1_008					:1;				/* ECMIE1_008 */
					U4	xIE1_009					:1;				/* ECMIE1_009 */
					U4	xIE1_010					:1;				/* ECMIE1_010 */
					U4	xIE1_011					:1;				/* ECMIE1_011 */
					U4	xIE1_012					:1;				/* ECMIE1_012 */
					U4	xIE1_013					:1;				/* ECMIE1_013 */
					U4	xIE1_014					:1;				/* ECMIE1_014 */
					U4	xIE1_015					:1;				/* ECMIE1_015 */
					U4	xIE1_016					:1;				/* ECMIE1_016 */
					U4	xIE1_017					:1;				/* ECMIE1_017 */
					U4	xIE1_018					:1;				/* ECMIE1_018 */
					U4	xIE1_019					:1;				/* ECMIE1_019 */
					U4	xIE1_020					:1;				/* ECMIE1_020 */
					U4	xIE1_021					:1;				/* ECMIE1_021 */
					U4	xIE1_022					:1;				/* ECMIE1_022 */
					U4	xIE1_023					:1;				/* ECMIE1_023 */
					U4	xIE1_024					:1;				/* ECMIE1_024 */
					U4	xIE1_025					:1;				/* ECMIE1_025 */
					U4	xIE1_026					:1;				/* ECMIE1_026 */
					U4	xIE1_027					:1;				/* ECMIE1_027 */
					U4	xIE1_028					:1;				/* ECMIE1_028 */
					U4	xIE1_029					:1;				/* ECMIE1_029 */
					U4	xIE1_030					:1;				/* ECMIE1_030 */
					U4	xIE1_031					:1;				/* ECMIE1_031 */
				} stBit;
			} unECMINCFG1_0;										/* 0xFFD3807C */

			union												/* ECMINCFG1_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_032					:1;				/* ECMIE1_032 */
					U4	xIE1_033					:1;				/* ECMIE1_033 */
					U4	xIE1_034					:1;				/* ECMIE1_034 */
					U4	xIE1_035					:1;				/* ECMIE1_035 */
					U4	xIE1_036					:1;				/* ECMIE1_036 */
					U4	xIE1_037					:1;				/* ECMIE1_037 */
					U4	xIE1_038					:1;				/* ECMIE1_038 */
					U4	xIE1_039					:1;				/* ECMIE1_039 */
					U4	xIE1_040					:1;				/* ECMIE1_040 */
					U4	xIE1_041					:1;				/* ECMIE1_041 */
					U4	xIE1_042					:1;				/* ECMIE1_042 */
					U4	xIE1_043					:1;				/* ECMIE1_043 */
					U4	xIE1_044					:1;				/* ECMIE1_044 */
					U4	xIE1_045					:1;				/* ECMIE1_045 */
					U4	xIE1_046					:1;				/* ECMIE1_046 */
					U4	xIE1_047					:1;				/* ECMIE1_047 */
					U4	xIE1_048					:1;				/* ECMIE1_048 */
					U4	xIE1_049					:1;				/* ECMIE1_049 */
					U4	xIE1_050					:1;				/* ECMIE1_050 */
					U4	xIE1_051					:1;				/* ECMIE1_051 */
					U4	xIE1_052					:1;				/* ECMIE1_052 */
					U4	xIE1_053					:1;				/* ECMIE1_053 */
					U4	xIE1_054					:1;				/* ECMIE1_054 */
					U4	xIE1_055					:1;				/* ECMIE1_055 */
					U4	xIE1_056					:1;				/* ECMIE1_056 */
					U4	xIE1_057					:1;				/* ECMIE1_057 */
					U4	xIE1_058					:1;				/* ECMIE1_058 */
					U4	xIE1_059					:1;				/* ECMIE1_059 */
					U4	xIE1_060					:1;				/* ECMIE1_060 */
					U4	xIE1_061					:1;				/* ECMIE1_061 */
					U4	xIE1_062					:1;				/* ECMIE1_062 */
					U4	xIE1_063					:1;				/* ECMIE1_063 */
				} stBit;
			} unECMINCFG1_1;										/* 0xFFD38080 */

			union												/* ECMINCFG1_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_064					:1;				/* ECMIE1_064 */
					U4	xIE1_065					:1;				/* ECMIE1_065 */
					U4	xIE1_066					:1;				/* ECMIE1_066 */
					U4	xIE1_067					:1;				/* ECMIE1_067 */
					U4	xIE1_068					:1;				/* ECMIE1_068 */
					U4	xIE1_069					:1;				/* ECMIE1_069 */
					U4	xIE1_070					:1;				/* ECMIE1_070 */
					U4	xIE1_071					:1;				/* ECMIE1_071 */
					U4	xIE1_072					:1;				/* ECMIE1_072 */
					U4	xIE1_073					:1;				/* ECMIE1_073 */
					U4	xIE1_074					:1;				/* ECMIE1_074 */
					U4	xIE1_075					:1;				/* ECMIE1_075 */
					U4	xIE1_076					:1;				/* ECMIE1_076 */
					U4	xIE1_077					:1;				/* ECMIE1_077 */
					U4	xIE1_078					:1;				/* ECMIE1_078 */
					U4	xIE1_079					:1;				/* ECMIE1_079 */
					U4	xIE1_080					:1;				/* ECMIE1_080 */
					U4	xIE1_081					:1;				/* ECMIE1_081 */
					U4	xIE1_082					:1;				/* ECMIE1_082 */
					U4	xIE1_083					:1;				/* ECMIE1_083 */
					U4	xIE1_084					:1;				/* ECMIE1_084 */
					U4	xIE1_085					:1;				/* ECMIE1_085 */
					U4	xIE1_086					:1;				/* ECMIE1_086 */
					U4	xIE1_087					:1;				/* ECMIE1_087 */
					U4	xIE1_088					:1;				/* ECMIE1_088 */
					U4	xIE1_089					:1;				/* ECMIE1_089 */
					U4	xIE1_090					:1;				/* ECMIE1_090 */
					U4	xIE1_091					:1;				/* ECMIE1_091 */
					U4	xIE1_092					:1;				/* ECMIE1_092 */
					U4	xIE1_093					:1;				/* ECMIE1_093 */
					U4	xIE1_094					:1;				/* ECMIE1_094 */
					U4	xIE1_095					:1;				/* ECMIE1_095 */
				} stBit;
			} unECMINCFG1_2;										/* 0xFFD38084 */

			union												/* ECMINCFG1_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_096					:1;				/* ECMIE1_096 */
					U4	xIE1_097					:1;				/* ECMIE1_097 */
					U4	xIE1_098					:1;				/* ECMIE1_098 */
					U4	xIE1_099					:1;				/* ECMIE1_099 */
					U4	xIE1_100					:1;				/* ECMIE1_100 */
					U4	xIE1_101					:1;				/* ECMIE1_101 */
					U4	xIE1_102					:1;				/* ECMIE1_102 */
					U4	xIE1_103					:1;				/* ECMIE1_103 */
					U4	xIE1_104					:1;				/* ECMIE1_104 */
					U4	xIE1_105					:1;				/* ECMIE1_105 */
					U4	xIE1_106					:1;				/* ECMIE1_106 */
					U4	xIE1_107					:1;				/* ECMIE1_107 */
					U4	xIE1_108					:1;				/* ECMIE1_108 */
					U4	xIE1_109					:1;				/* ECMIE1_109 */
					U4	xIE1_110					:1;				/* ECMIE1_110 */
					U4	xIE1_111					:1;				/* ECMIE1_111 */
					U4	xIE1_112					:1;				/* ECMIE1_112 */
					U4	xIE1_113					:1;				/* ECMIE1_113 */
					U4	xIE1_114					:1;				/* ECMIE1_114 */
					U4	xIE1_115					:1;				/* ECMIE1_115 */
					U4	xIE1_116					:1;				/* ECMIE1_116 */
					U4	xIE1_117					:1;				/* ECMIE1_117 */
					U4	xIE1_118					:1;				/* ECMIE1_118 */
					U4	xIE1_119					:1;				/* ECMIE1_119 */
					U4	xIE1_120					:1;				/* ECMIE1_120 */
					U4	xIE1_121					:1;				/* ECMIE1_121 */
					U4	xIE1_122					:1;				/* ECMIE1_122 */
					U4	xIE1_123					:1;				/* ECMIE1_123 */
					U4	xIE1_124					:1;				/* ECMIE1_124 */
					U4	xIE1_125					:1;				/* ECMIE1_125 */
					U4	xIE1_126					:1;				/* ECMIE1_126 */
					U4	xIE1_127					:1;				/* ECMIE1_127 */
				} stBit;
			} unECMINCFG1_3;										/* 0xFFD38088 */

			union												/* ECMINCFG1_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_128					:1;				/* ECMIE1_128 */
					U4	xIE1_129					:1;				/* ECMIE1_129 */
					U4	xIE1_130					:1;				/* ECMIE1_130 */
					U4	xIE1_131					:1;				/* ECMIE1_131 */
					U4	xIE1_132					:1;				/* ECMIE1_132 */
					U4	xIE1_133					:1;				/* ECMIE1_133 */
					U4	xIE1_134					:1;				/* ECMIE1_134 */
					U4	xIE1_135					:1;				/* ECMIE1_135 */
					U4	xIE1_136					:1;				/* ECMIE1_136 */
					U4	xIE1_137					:1;				/* ECMIE1_137 */
					U4	xIE1_138					:1;				/* ECMIE1_138 */
					U4	xIE1_139					:1;				/* ECMIE1_139 */
					U4	xIE1_140					:1;				/* ECMIE1_140 */
					U4	xIE1_141					:1;				/* ECMIE1_141 */
					U4	xIE1_142					:1;				/* ECMIE1_142 */
					U4	xIE1_143					:1;				/* ECMIE1_143 */
					U4	xIE1_144					:1;				/* ECMIE1_144 */
					U4	xIE1_145					:1;				/* ECMIE1_145 */
					U4	xIE1_146					:1;				/* ECMIE1_146 */
					U4	xIE1_147					:1;				/* ECMIE1_147 */
					U4	xIE1_148					:1;				/* ECMIE1_148 */
					U4	xIE1_149					:1;				/* ECMIE1_149 */
					U4	xIE1_150					:1;				/* ECMIE1_150 */
					U4	xIE1_151					:1;				/* ECMIE1_151 */
					U4	xIE1_152					:1;				/* ECMIE1_152 */
					U4	xIE1_153					:1;				/* ECMIE1_153 */
					U4	xIE1_154					:1;				/* ECMIE1_154 */
					U4	xIE1_155					:1;				/* ECMIE1_155 */
					U4	xIE1_156					:1;				/* ECMIE1_156 */
					U4	xIE1_157					:1;				/* ECMIE1_157 */
					U4	xIE1_158					:1;				/* ECMIE1_158 */
					U4	xIE1_159					:1;				/* ECMIE1_159 */
				} stBit;
			} unECMINCFG1_4;										/* 0xFFD3808C */

			union												/* ECMINCFG1_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_160					:1;				/* ECMIE1_160 */
					U4	xIE1_161					:1;				/* ECMIE1_161 */
					U4	xIE1_162					:1;				/* ECMIE1_162 */
					U4	xIE1_163					:1;				/* ECMIE1_163 */
					U4	xIE1_164					:1;				/* ECMIE1_164 */
					U4	xIE1_165					:1;				/* ECMIE1_165 */
					U4	xIE1_166					:1;				/* ECMIE1_166 */
					U4	xIE1_167					:1;				/* ECMIE1_167 */
					U4	xIE1_168					:1;				/* ECMIE1_168 */
					U4	xIE1_169					:1;				/* ECMIE1_169 */
					U4	xIE1_170					:1;				/* ECMIE1_170 */
					U4	xIE1_171					:1;				/* ECMIE1_171 */
					U4	xIE1_172					:1;				/* ECMIE1_172 */
					U4	xIE1_173					:1;				/* ECMIE1_173 */
					U4	xIE1_174					:1;				/* ECMIE1_174 */
					U4	xIE1_175					:1;				/* ECMIE1_175 */
					U4	xIE1_176					:1;				/* ECMIE1_176 */
					U4	xIE1_177					:1;				/* ECMIE1_177 */
					U4	xIE1_178					:1;				/* ECMIE1_178 */
					U4	xIE1_179					:1;				/* ECMIE1_179 */
					U4	xIE1_180					:1;				/* ECMIE1_180 */
					U4	xIE1_181					:1;				/* ECMIE1_181 */
					U4	xIE1_182					:1;				/* ECMIE1_182 */
					U4	xIE1_183					:1;				/* ECMIE1_183 */
					U4	xIE1_184					:1;				/* ECMIE1_184 */
					U4	xIE1_185					:1;				/* ECMIE1_185 */
					U4	xIE1_186					:1;				/* ECMIE1_186 */
					U4	xIE1_187					:1;				/* ECMIE1_187 */
					U4	xIE1_188					:1;				/* ECMIE1_188 */
					U4	xIE1_189					:1;				/* ECMIE1_189 */
					U4	xIE1_190					:1;				/* ECMIE1_190 */
					U4	xIE1_191					:1;				/* ECMIE1_191 */
				} stBit;
			} unECMINCFG1_5;										/* 0xFFD38090 */

			union												/* ECMINCFG1_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_192					:1;				/* ECMIE1_192 */
					U4	xIE1_193					:1;				/* ECMIE1_193 */
					U4	xIE1_194					:1;				/* ECMIE1_194 */
					U4	xIE1_195					:1;				/* ECMIE1_195 */
					U4	xIE1_196					:1;				/* ECMIE1_196 */
					U4	xIE1_197					:1;				/* ECMIE1_197 */
					U4	xIE1_198					:1;				/* ECMIE1_198 */
					U4	xIE1_199					:1;				/* ECMIE1_199 */
					U4	xIE1_200					:1;				/* ECMIE1_200 */
					U4	xIE1_201					:1;				/* ECMIE1_201 */
					U4	xIE1_202					:1;				/* ECMIE1_202 */
					U4	xIE1_203					:1;				/* ECMIE1_203 */
					U4	xIE1_204					:1;				/* ECMIE1_204 */
					U4	xIE1_205					:1;				/* ECMIE1_205 */
					U4	xIE1_206					:1;				/* ECMIE1_206 */
					U4	xIE1_207					:1;				/* ECMIE1_207 */
					U4	xIE1_208					:1;				/* ECMIE1_208 */
					U4	xIE1_209					:1;				/* ECMIE1_209 */
					U4	xIE1_210					:1;				/* ECMIE1_210 */
					U4	xIE1_211					:1;				/* ECMIE1_211 */
					U4	xIE1_212					:1;				/* ECMIE1_212 */
					U4	xIE1_213					:1;				/* ECMIE1_213 */
					U4	xIE1_214					:1;				/* ECMIE1_214 */
					U4	xIE1_215					:1;				/* ECMIE1_215 */
					U4	xIE1_216					:1;				/* ECMIE1_216 */
					U4	xIE1_217					:1;				/* ECMIE1_217 */
					U4	xIE1_218					:1;				/* ECMIE1_218 */
					U4	xIE1_219					:1;				/* ECMIE1_219 */
					U4	xIE1_220					:1;				/* ECMIE1_220 */
					U4	xIE1_221					:1;				/* ECMIE1_221 */
					U4	xIE1_222					:1;				/* ECMIE1_222 */
					U4	xIE1_223					:1;				/* ECMIE1_223 */
				} stBit;
			} unECMINCFG1_6;										/* 0xFFD38094 */

			union												/* ECMINCFG1_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_224					:1;				/* ECMIE1_224 */
					U4	xIE1_225					:1;				/* ECMIE1_225 */
					U4	xIE1_226					:1;				/* ECMIE1_226 */
					U4	xIE1_227					:1;				/* ECMIE1_227 */
					U4	xIE1_228					:1;				/* ECMIE1_228 */
					U4	xIE1_229					:1;				/* ECMIE1_229 */
					U4	xIE1_230					:1;				/* ECMIE1_230 */
					U4	xIE1_231					:1;				/* ECMIE1_231 */
					U4	xIE1_232					:1;				/* ECMIE1_232 */
					U4	xIE1_233					:1;				/* ECMIE1_233 */
					U4	xIE1_234					:1;				/* ECMIE1_234 */
					U4	xIE1_235					:1;				/* ECMIE1_235 */
					U4	xIE1_236					:1;				/* ECMIE1_236 */
					U4	xIE1_237					:1;				/* ECMIE1_237 */
					U4	xIE1_238					:1;				/* ECMIE1_238 */
					U4	xIE1_239					:1;				/* ECMIE1_239 */
					U4	xIE1_240					:1;				/* ECMIE1_240 */
					U4	xIE1_241					:1;				/* ECMIE1_241 */
					U4	xIE1_242					:1;				/* ECMIE1_242 */
					U4	xIE1_243					:1;				/* ECMIE1_243 */
					U4	xIE1_244					:1;				/* ECMIE1_244 */
					U4	xIE1_245					:1;				/* ECMIE1_245 */
					U4	xIE1_246					:1;				/* ECMIE1_246 */
					U4	xIE1_247					:1;				/* ECMIE1_247 */
					U4	xIE1_248					:1;				/* ECMIE1_248 */
					U4	xIE1_249					:1;				/* ECMIE1_249 */
					U4	xIE1_250					:1;				/* ECMIE1_250 */
					U4	xIE1_251					:1;				/* ECMIE1_251 */
					U4	xIE1_252					:1;				/* ECMIE1_252 */
					U4	xIE1_253					:1;				/* ECMIE1_253 */
					U4	xIE1_254					:1;				/* ECMIE1_254 */
					U4	xIE1_255					:1;				/* ECMIE1_255 */
				} stBit;
			} unECMINCFG1_7;										/* 0xFFD38098 */

			union												/* ECMINCFG1_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_256					:1;				/* ECMIE1_256 */
					U4	xIE1_257					:1;				/* ECMIE1_257 */
					U4	xIE1_258					:1;				/* ECMIE1_258 */
					U4	xIE1_259					:1;				/* ECMIE1_259 */
					U4	xIE1_260					:1;				/* ECMIE1_260 */
					U4	xIE1_261					:1;				/* ECMIE1_261 */
					U4	xIE1_262					:1;				/* ECMIE1_262 */
					U4	xIE1_263					:1;				/* ECMIE1_263 */
					U4	xIE1_264					:1;				/* ECMIE1_264 */
					U4	xIE1_265					:1;				/* ECMIE1_265 */
					U4	xIE1_266					:1;				/* ECMIE1_266 */
					U4	xIE1_267					:1;				/* ECMIE1_267 */
					U4	xIE1_268					:1;				/* ECMIE1_268 */
					U4	xIE1_269					:1;				/* ECMIE1_269 */
					U4	xIE1_270					:1;				/* ECMIE1_270 */
					U4	xIE1_271					:1;				/* ECMIE1_271 */
					U4	xIE1_272					:1;				/* ECMIE1_272 */
					U4	xIE1_273					:1;				/* ECMIE1_273 */
					U4	xIE1_274					:1;				/* ECMIE1_274 */
					U4	xIE1_275					:1;				/* ECMIE1_275 */
					U4	xIE1_276					:1;				/* ECMIE1_276 */
					U4	xIE1_277					:1;				/* ECMIE1_277 */
					U4	xIE1_278					:1;				/* ECMIE1_278 */
					U4	xIE1_279					:1;				/* ECMIE1_279 */
					U4	xIE1_280					:1;				/* ECMIE1_280 */
					U4	xIE1_281					:1;				/* ECMIE1_281 */
					U4	xIE1_282					:1;				/* ECMIE1_282 */
					U4	xIE1_283					:1;				/* ECMIE1_283 */
					U4	xIE1_284					:1;				/* ECMIE1_284 */
					U4	xIE1_285					:1;				/* ECMIE1_285 */
					U4	xIE1_286					:1;				/* ECMIE1_286 */
					U4	xIE1_287					:1;				/* ECMIE1_287 */
				} stBit;
			} unECMINCFG1_8;										/* 0xFFD3809C */

			union												/* ECMINCFG1_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_288					:1;				/* ECMIE1_288 */
					U4	xIE1_289					:1;				/* ECMIE1_289 */
					U4	xIE1_290					:1;				/* ECMIE1_290 */
					U4	xIE1_291					:1;				/* ECMIE1_291 */
					U4	xIE1_292					:1;				/* ECMIE1_292 */
					U4	xIE1_293					:1;				/* ECMIE1_293 */
					U4	xIE1_294					:1;				/* ECMIE1_294 */
					U4	xIE1_295					:1;				/* ECMIE1_295 */
					U4	xIE1_296					:1;				/* ECMIE1_296 */
					U4	xIE1_297					:1;				/* ECMIE1_297 */
					U4	xIE1_298					:1;				/* ECMIE1_298 */
					U4	xIE1_299					:1;				/* ECMIE1_299 */
					U4	xIE1_300					:1;				/* ECMIE1_300 */
					U4	xIE1_301					:1;				/* ECMIE1_301 */
					U4	xIE1_302					:1;				/* ECMIE1_302 */
					U4	xIE1_303					:1;				/* ECMIE1_303 */
					U4	xIE1_304					:1;				/* ECMIE1_304 */
					U4	xIE1_305					:1;				/* ECMIE1_305 */
					U4	xIE1_306					:1;				/* ECMIE1_306 */
					U4	xIE1_307					:1;				/* ECMIE1_307 */
					U4	xIE1_308					:1;				/* ECMIE1_308 */
					U4	xIE1_309					:1;				/* ECMIE1_309 */
					U4	xIE1_310					:1;				/* ECMIE1_310 */
					U4	xIE1_311					:1;				/* ECMIE1_311 */
					U4	xIE1_312					:1;				/* ECMIE1_312 */
					U4	xIE1_313					:1;				/* ECMIE1_313 */
					U4	xIE1_314					:1;				/* ECMIE1_314 */
					U4	xIE1_315					:1;				/* ECMIE1_315 */
					U4	xIE1_316					:1;				/* ECMIE1_316 */
					U4	xIE1_317					:1;				/* ECMIE1_317 */
					U4	xIE1_318					:1;				/* ECMIE1_318 */
					U4	xIE1_319					:1;				/* ECMIE1_319 */
				} stBit;
			} unECMINCFG1_9;										/* 0xFFD380A0 */

			union												/* ECMINCFG1_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE1_320					:1;				/* ECMIE1_320 */
					U4	xIE1_321					:1;				/* ECMIE1_321 */
					U4	xIE1_322					:1;				/* ECMIE1_322 */
					U4	xIE1_323					:1;				/* ECMIE1_323 */
					U4	xIE1_324					:1;				/* ECMIE1_324 */
					U4	xIE1_325					:1;				/* ECMIE1_325 */
					U4	xIE1_326					:1;				/* ECMIE1_326 */
					U4	xIE1_327					:1;				/* ECMIE1_327 */
					U4	xIE1_328					:1;				/* ECMIE1_328 */
					U4	xIE1_329					:1;				/* ECMIE1_329 */
					U4	xIE1_330					:1;				/* ECMIE1_330 */
					U4	xIE1_331					:1;				/* ECMIE1_331 */
					U4	xIE1_332					:1;				/* ECMIE1_332 */
					U4	xIE1_333					:1;				/* ECMIE1_333 */
					U4	xIE1_334					:1;				/* ECMIE1_334 */
					U4	xIE1_335					:1;				/* ECMIE1_335 */
					U4	xIE1_336					:1;				/* ECMIE1_336 */
					U4	xIE1_337					:1;				/* ECMIE1_337 */
					U4	xIE1_338					:1;				/* ECMIE1_338 */
					U4	xIE1_339					:1;				/* ECMIE1_339 */
					U4	xIE1_340					:1;				/* ECMIE1_340 */
					U4	xIE1_341					:1;				/* ECMIE1_341 */
					U4	xIE1_342					:1;				/* ECMIE1_342 */
					U4	xIE1_343					:1;				/* ECMIE1_343 */
					U4	xIE1_344					:1;				/* ECMIE1_344 */
					U4	xIE1_345					:1;				/* ECMIE1_345 */
					U4	xIE1_346					:1;				/* ECMIE1_346 */
					U4	xIE1_347					:1;				/* ECMIE1_347 */
					U4	xIE1_348					:1;				/* ECMIE1_348 */
					U4	xIE1_349					:1;				/* ECMIE1_349 */
					U4	xIE1_350					:1;				/* ECMIE1_350 */
					U4	xIE1_351					:1;				/* ECMIE1_351 */
				} stBit;
			} unECMINCFG1_10;										/* 0xFFD380A4 */
		} stECMINCFG1_n;
	} unECMINCFG1_n;

	U1	u1Dummy3[16];	/* 0xFFD380A8 - 0xFFD380B7 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMINCFG2_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_000					:1;				/* ECMIE2_000 */
					U4	xIE2_001					:1;				/* ECMIE2_001 */
					U4	xIE2_002					:1;				/* ECMIE2_002 */
					U4	xIE2_003					:1;				/* ECMIE2_003 */
					U4	xIE2_004					:1;				/* ECMIE2_004 */
					U4	xIE2_005					:1;				/* ECMIE2_005 */
					U4	xIE2_006					:1;				/* ECMIE2_006 */
					U4	xIE2_007					:1;				/* ECMIE2_007 */
					U4	xIE2_008					:1;				/* ECMIE2_008 */
					U4	xIE2_009					:1;				/* ECMIE2_009 */
					U4	xIE2_010					:1;				/* ECMIE2_010 */
					U4	xIE2_011					:1;				/* ECMIE2_011 */
					U4	xIE2_012					:1;				/* ECMIE2_012 */
					U4	xIE2_013					:1;				/* ECMIE2_013 */
					U4	xIE2_014					:1;				/* ECMIE2_014 */
					U4	xIE2_015					:1;				/* ECMIE2_015 */
					U4	xIE2_016					:1;				/* ECMIE2_016 */
					U4	xIE2_017					:1;				/* ECMIE2_017 */
					U4	xIE2_018					:1;				/* ECMIE2_018 */
					U4	xIE2_019					:1;				/* ECMIE2_019 */
					U4	xIE2_020					:1;				/* ECMIE2_020 */
					U4	xIE2_021					:1;				/* ECMIE2_021 */
					U4	xIE2_022					:1;				/* ECMIE2_022 */
					U4	xIE2_023					:1;				/* ECMIE2_023 */
					U4	xIE2_024					:1;				/* ECMIE2_024 */
					U4	xIE2_025					:1;				/* ECMIE2_025 */
					U4	xIE2_026					:1;				/* ECMIE2_026 */
					U4	xIE2_027					:1;				/* ECMIE2_027 */
					U4	xIE2_028					:1;				/* ECMIE2_028 */
					U4	xIE2_029					:1;				/* ECMIE2_029 */
					U4	xIE2_030					:1;				/* ECMIE2_030 */
					U4	xIE2_031					:1;				/* ECMIE2_031 */
				} stBit;
			} unECMINCFG2_0;										/* 0xFFD380B8 */

			union												/* ECMINCFG2_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_032					:1;				/* ECMIE2_032 */
					U4	xIE2_033					:1;				/* ECMIE2_033 */
					U4	xIE2_034					:1;				/* ECMIE2_034 */
					U4	xIE2_035					:1;				/* ECMIE2_035 */
					U4	xIE2_036					:1;				/* ECMIE2_036 */
					U4	xIE2_037					:1;				/* ECMIE2_037 */
					U4	xIE2_038					:1;				/* ECMIE2_038 */
					U4	xIE2_039					:1;				/* ECMIE2_039 */
					U4	xIE2_040					:1;				/* ECMIE2_040 */
					U4	xIE2_041					:1;				/* ECMIE2_041 */
					U4	xIE2_042					:1;				/* ECMIE2_042 */
					U4	xIE2_043					:1;				/* ECMIE2_043 */
					U4	xIE2_044					:1;				/* ECMIE2_044 */
					U4	xIE2_045					:1;				/* ECMIE2_045 */
					U4	xIE2_046					:1;				/* ECMIE2_046 */
					U4	xIE2_047					:1;				/* ECMIE2_047 */
					U4	xIE2_048					:1;				/* ECMIE2_048 */
					U4	xIE2_049					:1;				/* ECMIE2_049 */
					U4	xIE2_050					:1;				/* ECMIE2_050 */
					U4	xIE2_051					:1;				/* ECMIE2_051 */
					U4	xIE2_052					:1;				/* ECMIE2_052 */
					U4	xIE2_053					:1;				/* ECMIE2_053 */
					U4	xIE2_054					:1;				/* ECMIE2_054 */
					U4	xIE2_055					:1;				/* ECMIE2_055 */
					U4	xIE2_056					:1;				/* ECMIE2_056 */
					U4	xIE2_057					:1;				/* ECMIE2_057 */
					U4	xIE2_058					:1;				/* ECMIE2_058 */
					U4	xIE2_059					:1;				/* ECMIE2_059 */
					U4	xIE2_060					:1;				/* ECMIE2_060 */
					U4	xIE2_061					:1;				/* ECMIE2_061 */
					U4	xIE2_062					:1;				/* ECMIE2_062 */
					U4	xIE2_063					:1;				/* ECMIE2_063 */
				} stBit;
			} unECMINCFG2_1;										/* 0xFFD380BC */

			union												/* ECMINCFG2_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_064					:1;				/* ECMIE2_064 */
					U4	xIE2_065					:1;				/* ECMIE2_065 */
					U4	xIE2_066					:1;				/* ECMIE2_066 */
					U4	xIE2_067					:1;				/* ECMIE2_067 */
					U4	xIE2_068					:1;				/* ECMIE2_068 */
					U4	xIE2_069					:1;				/* ECMIE2_069 */
					U4	xIE2_070					:1;				/* ECMIE2_070 */
					U4	xIE2_071					:1;				/* ECMIE2_071 */
					U4	xIE2_072					:1;				/* ECMIE2_072 */
					U4	xIE2_073					:1;				/* ECMIE2_073 */
					U4	xIE2_074					:1;				/* ECMIE2_074 */
					U4	xIE2_075					:1;				/* ECMIE2_075 */
					U4	xIE2_076					:1;				/* ECMIE2_076 */
					U4	xIE2_077					:1;				/* ECMIE2_077 */
					U4	xIE2_078					:1;				/* ECMIE2_078 */
					U4	xIE2_079					:1;				/* ECMIE2_079 */
					U4	xIE2_080					:1;				/* ECMIE2_080 */
					U4	xIE2_081					:1;				/* ECMIE2_081 */
					U4	xIE2_082					:1;				/* ECMIE2_082 */
					U4	xIE2_083					:1;				/* ECMIE2_083 */
					U4	xIE2_084					:1;				/* ECMIE2_084 */
					U4	xIE2_085					:1;				/* ECMIE2_085 */
					U4	xIE2_086					:1;				/* ECMIE2_086 */
					U4	xIE2_087					:1;				/* ECMIE2_087 */
					U4	xIE2_088					:1;				/* ECMIE2_088 */
					U4	xIE2_089					:1;				/* ECMIE2_089 */
					U4	xIE2_090					:1;				/* ECMIE2_090 */
					U4	xIE2_091					:1;				/* ECMIE2_091 */
					U4	xIE2_092					:1;				/* ECMIE2_092 */
					U4	xIE2_093					:1;				/* ECMIE2_093 */
					U4	xIE2_094					:1;				/* ECMIE2_094 */
					U4	xIE2_095					:1;				/* ECMIE2_095 */
				} stBit;
			} unECMINCFG2_2;										/* 0xFFD380C0 */

			union												/* ECMINCFG2_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_096					:1;				/* ECMIE2_096 */
					U4	xIE2_097					:1;				/* ECMIE2_097 */
					U4	xIE2_098					:1;				/* ECMIE2_098 */
					U4	xIE2_099					:1;				/* ECMIE2_099 */
					U4	xIE2_100					:1;				/* ECMIE2_100 */
					U4	xIE2_101					:1;				/* ECMIE2_101 */
					U4	xIE2_102					:1;				/* ECMIE2_102 */
					U4	xIE2_103					:1;				/* ECMIE2_103 */
					U4	xIE2_104					:1;				/* ECMIE2_104 */
					U4	xIE2_105					:1;				/* ECMIE2_105 */
					U4	xIE2_106					:1;				/* ECMIE2_106 */
					U4	xIE2_107					:1;				/* ECMIE2_107 */
					U4	xIE2_108					:1;				/* ECMIE2_108 */
					U4	xIE2_109					:1;				/* ECMIE2_109 */
					U4	xIE2_110					:1;				/* ECMIE2_110 */
					U4	xIE2_111					:1;				/* ECMIE2_111 */
					U4	xIE2_112					:1;				/* ECMIE2_112 */
					U4	xIE2_113					:1;				/* ECMIE2_113 */
					U4	xIE2_114					:1;				/* ECMIE2_114 */
					U4	xIE2_115					:1;				/* ECMIE2_115 */
					U4	xIE2_116					:1;				/* ECMIE2_116 */
					U4	xIE2_117					:1;				/* ECMIE2_117 */
					U4	xIE2_118					:1;				/* ECMIE2_118 */
					U4	xIE2_119					:1;				/* ECMIE2_119 */
					U4	xIE2_120					:1;				/* ECMIE2_120 */
					U4	xIE2_121					:1;				/* ECMIE2_121 */
					U4	xIE2_122					:1;				/* ECMIE2_122 */
					U4	xIE2_123					:1;				/* ECMIE2_123 */
					U4	xIE2_124					:1;				/* ECMIE2_124 */
					U4	xIE2_125					:1;				/* ECMIE2_125 */
					U4	xIE2_126					:1;				/* ECMIE2_126 */
					U4	xIE2_127					:1;				/* ECMIE2_127 */
				} stBit;
			} unECMINCFG2_3;										/* 0xFFD380C4 */

			union												/* ECMINCFG2_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_128					:1;				/* ECMIE2_128 */
					U4	xIE2_129					:1;				/* ECMIE2_129 */
					U4	xIE2_130					:1;				/* ECMIE2_130 */
					U4	xIE2_131					:1;				/* ECMIE2_131 */
					U4	xIE2_132					:1;				/* ECMIE2_132 */
					U4	xIE2_133					:1;				/* ECMIE2_133 */
					U4	xIE2_134					:1;				/* ECMIE2_134 */
					U4	xIE2_135					:1;				/* ECMIE2_135 */
					U4	xIE2_136					:1;				/* ECMIE2_136 */
					U4	xIE2_137					:1;				/* ECMIE2_137 */
					U4	xIE2_138					:1;				/* ECMIE2_138 */
					U4	xIE2_139					:1;				/* ECMIE2_139 */
					U4	xIE2_140					:1;				/* ECMIE2_140 */
					U4	xIE2_141					:1;				/* ECMIE2_141 */
					U4	xIE2_142					:1;				/* ECMIE2_142 */
					U4	xIE2_143					:1;				/* ECMIE2_143 */
					U4	xIE2_144					:1;				/* ECMIE2_144 */
					U4	xIE2_145					:1;				/* ECMIE2_145 */
					U4	xIE2_146					:1;				/* ECMIE2_146 */
					U4	xIE2_147					:1;				/* ECMIE2_147 */
					U4	xIE2_148					:1;				/* ECMIE2_148 */
					U4	xIE2_149					:1;				/* ECMIE2_149 */
					U4	xIE2_150					:1;				/* ECMIE2_150 */
					U4	xIE2_151					:1;				/* ECMIE2_151 */
					U4	xIE2_152					:1;				/* ECMIE2_152 */
					U4	xIE2_153					:1;				/* ECMIE2_153 */
					U4	xIE2_154					:1;				/* ECMIE2_154 */
					U4	xIE2_155					:1;				/* ECMIE2_155 */
					U4	xIE2_156					:1;				/* ECMIE2_156 */
					U4	xIE2_157					:1;				/* ECMIE2_157 */
					U4	xIE2_158					:1;				/* ECMIE2_158 */
					U4	xIE2_159					:1;				/* ECMIE2_159 */
				} stBit;
			} unECMINCFG2_4;										/* 0xFFD380C8 */

			union												/* ECMINCFG2_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_160					:1;				/* ECMIE2_160 */
					U4	xIE2_161					:1;				/* ECMIE2_161 */
					U4	xIE2_162					:1;				/* ECMIE2_162 */
					U4	xIE2_163					:1;				/* ECMIE2_163 */
					U4	xIE2_164					:1;				/* ECMIE2_164 */
					U4	xIE2_165					:1;				/* ECMIE2_165 */
					U4	xIE2_166					:1;				/* ECMIE2_166 */
					U4	xIE2_167					:1;				/* ECMIE2_167 */
					U4	xIE2_168					:1;				/* ECMIE2_168 */
					U4	xIE2_169					:1;				/* ECMIE2_169 */
					U4	xIE2_170					:1;				/* ECMIE2_170 */
					U4	xIE2_171					:1;				/* ECMIE2_171 */
					U4	xIE2_172					:1;				/* ECMIE2_172 */
					U4	xIE2_173					:1;				/* ECMIE2_173 */
					U4	xIE2_174					:1;				/* ECMIE2_174 */
					U4	xIE2_175					:1;				/* ECMIE2_175 */
					U4	xIE2_176					:1;				/* ECMIE2_176 */
					U4	xIE2_177					:1;				/* ECMIE2_177 */
					U4	xIE2_178					:1;				/* ECMIE2_178 */
					U4	xIE2_179					:1;				/* ECMIE2_179 */
					U4	xIE2_180					:1;				/* ECMIE2_180 */
					U4	xIE2_181					:1;				/* ECMIE2_181 */
					U4	xIE2_182					:1;				/* ECMIE2_182 */
					U4	xIE2_183					:1;				/* ECMIE2_183 */
					U4	xIE2_184					:1;				/* ECMIE2_184 */
					U4	xIE2_185					:1;				/* ECMIE2_185 */
					U4	xIE2_186					:1;				/* ECMIE2_186 */
					U4	xIE2_187					:1;				/* ECMIE2_187 */
					U4	xIE2_188					:1;				/* ECMIE2_188 */
					U4	xIE2_189					:1;				/* ECMIE2_189 */
					U4	xIE2_190					:1;				/* ECMIE2_190 */
					U4	xIE2_191					:1;				/* ECMIE2_191 */
				} stBit;
			} unECMINCFG2_5;										/* 0xFFD380CC */

			union												/* ECMINCFG2_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_192					:1;				/* ECMIE2_192 */
					U4	xIE2_193					:1;				/* ECMIE2_193 */
					U4	xIE2_194					:1;				/* ECMIE2_194 */
					U4	xIE2_195					:1;				/* ECMIE2_195 */
					U4	xIE2_196					:1;				/* ECMIE2_196 */
					U4	xIE2_197					:1;				/* ECMIE2_197 */
					U4	xIE2_198					:1;				/* ECMIE2_198 */
					U4	xIE2_199					:1;				/* ECMIE2_199 */
					U4	xIE2_200					:1;				/* ECMIE2_200 */
					U4	xIE2_201					:1;				/* ECMIE2_201 */
					U4	xIE2_202					:1;				/* ECMIE2_202 */
					U4	xIE2_203					:1;				/* ECMIE2_203 */
					U4	xIE2_204					:1;				/* ECMIE2_204 */
					U4	xIE2_205					:1;				/* ECMIE2_205 */
					U4	xIE2_206					:1;				/* ECMIE2_206 */
					U4	xIE2_207					:1;				/* ECMIE2_207 */
					U4	xIE2_208					:1;				/* ECMIE2_208 */
					U4	xIE2_209					:1;				/* ECMIE2_209 */
					U4	xIE2_210					:1;				/* ECMIE2_210 */
					U4	xIE2_211					:1;				/* ECMIE2_211 */
					U4	xIE2_212					:1;				/* ECMIE2_212 */
					U4	xIE2_213					:1;				/* ECMIE2_213 */
					U4	xIE2_214					:1;				/* ECMIE2_214 */
					U4	xIE2_215					:1;				/* ECMIE2_215 */
					U4	xIE2_216					:1;				/* ECMIE2_216 */
					U4	xIE2_217					:1;				/* ECMIE2_217 */
					U4	xIE2_218					:1;				/* ECMIE2_218 */
					U4	xIE2_219					:1;				/* ECMIE2_219 */
					U4	xIE2_220					:1;				/* ECMIE2_220 */
					U4	xIE2_221					:1;				/* ECMIE2_221 */
					U4	xIE2_222					:1;				/* ECMIE2_222 */
					U4	xIE2_223					:1;				/* ECMIE2_223 */
				} stBit;
			} unECMINCFG2_6;										/* 0xFFD380D0 */

			union												/* ECMINCFG2_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_224					:1;				/* ECMIE2_224 */
					U4	xIE2_225					:1;				/* ECMIE2_225 */
					U4	xIE2_226					:1;				/* ECMIE2_226 */
					U4	xIE2_227					:1;				/* ECMIE2_227 */
					U4	xIE2_228					:1;				/* ECMIE2_228 */
					U4	xIE2_229					:1;				/* ECMIE2_229 */
					U4	xIE2_230					:1;				/* ECMIE2_230 */
					U4	xIE2_231					:1;				/* ECMIE2_231 */
					U4	xIE2_232					:1;				/* ECMIE2_232 */
					U4	xIE2_233					:1;				/* ECMIE2_233 */
					U4	xIE2_234					:1;				/* ECMIE2_234 */
					U4	xIE2_235					:1;				/* ECMIE2_235 */
					U4	xIE2_236					:1;				/* ECMIE2_236 */
					U4	xIE2_237					:1;				/* ECMIE2_237 */
					U4	xIE2_238					:1;				/* ECMIE2_238 */
					U4	xIE2_239					:1;				/* ECMIE2_239 */
					U4	xIE2_240					:1;				/* ECMIE2_240 */
					U4	xIE2_241					:1;				/* ECMIE2_241 */
					U4	xIE2_242					:1;				/* ECMIE2_242 */
					U4	xIE2_243					:1;				/* ECMIE2_243 */
					U4	xIE2_244					:1;				/* ECMIE2_244 */
					U4	xIE2_245					:1;				/* ECMIE2_245 */
					U4	xIE2_246					:1;				/* ECMIE2_246 */
					U4	xIE2_247					:1;				/* ECMIE2_247 */
					U4	xIE2_248					:1;				/* ECMIE2_248 */
					U4	xIE2_249					:1;				/* ECMIE2_249 */
					U4	xIE2_250					:1;				/* ECMIE2_250 */
					U4	xIE2_251					:1;				/* ECMIE2_251 */
					U4	xIE2_252					:1;				/* ECMIE2_252 */
					U4	xIE2_253					:1;				/* ECMIE2_253 */
					U4	xIE2_254					:1;				/* ECMIE2_254 */
					U4	xIE2_255					:1;				/* ECMIE2_255 */
				} stBit;
			} unECMINCFG2_7;										/* 0xFFD380D4 */

			union												/* ECMINCFG2_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_256					:1;				/* ECMIE2_256 */
					U4	xIE2_257					:1;				/* ECMIE2_257 */
					U4	xIE2_258					:1;				/* ECMIE2_258 */
					U4	xIE2_259					:1;				/* ECMIE2_259 */
					U4	xIE2_260					:1;				/* ECMIE2_260 */
					U4	xIE2_261					:1;				/* ECMIE2_261 */
					U4	xIE2_262					:1;				/* ECMIE2_262 */
					U4	xIE2_263					:1;				/* ECMIE2_263 */
					U4	xIE2_264					:1;				/* ECMIE2_264 */
					U4	xIE2_265					:1;				/* ECMIE2_265 */
					U4	xIE2_266					:1;				/* ECMIE2_266 */
					U4	xIE2_267					:1;				/* ECMIE2_267 */
					U4	xIE2_268					:1;				/* ECMIE2_268 */
					U4	xIE2_269					:1;				/* ECMIE2_269 */
					U4	xIE2_270					:1;				/* ECMIE2_270 */
					U4	xIE2_271					:1;				/* ECMIE2_271 */
					U4	xIE2_272					:1;				/* ECMIE2_272 */
					U4	xIE2_273					:1;				/* ECMIE2_273 */
					U4	xIE2_274					:1;				/* ECMIE2_274 */
					U4	xIE2_275					:1;				/* ECMIE2_275 */
					U4	xIE2_276					:1;				/* ECMIE2_276 */
					U4	xIE2_277					:1;				/* ECMIE2_277 */
					U4	xIE2_278					:1;				/* ECMIE2_278 */
					U4	xIE2_279					:1;				/* ECMIE2_279 */
					U4	xIE2_280					:1;				/* ECMIE2_280 */
					U4	xIE2_281					:1;				/* ECMIE2_281 */
					U4	xIE2_282					:1;				/* ECMIE2_282 */
					U4	xIE2_283					:1;				/* ECMIE2_283 */
					U4	xIE2_284					:1;				/* ECMIE2_284 */
					U4	xIE2_285					:1;				/* ECMIE2_285 */
					U4	xIE2_286					:1;				/* ECMIE2_286 */
					U4	xIE2_287					:1;				/* ECMIE2_287 */
				} stBit;
			} unECMINCFG2_8;										/* 0xFFD380D8 */

			union												/* ECMINCFG2_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_288					:1;				/* ECMIE2_288 */
					U4	xIE2_289					:1;				/* ECMIE2_289 */
					U4	xIE2_290					:1;				/* ECMIE2_290 */
					U4	xIE2_291					:1;				/* ECMIE2_291 */
					U4	xIE2_292					:1;				/* ECMIE2_292 */
					U4	xIE2_293					:1;				/* ECMIE2_293 */
					U4	xIE2_294					:1;				/* ECMIE2_294 */
					U4	xIE2_295					:1;				/* ECMIE2_295 */
					U4	xIE2_296					:1;				/* ECMIE2_296 */
					U4	xIE2_297					:1;				/* ECMIE2_297 */
					U4	xIE2_298					:1;				/* ECMIE2_298 */
					U4	xIE2_299					:1;				/* ECMIE2_299 */
					U4	xIE2_300					:1;				/* ECMIE2_300 */
					U4	xIE2_301					:1;				/* ECMIE2_301 */
					U4	xIE2_302					:1;				/* ECMIE2_302 */
					U4	xIE2_303					:1;				/* ECMIE2_303 */
					U4	xIE2_304					:1;				/* ECMIE2_304 */
					U4	xIE2_305					:1;				/* ECMIE2_305 */
					U4	xIE2_306					:1;				/* ECMIE2_306 */
					U4	xIE2_307					:1;				/* ECMIE2_307 */
					U4	xIE2_308					:1;				/* ECMIE2_308 */
					U4	xIE2_309					:1;				/* ECMIE2_309 */
					U4	xIE2_310					:1;				/* ECMIE2_310 */
					U4	xIE2_311					:1;				/* ECMIE2_311 */
					U4	xIE2_312					:1;				/* ECMIE2_312 */
					U4	xIE2_313					:1;				/* ECMIE2_313 */
					U4	xIE2_314					:1;				/* ECMIE2_314 */
					U4	xIE2_315					:1;				/* ECMIE2_315 */
					U4	xIE2_316					:1;				/* ECMIE2_316 */
					U4	xIE2_317					:1;				/* ECMIE2_317 */
					U4	xIE2_318					:1;				/* ECMIE2_318 */
					U4	xIE2_319					:1;				/* ECMIE2_319 */
				} stBit;
			} unECMINCFG2_9;										/* 0xFFD380DC */

			union												/* ECMINCFG2_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE2_320					:1;				/* ECMIE2_320 */
					U4	xIE2_321					:1;				/* ECMIE2_321 */
					U4	xIE2_322					:1;				/* ECMIE2_322 */
					U4	xIE2_323					:1;				/* ECMIE2_323 */
					U4	xIE2_324					:1;				/* ECMIE2_324 */
					U4	xIE2_325					:1;				/* ECMIE2_325 */
					U4	xIE2_326					:1;				/* ECMIE2_326 */
					U4	xIE2_327					:1;				/* ECMIE2_327 */
					U4	xIE2_328					:1;				/* ECMIE2_328 */
					U4	xIE2_329					:1;				/* ECMIE2_329 */
					U4	xIE2_330					:1;				/* ECMIE2_330 */
					U4	xIE2_331					:1;				/* ECMIE2_331 */
					U4	xIE2_332					:1;				/* ECMIE2_332 */
					U4	xIE2_333					:1;				/* ECMIE2_333 */
					U4	xIE2_334					:1;				/* ECMIE2_334 */
					U4	xIE2_335					:1;				/* ECMIE2_335 */
					U4	xIE2_336					:1;				/* ECMIE2_336 */
					U4	xIE2_337					:1;				/* ECMIE2_337 */
					U4	xIE2_338					:1;				/* ECMIE2_338 */
					U4	xIE2_339					:1;				/* ECMIE2_339 */
					U4	xIE2_340					:1;				/* ECMIE2_340 */
					U4	xIE2_341					:1;				/* ECMIE2_341 */
					U4	xIE2_342					:1;				/* ECMIE2_342 */
					U4	xIE2_343					:1;				/* ECMIE2_343 */
					U4	xIE2_344					:1;				/* ECMIE2_344 */
					U4	xIE2_345					:1;				/* ECMIE2_345 */
					U4	xIE2_346					:1;				/* ECMIE2_346 */
					U4	xIE2_347					:1;				/* ECMIE2_347 */
					U4	xIE2_348					:1;				/* ECMIE2_348 */
					U4	xIE2_349					:1;				/* ECMIE2_349 */
					U4	xIE2_350					:1;				/* ECMIE2_350 */
					U4	xIE2_351					:1;				/* ECMIE2_351 */
				} stBit;
			} unECMINCFG2_10;										/* 0xFFD380E0 */
		} stECMINCFG2_n;
	} unECMINCFG2_n;

	U1	u1Dummy4[16];	/* 0xFFD380E4 - 0xFFD380F3 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMINCFG3_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_000					:1;				/* ECMIE3_000 */
					U4	xIE3_001					:1;				/* ECMIE3_001 */
					U4	xIE3_002					:1;				/* ECMIE3_002 */
					U4	xIE3_003					:1;				/* ECMIE3_003 */
					U4	xIE3_004					:1;				/* ECMIE3_004 */
					U4	xIE3_005					:1;				/* ECMIE3_005 */
					U4	xIE3_006					:1;				/* ECMIE3_006 */
					U4	xIE3_007					:1;				/* ECMIE3_007 */
					U4	xIE3_008					:1;				/* ECMIE3_008 */
					U4	xIE3_009					:1;				/* ECMIE3_009 */
					U4	xIE3_010					:1;				/* ECMIE3_010 */
					U4	xIE3_011					:1;				/* ECMIE3_011 */
					U4	xIE3_012					:1;				/* ECMIE3_012 */
					U4	xIE3_013					:1;				/* ECMIE3_013 */
					U4	xIE3_014					:1;				/* ECMIE3_014 */
					U4	xIE3_015					:1;				/* ECMIE3_015 */
					U4	xIE3_016					:1;				/* ECMIE3_016 */
					U4	xIE3_017					:1;				/* ECMIE3_017 */
					U4	xIE3_018					:1;				/* ECMIE3_018 */
					U4	xIE3_019					:1;				/* ECMIE3_019 */
					U4	xIE3_020					:1;				/* ECMIE3_020 */
					U4	xIE3_021					:1;				/* ECMIE3_021 */
					U4	xIE3_022					:1;				/* ECMIE3_022 */
					U4	xIE3_023					:1;				/* ECMIE3_023 */
					U4	xIE3_024					:1;				/* ECMIE3_024 */
					U4	xIE3_025					:1;				/* ECMIE3_025 */
					U4	xIE3_026					:1;				/* ECMIE3_026 */
					U4	xIE3_027					:1;				/* ECMIE3_027 */
					U4	xIE3_028					:1;				/* ECMIE3_028 */
					U4	xIE3_029					:1;				/* ECMIE3_029 */
					U4	xIE3_030					:1;				/* ECMIE3_030 */
					U4	xIE3_031					:1;				/* ECMIE3_031 */
				} stBit;
			} unECMINCFG3_0;										/* 0xFFD380F4 */

			union												/* ECMINCFG3_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_032					:1;				/* ECMIE3_032 */
					U4	xIE3_033					:1;				/* ECMIE3_033 */
					U4	xIE3_034					:1;				/* ECMIE3_034 */
					U4	xIE3_035					:1;				/* ECMIE3_035 */
					U4	xIE3_036					:1;				/* ECMIE3_036 */
					U4	xIE3_037					:1;				/* ECMIE3_037 */
					U4	xIE3_038					:1;				/* ECMIE3_038 */
					U4	xIE3_039					:1;				/* ECMIE3_039 */
					U4	xIE3_040					:1;				/* ECMIE3_040 */
					U4	xIE3_041					:1;				/* ECMIE3_041 */
					U4	xIE3_042					:1;				/* ECMIE3_042 */
					U4	xIE3_043					:1;				/* ECMIE3_043 */
					U4	xIE3_044					:1;				/* ECMIE3_044 */
					U4	xIE3_045					:1;				/* ECMIE3_045 */
					U4	xIE3_046					:1;				/* ECMIE3_046 */
					U4	xIE3_047					:1;				/* ECMIE3_047 */
					U4	xIE3_048					:1;				/* ECMIE3_048 */
					U4	xIE3_049					:1;				/* ECMIE3_049 */
					U4	xIE3_050					:1;				/* ECMIE3_050 */
					U4	xIE3_051					:1;				/* ECMIE3_051 */
					U4	xIE3_052					:1;				/* ECMIE3_052 */
					U4	xIE3_053					:1;				/* ECMIE3_053 */
					U4	xIE3_054					:1;				/* ECMIE3_054 */
					U4	xIE3_055					:1;				/* ECMIE3_055 */
					U4	xIE3_056					:1;				/* ECMIE3_056 */
					U4	xIE3_057					:1;				/* ECMIE3_057 */
					U4	xIE3_058					:1;				/* ECMIE3_058 */
					U4	xIE3_059					:1;				/* ECMIE3_059 */
					U4	xIE3_060					:1;				/* ECMIE3_060 */
					U4	xIE3_061					:1;				/* ECMIE3_061 */
					U4	xIE3_062					:1;				/* ECMIE3_062 */
					U4	xIE3_063					:1;				/* ECMIE3_063 */
				} stBit;
			} unECMINCFG3_1;										/* 0xFFD380F8 */

			union												/* ECMINCFG3_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_064					:1;				/* ECMIE3_064 */
					U4	xIE3_065					:1;				/* ECMIE3_065 */
					U4	xIE3_066					:1;				/* ECMIE3_066 */
					U4	xIE3_067					:1;				/* ECMIE3_067 */
					U4	xIE3_068					:1;				/* ECMIE3_068 */
					U4	xIE3_069					:1;				/* ECMIE3_069 */
					U4	xIE3_070					:1;				/* ECMIE3_070 */
					U4	xIE3_071					:1;				/* ECMIE3_071 */
					U4	xIE3_072					:1;				/* ECMIE3_072 */
					U4	xIE3_073					:1;				/* ECMIE3_073 */
					U4	xIE3_074					:1;				/* ECMIE3_074 */
					U4	xIE3_075					:1;				/* ECMIE3_075 */
					U4	xIE3_076					:1;				/* ECMIE3_076 */
					U4	xIE3_077					:1;				/* ECMIE3_077 */
					U4	xIE3_078					:1;				/* ECMIE3_078 */
					U4	xIE3_079					:1;				/* ECMIE3_079 */
					U4	xIE3_080					:1;				/* ECMIE3_080 */
					U4	xIE3_081					:1;				/* ECMIE3_081 */
					U4	xIE3_082					:1;				/* ECMIE3_082 */
					U4	xIE3_083					:1;				/* ECMIE3_083 */
					U4	xIE3_084					:1;				/* ECMIE3_084 */
					U4	xIE3_085					:1;				/* ECMIE3_085 */
					U4	xIE3_086					:1;				/* ECMIE3_086 */
					U4	xIE3_087					:1;				/* ECMIE3_087 */
					U4	xIE3_088					:1;				/* ECMIE3_088 */
					U4	xIE3_089					:1;				/* ECMIE3_089 */
					U4	xIE3_090					:1;				/* ECMIE3_090 */
					U4	xIE3_091					:1;				/* ECMIE3_091 */
					U4	xIE3_092					:1;				/* ECMIE3_092 */
					U4	xIE3_093					:1;				/* ECMIE3_093 */
					U4	xIE3_094					:1;				/* ECMIE3_094 */
					U4	xIE3_095					:1;				/* ECMIE3_095 */
				} stBit;
			} unECMINCFG3_2;										/* 0xFFD380FC */

			union												/* ECMINCFG3_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_096					:1;				/* ECMIE3_096 */
					U4	xIE3_097					:1;				/* ECMIE3_097 */
					U4	xIE3_098					:1;				/* ECMIE3_098 */
					U4	xIE3_099					:1;				/* ECMIE3_099 */
					U4	xIE3_100					:1;				/* ECMIE3_100 */
					U4	xIE3_101					:1;				/* ECMIE3_101 */
					U4	xIE3_102					:1;				/* ECMIE3_102 */
					U4	xIE3_103					:1;				/* ECMIE3_103 */
					U4	xIE3_104					:1;				/* ECMIE3_104 */
					U4	xIE3_105					:1;				/* ECMIE3_105 */
					U4	xIE3_106					:1;				/* ECMIE3_106 */
					U4	xIE3_107					:1;				/* ECMIE3_107 */
					U4	xIE3_108					:1;				/* ECMIE3_108 */
					U4	xIE3_109					:1;				/* ECMIE3_109 */
					U4	xIE3_110					:1;				/* ECMIE3_110 */
					U4	xIE3_111					:1;				/* ECMIE3_111 */
					U4	xIE3_112					:1;				/* ECMIE3_112 */
					U4	xIE3_113					:1;				/* ECMIE3_113 */
					U4	xIE3_114					:1;				/* ECMIE3_114 */
					U4	xIE3_115					:1;				/* ECMIE3_115 */
					U4	xIE3_116					:1;				/* ECMIE3_116 */
					U4	xIE3_117					:1;				/* ECMIE3_117 */
					U4	xIE3_118					:1;				/* ECMIE3_118 */
					U4	xIE3_119					:1;				/* ECMIE3_119 */
					U4	xIE3_120					:1;				/* ECMIE3_120 */
					U4	xIE3_121					:1;				/* ECMIE3_121 */
					U4	xIE3_122					:1;				/* ECMIE3_122 */
					U4	xIE3_123					:1;				/* ECMIE3_123 */
					U4	xIE3_124					:1;				/* ECMIE3_124 */
					U4	xIE3_125					:1;				/* ECMIE3_125 */
					U4	xIE3_126					:1;				/* ECMIE3_126 */
					U4	xIE3_127					:1;				/* ECMIE3_127 */
				} stBit;
			} unECMINCFG3_3;										/* 0xFFD38100 */

			union												/* ECMINCFG3_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_128					:1;				/* ECMIE3_128 */
					U4	xIE3_129					:1;				/* ECMIE3_129 */
					U4	xIE3_130					:1;				/* ECMIE3_130 */
					U4	xIE3_131					:1;				/* ECMIE3_131 */
					U4	xIE3_132					:1;				/* ECMIE3_132 */
					U4	xIE3_133					:1;				/* ECMIE3_133 */
					U4	xIE3_134					:1;				/* ECMIE3_134 */
					U4	xIE3_135					:1;				/* ECMIE3_135 */
					U4	xIE3_136					:1;				/* ECMIE3_136 */
					U4	xIE3_137					:1;				/* ECMIE3_137 */
					U4	xIE3_138					:1;				/* ECMIE3_138 */
					U4	xIE3_139					:1;				/* ECMIE3_139 */
					U4	xIE3_140					:1;				/* ECMIE3_140 */
					U4	xIE3_141					:1;				/* ECMIE3_141 */
					U4	xIE3_142					:1;				/* ECMIE3_142 */
					U4	xIE3_143					:1;				/* ECMIE3_143 */
					U4	xIE3_144					:1;				/* ECMIE3_144 */
					U4	xIE3_145					:1;				/* ECMIE3_145 */
					U4	xIE3_146					:1;				/* ECMIE3_146 */
					U4	xIE3_147					:1;				/* ECMIE3_147 */
					U4	xIE3_148					:1;				/* ECMIE3_148 */
					U4	xIE3_149					:1;				/* ECMIE3_149 */
					U4	xIE3_150					:1;				/* ECMIE3_150 */
					U4	xIE3_151					:1;				/* ECMIE3_151 */
					U4	xIE3_152					:1;				/* ECMIE3_152 */
					U4	xIE3_153					:1;				/* ECMIE3_153 */
					U4	xIE3_154					:1;				/* ECMIE3_154 */
					U4	xIE3_155					:1;				/* ECMIE3_155 */
					U4	xIE3_156					:1;				/* ECMIE3_156 */
					U4	xIE3_157					:1;				/* ECMIE3_157 */
					U4	xIE3_158					:1;				/* ECMIE3_158 */
					U4	xIE3_159					:1;				/* ECMIE3_159 */
				} stBit;
			} unECMINCFG3_4;										/* 0xFFD38104 */

			union												/* ECMINCFG3_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_160					:1;				/* ECMIE3_160 */
					U4	xIE3_161					:1;				/* ECMIE3_161 */
					U4	xIE3_162					:1;				/* ECMIE3_162 */
					U4	xIE3_163					:1;				/* ECMIE3_163 */
					U4	xIE3_164					:1;				/* ECMIE3_164 */
					U4	xIE3_165					:1;				/* ECMIE3_165 */
					U4	xIE3_166					:1;				/* ECMIE3_166 */
					U4	xIE3_167					:1;				/* ECMIE3_167 */
					U4	xIE3_168					:1;				/* ECMIE3_168 */
					U4	xIE3_169					:1;				/* ECMIE3_169 */
					U4	xIE3_170					:1;				/* ECMIE3_170 */
					U4	xIE3_171					:1;				/* ECMIE3_171 */
					U4	xIE3_172					:1;				/* ECMIE3_172 */
					U4	xIE3_173					:1;				/* ECMIE3_173 */
					U4	xIE3_174					:1;				/* ECMIE3_174 */
					U4	xIE3_175					:1;				/* ECMIE3_175 */
					U4	xIE3_176					:1;				/* ECMIE3_176 */
					U4	xIE3_177					:1;				/* ECMIE3_177 */
					U4	xIE3_178					:1;				/* ECMIE3_178 */
					U4	xIE3_179					:1;				/* ECMIE3_179 */
					U4	xIE3_180					:1;				/* ECMIE3_180 */
					U4	xIE3_181					:1;				/* ECMIE3_181 */
					U4	xIE3_182					:1;				/* ECMIE3_182 */
					U4	xIE3_183					:1;				/* ECMIE3_183 */
					U4	xIE3_184					:1;				/* ECMIE3_184 */
					U4	xIE3_185					:1;				/* ECMIE3_185 */
					U4	xIE3_186					:1;				/* ECMIE3_186 */
					U4	xIE3_187					:1;				/* ECMIE3_187 */
					U4	xIE3_188					:1;				/* ECMIE3_188 */
					U4	xIE3_189					:1;				/* ECMIE3_189 */
					U4	xIE3_190					:1;				/* ECMIE3_190 */
					U4	xIE3_191					:1;				/* ECMIE3_191 */
				} stBit;
			} unECMINCFG3_5;										/* 0xFFD38108 */

			union												/* ECMINCFG3_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_192					:1;				/* ECMIE3_192 */
					U4	xIE3_193					:1;				/* ECMIE3_193 */
					U4	xIE3_194					:1;				/* ECMIE3_194 */
					U4	xIE3_195					:1;				/* ECMIE3_195 */
					U4	xIE3_196					:1;				/* ECMIE3_196 */
					U4	xIE3_197					:1;				/* ECMIE3_197 */
					U4	xIE3_198					:1;				/* ECMIE3_198 */
					U4	xIE3_199					:1;				/* ECMIE3_199 */
					U4	xIE3_200					:1;				/* ECMIE3_200 */
					U4	xIE3_201					:1;				/* ECMIE3_201 */
					U4	xIE3_202					:1;				/* ECMIE3_202 */
					U4	xIE3_203					:1;				/* ECMIE3_203 */
					U4	xIE3_204					:1;				/* ECMIE3_204 */
					U4	xIE3_205					:1;				/* ECMIE3_205 */
					U4	xIE3_206					:1;				/* ECMIE3_206 */
					U4	xIE3_207					:1;				/* ECMIE3_207 */
					U4	xIE3_208					:1;				/* ECMIE3_208 */
					U4	xIE3_209					:1;				/* ECMIE3_209 */
					U4	xIE3_210					:1;				/* ECMIE3_210 */
					U4	xIE3_211					:1;				/* ECMIE3_211 */
					U4	xIE3_212					:1;				/* ECMIE3_212 */
					U4	xIE3_213					:1;				/* ECMIE3_213 */
					U4	xIE3_214					:1;				/* ECMIE3_214 */
					U4	xIE3_215					:1;				/* ECMIE3_215 */
					U4	xIE3_216					:1;				/* ECMIE3_216 */
					U4	xIE3_217					:1;				/* ECMIE3_217 */
					U4	xIE3_218					:1;				/* ECMIE3_218 */
					U4	xIE3_219					:1;				/* ECMIE3_219 */
					U4	xIE3_220					:1;				/* ECMIE3_220 */
					U4	xIE3_221					:1;				/* ECMIE3_221 */
					U4	xIE3_222					:1;				/* ECMIE3_222 */
					U4	xIE3_223					:1;				/* ECMIE3_223 */
				} stBit;
			} unECMINCFG3_6;										/* 0xFFD3810C */

			union												/* ECMINCFG3_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_224					:1;				/* ECMIE3_224 */
					U4	xIE3_225					:1;				/* ECMIE3_225 */
					U4	xIE3_226					:1;				/* ECMIE3_226 */
					U4	xIE3_227					:1;				/* ECMIE3_227 */
					U4	xIE3_228					:1;				/* ECMIE3_228 */
					U4	xIE3_229					:1;				/* ECMIE3_229 */
					U4	xIE3_230					:1;				/* ECMIE3_230 */
					U4	xIE3_231					:1;				/* ECMIE3_231 */
					U4	xIE3_232					:1;				/* ECMIE3_232 */
					U4	xIE3_233					:1;				/* ECMIE3_233 */
					U4	xIE3_234					:1;				/* ECMIE3_234 */
					U4	xIE3_235					:1;				/* ECMIE3_235 */
					U4	xIE3_236					:1;				/* ECMIE3_236 */
					U4	xIE3_237					:1;				/* ECMIE3_237 */
					U4	xIE3_238					:1;				/* ECMIE3_238 */
					U4	xIE3_239					:1;				/* ECMIE3_239 */
					U4	xIE3_240					:1;				/* ECMIE3_240 */
					U4	xIE3_241					:1;				/* ECMIE3_241 */
					U4	xIE3_242					:1;				/* ECMIE3_242 */
					U4	xIE3_243					:1;				/* ECMIE3_243 */
					U4	xIE3_244					:1;				/* ECMIE3_244 */
					U4	xIE3_245					:1;				/* ECMIE3_245 */
					U4	xIE3_246					:1;				/* ECMIE3_246 */
					U4	xIE3_247					:1;				/* ECMIE3_247 */
					U4	xIE3_248					:1;				/* ECMIE3_248 */
					U4	xIE3_249					:1;				/* ECMIE3_249 */
					U4	xIE3_250					:1;				/* ECMIE3_250 */
					U4	xIE3_251					:1;				/* ECMIE3_251 */
					U4	xIE3_252					:1;				/* ECMIE3_252 */
					U4	xIE3_253					:1;				/* ECMIE3_253 */
					U4	xIE3_254					:1;				/* ECMIE3_254 */
					U4	xIE3_255					:1;				/* ECMIE3_255 */
				} stBit;
			} unECMINCFG3_7;										/* 0xFFD38110 */

			union												/* ECMINCFG3_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_256					:1;				/* ECMIE3_256 */
					U4	xIE3_257					:1;				/* ECMIE3_257 */
					U4	xIE3_258					:1;				/* ECMIE3_258 */
					U4	xIE3_259					:1;				/* ECMIE3_259 */
					U4	xIE3_260					:1;				/* ECMIE3_260 */
					U4	xIE3_261					:1;				/* ECMIE3_261 */
					U4	xIE3_262					:1;				/* ECMIE3_262 */
					U4	xIE3_263					:1;				/* ECMIE3_263 */
					U4	xIE3_264					:1;				/* ECMIE3_264 */
					U4	xIE3_265					:1;				/* ECMIE3_265 */
					U4	xIE3_266					:1;				/* ECMIE3_266 */
					U4	xIE3_267					:1;				/* ECMIE3_267 */
					U4	xIE3_268					:1;				/* ECMIE3_268 */
					U4	xIE3_269					:1;				/* ECMIE3_269 */
					U4	xIE3_270					:1;				/* ECMIE3_270 */
					U4	xIE3_271					:1;				/* ECMIE3_271 */
					U4	xIE3_272					:1;				/* ECMIE3_272 */
					U4	xIE3_273					:1;				/* ECMIE3_273 */
					U4	xIE3_274					:1;				/* ECMIE3_274 */
					U4	xIE3_275					:1;				/* ECMIE3_275 */
					U4	xIE3_276					:1;				/* ECMIE3_276 */
					U4	xIE3_277					:1;				/* ECMIE3_277 */
					U4	xIE3_278					:1;				/* ECMIE3_278 */
					U4	xIE3_279					:1;				/* ECMIE3_279 */
					U4	xIE3_280					:1;				/* ECMIE3_280 */
					U4	xIE3_281					:1;				/* ECMIE3_281 */
					U4	xIE3_282					:1;				/* ECMIE3_282 */
					U4	xIE3_283					:1;				/* ECMIE3_283 */
					U4	xIE3_284					:1;				/* ECMIE3_284 */
					U4	xIE3_285					:1;				/* ECMIE3_285 */
					U4	xIE3_286					:1;				/* ECMIE3_286 */
					U4	xIE3_287					:1;				/* ECMIE3_287 */
				} stBit;
			} unECMINCFG3_8;										/* 0xFFD38114 */

			union												/* ECMINCFG3_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_288					:1;				/* ECMIE3_288 */
					U4	xIE3_289					:1;				/* ECMIE3_289 */
					U4	xIE3_290					:1;				/* ECMIE3_290 */
					U4	xIE3_291					:1;				/* ECMIE3_291 */
					U4	xIE3_292					:1;				/* ECMIE3_292 */
					U4	xIE3_293					:1;				/* ECMIE3_293 */
					U4	xIE3_294					:1;				/* ECMIE3_294 */
					U4	xIE3_295					:1;				/* ECMIE3_295 */
					U4	xIE3_296					:1;				/* ECMIE3_296 */
					U4	xIE3_297					:1;				/* ECMIE3_297 */
					U4	xIE3_298					:1;				/* ECMIE3_298 */
					U4	xIE3_299					:1;				/* ECMIE3_299 */
					U4	xIE3_300					:1;				/* ECMIE3_300 */
					U4	xIE3_301					:1;				/* ECMIE3_301 */
					U4	xIE3_302					:1;				/* ECMIE3_302 */
					U4	xIE3_303					:1;				/* ECMIE3_303 */
					U4	xIE3_304					:1;				/* ECMIE3_304 */
					U4	xIE3_305					:1;				/* ECMIE3_305 */
					U4	xIE3_306					:1;				/* ECMIE3_306 */
					U4	xIE3_307					:1;				/* ECMIE3_307 */
					U4	xIE3_308					:1;				/* ECMIE3_308 */
					U4	xIE3_309					:1;				/* ECMIE3_309 */
					U4	xIE3_310					:1;				/* ECMIE3_310 */
					U4	xIE3_311					:1;				/* ECMIE3_311 */
					U4	xIE3_312					:1;				/* ECMIE3_312 */
					U4	xIE3_313					:1;				/* ECMIE3_313 */
					U4	xIE3_314					:1;				/* ECMIE3_314 */
					U4	xIE3_315					:1;				/* ECMIE3_315 */
					U4	xIE3_316					:1;				/* ECMIE3_316 */
					U4	xIE3_317					:1;				/* ECMIE3_317 */
					U4	xIE3_318					:1;				/* ECMIE3_318 */
					U4	xIE3_319					:1;				/* ECMIE3_319 */
				} stBit;
			} unECMINCFG3_9;										/* 0xFFD38118 */

			union												/* ECMINCFG3_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIE3_320					:1;				/* ECMIE3_320 */
					U4	xIE3_321					:1;				/* ECMIE3_321 */
					U4	xIE3_322					:1;				/* ECMIE3_322 */
					U4	xIE3_323					:1;				/* ECMIE3_323 */
					U4	xIE3_324					:1;				/* ECMIE3_324 */
					U4	xIE3_325					:1;				/* ECMIE3_325 */
					U4	xIE3_326					:1;				/* ECMIE3_326 */
					U4	xIE3_327					:1;				/* ECMIE3_327 */
					U4	xIE3_328					:1;				/* ECMIE3_328 */
					U4	xIE3_329					:1;				/* ECMIE3_329 */
					U4	xIE3_330					:1;				/* ECMIE3_330 */
					U4	xIE3_331					:1;				/* ECMIE3_331 */
					U4	xIE3_332					:1;				/* ECMIE3_332 */
					U4	xIE3_333					:1;				/* ECMIE3_333 */
					U4	xIE3_334					:1;				/* ECMIE3_334 */
					U4	xIE3_335					:1;				/* ECMIE3_335 */
					U4	xIE3_336					:1;				/* ECMIE3_336 */
					U4	xIE3_337					:1;				/* ECMIE3_337 */
					U4	xIE3_338					:1;				/* ECMIE3_338 */
					U4	xIE3_339					:1;				/* ECMIE3_339 */
					U4	xIE3_340					:1;				/* ECMIE3_340 */
					U4	xIE3_341					:1;				/* ECMIE3_341 */
					U4	xIE3_342					:1;				/* ECMIE3_342 */
					U4	xIE3_343					:1;				/* ECMIE3_343 */
					U4	xIE3_344					:1;				/* ECMIE3_344 */
					U4	xIE3_345					:1;				/* ECMIE3_345 */
					U4	xIE3_346					:1;				/* ECMIE3_346 */
					U4	xIE3_347					:1;				/* ECMIE3_347 */
					U4	xIE3_348					:1;				/* ECMIE3_348 */
					U4	xIE3_349					:1;				/* ECMIE3_349 */
					U4	xIE3_350					:1;				/* ECMIE3_350 */
					U4	xIE3_351					:1;				/* ECMIE3_351 */
				} stBit;
			} unECMINCFG3_10;										/* 0xFFD3811C */
		} stECMINCFG3_n;
	} unECMINCFG3_n;

	U1	u1Dummy5[256];	/* 0xFFD38120 - 0xFFD3821F */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMIRCFG0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE000					:1;				/* ECMIRE000 */
					U4	xIRE001					:1;				/* ECMIRE001 */
					U4	xIRE002					:1;				/* ECMIRE002 */
					U4	xIRE003					:1;				/* ECMIRE003 */
					U4	xIRE004					:1;				/* ECMIRE004 */
					U4	xIRE005					:1;				/* ECMIRE005 */
					U4	xIRE006					:1;				/* ECMIRE006 */
					U4	xIRE007					:1;				/* ECMIRE007 */
					U4	xIRE008					:1;				/* ECMIRE008 */
					U4	xIRE009					:1;				/* ECMIRE009 */
					U4	xIRE010					:1;				/* ECMIRE010 */
					U4	xIRE011					:1;				/* ECMIRE011 */
					U4	xIRE012					:1;				/* ECMIRE012 */
					U4	xIRE013					:1;				/* ECMIRE013 */
					U4	xIRE014					:1;				/* ECMIRE014 */
					U4	xIRE015					:1;				/* ECMIRE015 */
					U4	xIRE016					:1;				/* ECMIRE016 */
					U4	xIRE017					:1;				/* ECMIRE017 */
					U4	xIRE018					:1;				/* ECMIRE018 */
					U4	xIRE019					:1;				/* ECMIRE019 */
					U4	xIRE020					:1;				/* ECMIRE020 */
					U4	xIRE021					:1;				/* ECMIRE021 */
					U4	xIRE022					:1;				/* ECMIRE022 */
					U4	xIRE023					:1;				/* ECMIRE023 */
					U4	xIRE024					:1;				/* ECMIRE024 */
					U4	xIRE025					:1;				/* ECMIRE025 */
					U4	xIRE026					:1;				/* ECMIRE026 */
					U4	xIRE027					:1;				/* ECMIRE027 */
					U4	xIRE028					:1;				/* ECMIRE028 */
					U4	xIRE029					:1;				/* ECMIRE029 */
					U4	xIRE030					:1;				/* ECMIRE030 */
					U4	xIRE031					:1;				/* ECMIRE031 */
				} stBit;
			} unECMIRCFG0;										/* 0xFFD38220 */

			union												/* ECMIRCFG1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE032					:1;				/* ECMIRE032 */
					U4	xIRE033					:1;				/* ECMIRE033 */
					U4	xIRE034					:1;				/* ECMIRE034 */
					U4	xIRE035					:1;				/* ECMIRE035 */
					U4	xIRE036					:1;				/* ECMIRE036 */
					U4	xIRE037					:1;				/* ECMIRE037 */
					U4	xIRE038					:1;				/* ECMIRE038 */
					U4	xIRE039					:1;				/* ECMIRE039 */
					U4	xIRE040					:1;				/* ECMIRE040 */
					U4	xIRE041					:1;				/* ECMIRE041 */
					U4	xIRE042					:1;				/* ECMIRE042 */
					U4	xIRE043					:1;				/* ECMIRE043 */
					U4	xIRE044					:1;				/* ECMIRE044 */
					U4	xIRE045					:1;				/* ECMIRE045 */
					U4	xIRE046					:1;				/* ECMIRE046 */
					U4	xIRE047					:1;				/* ECMIRE047 */
					U4	xIRE048					:1;				/* ECMIRE048 */
					U4	xIRE049					:1;				/* ECMIRE049 */
					U4	xIRE050					:1;				/* ECMIRE050 */
					U4	xIRE051					:1;				/* ECMIRE051 */
					U4	xIRE052					:1;				/* ECMIRE052 */
					U4	xIRE053					:1;				/* ECMIRE053 */
					U4	xIRE054					:1;				/* ECMIRE054 */
					U4	xIRE055					:1;				/* ECMIRE055 */
					U4	xIRE056					:1;				/* ECMIRE056 */
					U4	xIRE057					:1;				/* ECMIRE057 */
					U4	xIRE058					:1;				/* ECMIRE058 */
					U4	xIRE059					:1;				/* ECMIRE059 */
					U4	xIRE060					:1;				/* ECMIRE060 */
					U4	xIRE061					:1;				/* ECMIRE061 */
					U4	xIRE062					:1;				/* ECMIRE062 */
					U4	xIRE063					:1;				/* ECMIRE063 */
				} stBit;
			} unECMIRCFG1;										/* 0xFFD38224 */

			union												/* ECMIRCFG2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE064					:1;				/* ECMIRE064 */
					U4	xIRE065					:1;				/* ECMIRE065 */
					U4	xIRE066					:1;				/* ECMIRE066 */
					U4	xIRE067					:1;				/* ECMIRE067 */
					U4	xIRE068					:1;				/* ECMIRE068 */
					U4	xIRE069					:1;				/* ECMIRE069 */
					U4	xIRE070					:1;				/* ECMIRE070 */
					U4	xIRE071					:1;				/* ECMIRE071 */
					U4	xIRE072					:1;				/* ECMIRE072 */
					U4	xIRE073					:1;				/* ECMIRE073 */
					U4	xIRE074					:1;				/* ECMIRE074 */
					U4	xIRE075					:1;				/* ECMIRE075 */
					U4	xIRE076					:1;				/* ECMIRE076 */
					U4	xIRE077					:1;				/* ECMIRE077 */
					U4	xIRE078					:1;				/* ECMIRE078 */
					U4	xIRE079					:1;				/* ECMIRE079 */
					U4	xIRE080					:1;				/* ECMIRE080 */
					U4	xIRE081					:1;				/* ECMIRE081 */
					U4	xIRE082					:1;				/* ECMIRE082 */
					U4	xIRE083					:1;				/* ECMIRE083 */
					U4	xIRE084					:1;				/* ECMIRE084 */
					U4	xIRE085					:1;				/* ECMIRE085 */
					U4	xIRE086					:1;				/* ECMIRE086 */
					U4	xIRE087					:1;				/* ECMIRE087 */
					U4	xIRE088					:1;				/* ECMIRE088 */
					U4	xIRE089					:1;				/* ECMIRE089 */
					U4	xIRE090					:1;				/* ECMIRE090 */
					U4	xIRE091					:1;				/* ECMIRE091 */
					U4	xIRE092					:1;				/* ECMIRE092 */
					U4	xIRE093					:1;				/* ECMIRE093 */
					U4	xIRE094					:1;				/* ECMIRE094 */
					U4	xIRE095					:1;				/* ECMIRE095 */
				} stBit;
			} unECMIRCFG2;										/* 0xFFD38228 */

			union												/* ECMIRCFG3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE096					:1;				/* ECMIRE096 */
					U4	xIRE097					:1;				/* ECMIRE097 */
					U4	xIRE098					:1;				/* ECMIRE098 */
					U4	xIRE099					:1;				/* ECMIRE099 */
					U4	xIRE100					:1;				/* ECMIRE100 */
					U4	xIRE101					:1;				/* ECMIRE101 */
					U4	xIRE102					:1;				/* ECMIRE102 */
					U4	xIRE103					:1;				/* ECMIRE103 */
					U4	xIRE104					:1;				/* ECMIRE104 */
					U4	xIRE105					:1;				/* ECMIRE105 */
					U4	xIRE106					:1;				/* ECMIRE106 */
					U4	xIRE107					:1;				/* ECMIRE107 */
					U4	xIRE108					:1;				/* ECMIRE108 */
					U4	xIRE109					:1;				/* ECMIRE109 */
					U4	xIRE110					:1;				/* ECMIRE110 */
					U4	xIRE111					:1;				/* ECMIRE111 */
					U4	xIRE112					:1;				/* ECMIRE112 */
					U4	xIRE113					:1;				/* ECMIRE113 */
					U4	xIRE114					:1;				/* ECMIRE114 */
					U4	xIRE115					:1;				/* ECMIRE115 */
					U4	xIRE116					:1;				/* ECMIRE116 */
					U4	xIRE117					:1;				/* ECMIRE117 */
					U4	xIRE118					:1;				/* ECMIRE118 */
					U4	xIRE119					:1;				/* ECMIRE119 */
					U4	xIRE120					:1;				/* ECMIRE120 */
					U4	xIRE121					:1;				/* ECMIRE121 */
					U4	xIRE122					:1;				/* ECMIRE122 */
					U4	xIRE123					:1;				/* ECMIRE123 */
					U4	xIRE124					:1;				/* ECMIRE124 */
					U4	xIRE125					:1;				/* ECMIRE125 */
					U4	xIRE126					:1;				/* ECMIRE126 */
					U4	xIRE127					:1;				/* ECMIRE127 */
				} stBit;
			} unECMIRCFG3;										/* 0xFFD3822C */

			union												/* ECMIRCFG4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE128					:1;				/* ECMIRE128 */
					U4	xIRE129					:1;				/* ECMIRE129 */
					U4	xIRE130					:1;				/* ECMIRE130 */
					U4	xIRE131					:1;				/* ECMIRE131 */
					U4	xIRE132					:1;				/* ECMIRE132 */
					U4	xIRE133					:1;				/* ECMIRE133 */
					U4	xIRE134					:1;				/* ECMIRE134 */
					U4	xIRE135					:1;				/* ECMIRE135 */
					U4	xIRE136					:1;				/* ECMIRE136 */
					U4	xIRE137					:1;				/* ECMIRE137 */
					U4	xIRE138					:1;				/* ECMIRE138 */
					U4	xIRE139					:1;				/* ECMIRE139 */
					U4	xIRE140					:1;				/* ECMIRE140 */
					U4	xIRE141					:1;				/* ECMIRE141 */
					U4	xIRE142					:1;				/* ECMIRE142 */
					U4	xIRE143					:1;				/* ECMIRE143 */
					U4	xIRE144					:1;				/* ECMIRE144 */
					U4	xIRE145					:1;				/* ECMIRE145 */
					U4	xIRE146					:1;				/* ECMIRE146 */
					U4	xIRE147					:1;				/* ECMIRE147 */
					U4	xIRE148					:1;				/* ECMIRE148 */
					U4	xIRE149					:1;				/* ECMIRE149 */
					U4	xIRE150					:1;				/* ECMIRE150 */
					U4	xIRE151					:1;				/* ECMIRE151 */
					U4	xIRE152					:1;				/* ECMIRE152 */
					U4	xIRE153					:1;				/* ECMIRE153 */
					U4	xIRE154					:1;				/* ECMIRE154 */
					U4	xIRE155					:1;				/* ECMIRE155 */
					U4	xIRE156					:1;				/* ECMIRE156 */
					U4	xIRE157					:1;				/* ECMIRE157 */
					U4	xIRE158					:1;				/* ECMIRE158 */
					U4	xIRE159					:1;				/* ECMIRE159 */
				} stBit;
			} unECMIRCFG4;										/* 0xFFD38230 */

			union												/* ECMIRCFG5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE160					:1;				/* ECMIRE160 */
					U4	xIRE161					:1;				/* ECMIRE161 */
					U4	xIRE162					:1;				/* ECMIRE162 */
					U4	xIRE163					:1;				/* ECMIRE163 */
					U4	xIRE164					:1;				/* ECMIRE164 */
					U4	xIRE165					:1;				/* ECMIRE165 */
					U4	xIRE166					:1;				/* ECMIRE166 */
					U4	xIRE167					:1;				/* ECMIRE167 */
					U4	xIRE168					:1;				/* ECMIRE168 */
					U4	xIRE169					:1;				/* ECMIRE169 */
					U4	xIRE170					:1;				/* ECMIRE170 */
					U4	xIRE171					:1;				/* ECMIRE171 */
					U4	xIRE172					:1;				/* ECMIRE172 */
					U4	xIRE173					:1;				/* ECMIRE173 */
					U4	xIRE174					:1;				/* ECMIRE174 */
					U4	xIRE175					:1;				/* ECMIRE175 */
					U4	xIRE176					:1;				/* ECMIRE176 */
					U4	xIRE177					:1;				/* ECMIRE177 */
					U4	xIRE178					:1;				/* ECMIRE178 */
					U4	xIRE179					:1;				/* ECMIRE179 */
					U4	xIRE180					:1;				/* ECMIRE180 */
					U4	xIRE181					:1;				/* ECMIRE181 */
					U4	xIRE182					:1;				/* ECMIRE182 */
					U4	xIRE183					:1;				/* ECMIRE183 */
					U4	xIRE184					:1;				/* ECMIRE184 */
					U4	xIRE185					:1;				/* ECMIRE185 */
					U4	xIRE186					:1;				/* ECMIRE186 */
					U4	xIRE187					:1;				/* ECMIRE187 */
					U4	xIRE188					:1;				/* ECMIRE188 */
					U4	xIRE189					:1;				/* ECMIRE189 */
					U4	xIRE190					:1;				/* ECMIRE190 */
					U4	xIRE191					:1;				/* ECMIRE191 */
				} stBit;
			} unECMIRCFG5;										/* 0xFFD38234 */

			union												/* ECMIRCFG6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE192					:1;				/* ECMIRE192 */
					U4	xIRE193					:1;				/* ECMIRE193 */
					U4	xIRE194					:1;				/* ECMIRE194 */
					U4	xIRE195					:1;				/* ECMIRE195 */
					U4	xIRE196					:1;				/* ECMIRE196 */
					U4	xIRE197					:1;				/* ECMIRE197 */
					U4	xIRE198					:1;				/* ECMIRE198 */
					U4	xIRE199					:1;				/* ECMIRE199 */
					U4	xIRE200					:1;				/* ECMIRE200 */
					U4	xIRE201					:1;				/* ECMIRE201 */
					U4	xIRE202					:1;				/* ECMIRE202 */
					U4	xIRE203					:1;				/* ECMIRE203 */
					U4	xIRE204					:1;				/* ECMIRE204 */
					U4	xIRE205					:1;				/* ECMIRE205 */
					U4	xIRE206					:1;				/* ECMIRE206 */
					U4	xIRE207					:1;				/* ECMIRE207 */
					U4	xIRE208					:1;				/* ECMIRE208 */
					U4	xIRE209					:1;				/* ECMIRE209 */
					U4	xIRE210					:1;				/* ECMIRE210 */
					U4	xIRE211					:1;				/* ECMIRE211 */
					U4	xIRE212					:1;				/* ECMIRE212 */
					U4	xIRE213					:1;				/* ECMIRE213 */
					U4	xIRE214					:1;				/* ECMIRE214 */
					U4	xIRE215					:1;				/* ECMIRE215 */
					U4	xIRE216					:1;				/* ECMIRE216 */
					U4	xIRE217					:1;				/* ECMIRE217 */
					U4	xIRE218					:1;				/* ECMIRE218 */
					U4	xIRE219					:1;				/* ECMIRE219 */
					U4	xIRE220					:1;				/* ECMIRE220 */
					U4	xIRE221					:1;				/* ECMIRE221 */
					U4	xIRE222					:1;				/* ECMIRE222 */
					U4	xIRE223					:1;				/* ECMIRE223 */
				} stBit;
			} unECMIRCFG6;										/* 0xFFD38238 */

			union												/* ECMIRCFG7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE224					:1;				/* ECMIRE224 */
					U4	xIRE225					:1;				/* ECMIRE225 */
					U4	xIRE226					:1;				/* ECMIRE226 */
					U4	xIRE227					:1;				/* ECMIRE227 */
					U4	xIRE228					:1;				/* ECMIRE228 */
					U4	xIRE229					:1;				/* ECMIRE229 */
					U4	xIRE230					:1;				/* ECMIRE230 */
					U4	xIRE231					:1;				/* ECMIRE231 */
					U4	xIRE232					:1;				/* ECMIRE232 */
					U4	xIRE233					:1;				/* ECMIRE233 */
					U4	xIRE234					:1;				/* ECMIRE234 */
					U4	xIRE235					:1;				/* ECMIRE235 */
					U4	xIRE236					:1;				/* ECMIRE236 */
					U4	xIRE237					:1;				/* ECMIRE237 */
					U4	xIRE238					:1;				/* ECMIRE238 */
					U4	xIRE239					:1;				/* ECMIRE239 */
					U4	xIRE240					:1;				/* ECMIRE240 */
					U4	xIRE241					:1;				/* ECMIRE241 */
					U4	xIRE242					:1;				/* ECMIRE242 */
					U4	xIRE243					:1;				/* ECMIRE243 */
					U4	xIRE244					:1;				/* ECMIRE244 */
					U4	xIRE245					:1;				/* ECMIRE245 */
					U4	xIRE246					:1;				/* ECMIRE246 */
					U4	xIRE247					:1;				/* ECMIRE247 */
					U4	xIRE248					:1;				/* ECMIRE248 */
					U4	xIRE249					:1;				/* ECMIRE249 */
					U4	xIRE250					:1;				/* ECMIRE250 */
					U4	xIRE251					:1;				/* ECMIRE251 */
					U4	xIRE252					:1;				/* ECMIRE252 */
					U4	xIRE253					:1;				/* ECMIRE253 */
					U4	xIRE254					:1;				/* ECMIRE254 */
					U4	xIRE255					:1;				/* ECMIRE255 */
				} stBit;
			} unECMIRCFG7;										/* 0xFFD3823C */

			union												/* ECMIRCFG8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE256					:1;				/* ECMIRE256 */
					U4	xIRE257					:1;				/* ECMIRE257 */
					U4	xIRE258					:1;				/* ECMIRE258 */
					U4	xIRE259					:1;				/* ECMIRE259 */
					U4	xIRE260					:1;				/* ECMIRE260 */
					U4	xIRE261					:1;				/* ECMIRE261 */
					U4	xIRE262					:1;				/* ECMIRE262 */
					U4	xIRE263					:1;				/* ECMIRE263 */
					U4	xIRE264					:1;				/* ECMIRE264 */
					U4	xIRE265					:1;				/* ECMIRE265 */
					U4	xIRE266					:1;				/* ECMIRE266 */
					U4	xIRE267					:1;				/* ECMIRE267 */
					U4	xIRE268					:1;				/* ECMIRE268 */
					U4	xIRE269					:1;				/* ECMIRE269 */
					U4	xIRE270					:1;				/* ECMIRE270 */
					U4	xIRE271					:1;				/* ECMIRE271 */
					U4	xIRE272					:1;				/* ECMIRE272 */
					U4	xIRE273					:1;				/* ECMIRE273 */
					U4	xIRE274					:1;				/* ECMIRE274 */
					U4	xIRE275					:1;				/* ECMIRE275 */
					U4	xIRE276					:1;				/* ECMIRE276 */
					U4	xIRE277					:1;				/* ECMIRE277 */
					U4	xIRE278					:1;				/* ECMIRE278 */
					U4	xIRE279					:1;				/* ECMIRE279 */
					U4	xIRE280					:1;				/* ECMIRE280 */
					U4	xIRE281					:1;				/* ECMIRE281 */
					U4	xIRE282					:1;				/* ECMIRE282 */
					U4	xIRE283					:1;				/* ECMIRE283 */
					U4	xIRE284					:1;				/* ECMIRE284 */
					U4	xIRE285					:1;				/* ECMIRE285 */
					U4	xIRE286					:1;				/* ECMIRE286 */
					U4	xIRE287					:1;				/* ECMIRE287 */
				} stBit;
			} unECMIRCFG8;										/* 0xFFD38240 */

			union												/* ECMIRCFG9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE288					:1;				/* ECMIRE288 */
					U4	xIRE289					:1;				/* ECMIRE289 */
					U4	xIRE290					:1;				/* ECMIRE290 */
					U4	xIRE291					:1;				/* ECMIRE291 */
					U4	xIRE292					:1;				/* ECMIRE292 */
					U4	xIRE293					:1;				/* ECMIRE293 */
					U4	xIRE294					:1;				/* ECMIRE294 */
					U4	xIRE295					:1;				/* ECMIRE295 */
					U4	xIRE296					:1;				/* ECMIRE296 */
					U4	xIRE297					:1;				/* ECMIRE297 */
					U4	xIRE298					:1;				/* ECMIRE298 */
					U4	xIRE299					:1;				/* ECMIRE299 */
					U4	xIRE300					:1;				/* ECMIRE300 */
					U4	xIRE301					:1;				/* ECMIRE301 */
					U4	xIRE302					:1;				/* ECMIRE302 */
					U4	xIRE303					:1;				/* ECMIRE303 */
					U4	xIRE304					:1;				/* ECMIRE304 */
					U4	xIRE305					:1;				/* ECMIRE305 */
					U4	xIRE306					:1;				/* ECMIRE306 */
					U4	xIRE307					:1;				/* ECMIRE307 */
					U4	xIRE308					:1;				/* ECMIRE308 */
					U4	xIRE309					:1;				/* ECMIRE309 */
					U4	xIRE310					:1;				/* ECMIRE310 */
					U4	xIRE311					:1;				/* ECMIRE311 */
					U4	xIRE312					:1;				/* ECMIRE312 */
					U4	xIRE313					:1;				/* ECMIRE313 */
					U4	xIRE314					:1;				/* ECMIRE314 */
					U4	xIRE315					:1;				/* ECMIRE315 */
					U4	xIRE316					:1;				/* ECMIRE316 */
					U4	xIRE317					:1;				/* ECMIRE317 */
					U4	xIRE318					:1;				/* ECMIRE318 */
					U4	xIRE319					:1;				/* ECMIRE319 */
				} stBit;
			} unECMIRCFG9;										/* 0xFFD38244 */

			union												/* ECMIRCFG10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xIRE320					:1;				/* ECMIRE320 */
					U4	xIRE321					:1;				/* ECMIRE321 */
					U4	xIRE322					:1;				/* ECMIRE322 */
					U4	xIRE323					:1;				/* ECMIRE323 */
					U4	xIRE324					:1;				/* ECMIRE324 */
					U4	xIRE325					:1;				/* ECMIRE325 */
					U4	xIRE326					:1;				/* ECMIRE326 */
					U4	xIRE327					:1;				/* ECMIRE327 */
					U4	xIRE328					:1;				/* ECMIRE328 */
					U4	xIRE329					:1;				/* ECMIRE329 */
					U4	xIRE330					:1;				/* ECMIRE330 */
					U4	xIRE331					:1;				/* ECMIRE331 */
					U4	xIRE332					:1;				/* ECMIRE332 */
					U4	xIRE333					:1;				/* ECMIRE333 */
					U4	xIRE334					:1;				/* ECMIRE334 */
					U4	xIRE335					:1;				/* ECMIRE335 */
					U4	xIRE336					:1;				/* ECMIRE336 */
					U4	xIRE337					:1;				/* ECMIRE337 */
					U4	xIRE338					:1;				/* ECMIRE338 */
					U4	xIRE339					:1;				/* ECMIRE339 */
					U4	xIRE340					:1;				/* ECMIRE340 */
					U4	xIRE341					:1;				/* ECMIRE341 */
					U4	xIRE342					:1;				/* ECMIRE342 */
					U4	xIRE343					:1;				/* ECMIRE343 */
					U4	xIRE344					:1;				/* ECMIRE344 */
					U4	xIRE345					:1;				/* ECMIRE345 */
					U4	xIRE346					:1;				/* ECMIRE346 */
					U4	xIRE347					:1;				/* ECMIRE347 */
					U4	xIRE348					:1;				/* ECMIRE348 */
					U4	xIRE349					:1;				/* ECMIRE349 */
					U4	xIRE350					:1;				/* ECMIRE350 */
					U4	xIRE351					:1;				/* ECMIRE351 */
				} stBit;
			} unECMIRCFG10;										/* 0xFFD38248 */
		} stECMIRCFGn;
	} unECMIRCFGn;

	U1	u1Dummy8[16];	/* 0xFFD3824C - 0xFFD3825C */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMEMK0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	b11Dummy1				:11;			/* Reserved Bits */
					U4	xEMK011					:1;				/* ECMEMK011 */
					U4	b8Dummy2				:8;				/* Reserved Bits */
					U4	xEMK020					:1;				/* ECMEMK020 */
					U4	xEMK021					:1;				/* ECMEMK021 */
					U4	xEMK022					:1;				/* ECMEMK022 */
					U4	xEMK023					:1;				/* ECMEMK023 */
					U4	xEMK024					:1;				/* ECMEMK024 */
					U4	xEMK025					:1;				/* ECMEMK025 */
					U4	xEMK026					:1;				/* ECMEMK026 */
					U4	xEMK027					:1;				/* ECMEMK027 */
					U4	xEMK028					:1;				/* ECMEMK028 */
					U4	xEMK029					:1;				/* ECMEMK029 */
					U4	xEMK030					:1;				/* ECMEMK030 */
					U4	xEMK031					:1;				/* ECMEMK031 */
				} stBit;
			} unECMEMK0;										/* 0xFFD3825C */

			union												/* ECMEMK1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK032					:1;				/* ECMEMK032 */
					U4	xEMK033					:1;				/* ECMEMK033 */
					U4	xEMK034					:1;				/* ECMEMK034 */
					U4	xEMK035					:1;				/* ECMEMK035 */
					U4	xEMK036					:1;				/* ECMEMK036 */
					U4	xEMK037					:1;				/* ECMEMK037 */
					U4	xEMK038					:1;				/* ECMEMK038 */
					U4	xEMK039					:1;				/* ECMEMK039 */
					U4	xEMK040					:1;				/* ECMEMK040 */
					U4	xEMK041					:1;				/* ECMEMK041 */
					U4	xEMK042					:1;				/* ECMEMK042 */
					U4	xEMK043					:1;				/* ECMEMK043 */
					U4	xEMK044					:1;				/* ECMEMK044 */
					U4	xEMK045					:1;				/* ECMEMK045 */
					U4	xEMK046					:1;				/* ECMEMK046 */
					U4	xEMK047					:1;				/* ECMEMK047 */
					U4	xEMK048					:1;				/* ECMEMK048 */
					U4	xEMK049					:1;				/* ECMEMK049 */
					U4	xEMK050					:1;				/* ECMEMK050 */
					U4	xEMK051					:1;				/* ECMEMK051 */
					U4	xEMK052					:1;				/* ECMEMK052 */
					U4	xEMK053					:1;				/* ECMEMK053 */
					U4	xEMK054					:1;				/* ECMEMK054 */
					U4	xEMK055					:1;				/* ECMEMK055 */
					U4	xEMK056					:1;				/* ECMEMK056 */
					U4	xEMK057					:1;				/* ECMEMK057 */
					U4	xEMK058					:1;				/* ECMEMK058 */
					U4	xEMK059					:1;				/* ECMEMK059 */
					U4	xEMK060					:1;				/* ECMEMK060 */
					U4	xEMK061					:1;				/* ECMEMK061 */
					U4	xEMK062					:1;				/* ECMEMK062 */
					U4	xEMK063					:1;				/* ECMEMK063 */
				} stBit;
			} unECMEMK1;										/* 0xFFD38260 */

			union												/* ECMEMK2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK064					:1;				/* ECMEMK064 */
					U4	xEMK065					:1;				/* ECMEMK065 */
					U4	xEMK066					:1;				/* ECMEMK066 */
					U4	xEMK067					:1;				/* ECMEMK067 */
					U4	xEMK068					:1;				/* ECMEMK068 */
					U4	xEMK069					:1;				/* ECMEMK069 */
					U4	xEMK070					:1;				/* ECMEMK070 */
					U4	xEMK071					:1;				/* ECMEMK071 */
					U4	xEMK072					:1;				/* ECMEMK072 */
					U4	xEMK073					:1;				/* ECMEMK073 */
					U4	xEMK074					:1;				/* ECMEMK074 */
					U4	xEMK075					:1;				/* ECMEMK075 */
					U4	xEMK076					:1;				/* ECMEMK076 */
					U4	xEMK077					:1;				/* ECMEMK077 */
					U4	xEMK078					:1;				/* ECMEMK078 */
					U4	xEMK079					:1;				/* ECMEMK079 */
					U4	xEMK080					:1;				/* ECMEMK080 */
					U4	xEMK081					:1;				/* ECMEMK081 */
					U4	xEMK082					:1;				/* ECMEMK082 */
					U4	xEMK083					:1;				/* ECMEMK083 */
					U4	xEMK084					:1;				/* ECMEMK084 */
					U4	xEMK085					:1;				/* ECMEMK085 */
					U4	xEMK086					:1;				/* ECMEMK086 */
					U4	xEMK087					:1;				/* ECMEMK087 */
					U4	xEMK088					:1;				/* ECMEMK088 */
					U4	xEMK089					:1;				/* ECMEMK089 */
					U4	xEMK090					:1;				/* ECMEMK090 */
					U4	xEMK091					:1;				/* ECMEMK091 */
					U4	xEMK092					:1;				/* ECMEMK092 */
					U4	xEMK093					:1;				/* ECMEMK093 */
					U4	xEMK094					:1;				/* ECMEMK094 */
					U4	xEMK095					:1;				/* ECMEMK095 */
				} stBit;
			} unECMEMK2;										/* 0xFFD38264 */

			union												/* ECMEMK3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK096					:1;				/* ECMEMK096 */
					U4	xEMK097					:1;				/* ECMEMK097 */
					U4	xEMK098					:1;				/* ECMEMK098 */
					U4	xEMK099					:1;				/* ECMEMK099 */
					U4	xEMK100					:1;				/* ECMEMK100 */
					U4	xEMK101					:1;				/* ECMEMK101 */
					U4	xEMK102					:1;				/* ECMEMK102 */
					U4	xEMK103					:1;				/* ECMEMK103 */
					U4	xEMK104					:1;				/* ECMEMK104 */
					U4	xEMK105					:1;				/* ECMEMK105 */
					U4	xEMK106					:1;				/* ECMEMK106 */
					U4	xEMK107					:1;				/* ECMEMK107 */
					U4	xEMK108					:1;				/* ECMEMK108 */
					U4	xEMK109					:1;				/* ECMEMK109 */
					U4	xEMK110					:1;				/* ECMEMK110 */
					U4	xEMK111					:1;				/* ECMEMK111 */
					U4	xEMK112					:1;				/* ECMEMK112 */
					U4	xEMK113					:1;				/* ECMEMK113 */
					U4	xEMK114					:1;				/* ECMEMK114 */
					U4	xEMK115					:1;				/* ECMEMK115 */
					U4	xEMK116					:1;				/* ECMEMK116 */
					U4	xEMK117					:1;				/* ECMEMK117 */
					U4	xEMK118					:1;				/* ECMEMK118 */
					U4	xEMK119					:1;				/* ECMEMK119 */
					U4	xEMK120					:1;				/* ECMEMK120 */
					U4	xEMK121					:1;				/* ECMEMK121 */
					U4	xEMK122					:1;				/* ECMEMK122 */
					U4	xEMK123					:1;				/* ECMEMK123 */
					U4	xEMK124					:1;				/* ECMEMK124 */
					U4	xEMK125					:1;				/* ECMEMK125 */
					U4	xEMK126					:1;				/* ECMEMK126 */
					U4	xEMK127					:1;				/* ECMEMK127 */
				} stBit;
			} unECMEMK3;										/* 0xFFD38268 */

			union												/* ECMEMK4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK128					:1;				/* ECMEMK128 */
					U4	xEMK129					:1;				/* ECMEMK129 */
					U4	xEMK130					:1;				/* ECMEMK130 */
					U4	xEMK131					:1;				/* ECMEMK131 */
					U4	xEMK132					:1;				/* ECMEMK132 */
					U4	xEMK133					:1;				/* ECMEMK133 */
					U4	xEMK134					:1;				/* ECMEMK134 */
					U4	xEMK135					:1;				/* ECMEMK135 */
					U4	xEMK136					:1;				/* ECMEMK136 */
					U4	xEMK137					:1;				/* ECMEMK137 */
					U4	xEMK138					:1;				/* ECMEMK138 */
					U4	xEMK139					:1;				/* ECMEMK139 */
					U4	xEMK140					:1;				/* ECMEMK140 */
					U4	xEMK141					:1;				/* ECMEMK141 */
					U4	xEMK142					:1;				/* ECMEMK142 */
					U4	xEMK143					:1;				/* ECMEMK143 */
					U4	xEMK144					:1;				/* ECMEMK144 */
					U4	xEMK145					:1;				/* ECMEMK145 */
					U4	xEMK146					:1;				/* ECMEMK146 */
					U4	xEMK147					:1;				/* ECMEMK147 */
					U4	xEMK148					:1;				/* ECMEMK148 */
					U4	xEMK149					:1;				/* ECMEMK149 */
					U4	xEMK150					:1;				/* ECMEMK150 */
					U4	xEMK151					:1;				/* ECMEMK151 */
					U4	xEMK152					:1;				/* ECMEMK152 */
					U4	xEMK153					:1;				/* ECMEMK153 */
					U4	xEMK154					:1;				/* ECMEMK154 */
					U4	xEMK155					:1;				/* ECMEMK155 */
					U4	xEMK156					:1;				/* ECMEMK156 */
					U4	xEMK157					:1;				/* ECMEMK157 */
					U4	xEMK158					:1;				/* ECMEMK158 */
					U4	xEMK159					:1;				/* ECMEMK159 */
				} stBit;
			} unECMEMK4;										/* 0xFFD3826C */

			union												/* ECMEMK5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK160					:1;				/* ECMEMK160 */
					U4	xEMK161					:1;				/* ECMEMK161 */
					U4	xEMK162					:1;				/* ECMEMK162 */
					U4	xEMK163					:1;				/* ECMEMK163 */
					U4	xEMK164					:1;				/* ECMEMK164 */
					U4	xEMK165					:1;				/* ECMEMK165 */
					U4	xEMK166					:1;				/* ECMEMK166 */
					U4	xEMK167					:1;				/* ECMEMK167 */
					U4	xEMK168					:1;				/* ECMEMK168 */
					U4	xEMK169					:1;				/* ECMEMK169 */
					U4	xEMK170					:1;				/* ECMEMK170 */
					U4	xEMK171					:1;				/* ECMEMK171 */
					U4	xEMK172					:1;				/* ECMEMK172 */
					U4	xEMK173					:1;				/* ECMEMK173 */
					U4	xEMK174					:1;				/* ECMEMK174 */
					U4	xEMK175					:1;				/* ECMEMK175 */
					U4	xEMK176					:1;				/* ECMEMK176 */
					U4	xEMK177					:1;				/* ECMEMK177 */
					U4	xEMK178					:1;				/* ECMEMK178 */
					U4	xEMK179					:1;				/* ECMEMK179 */
					U4	xEMK180					:1;				/* ECMEMK180 */
					U4	xEMK181					:1;				/* ECMEMK181 */
					U4	xEMK182					:1;				/* ECMEMK182 */
					U4	xEMK183					:1;				/* ECMEMK183 */
					U4	xEMK184					:1;				/* ECMEMK184 */
					U4	xEMK185					:1;				/* ECMEMK185 */
					U4	xEMK186					:1;				/* ECMEMK186 */
					U4	xEMK187					:1;				/* ECMEMK187 */
					U4	xEMK188					:1;				/* ECMEMK188 */
					U4	xEMK189					:1;				/* ECMEMK189 */
					U4	xEMK190					:1;				/* ECMEMK190 */
					U4	xEMK191					:1;				/* ECMEMK191 */
				} stBit;
			} unECMEMK5;										/* 0xFFD38270 */

			union												/* ECMEMK6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK192					:1;				/* ECMEMK192 */
					U4	xEMK193					:1;				/* ECMEMK193 */
					U4	xEMK194					:1;				/* ECMEMK194 */
					U4	xEMK195					:1;				/* ECMEMK195 */
					U4	xEMK196					:1;				/* ECMEMK196 */
					U4	xEMK197					:1;				/* ECMEMK197 */
					U4	xEMK198					:1;				/* ECMEMK198 */
					U4	xEMK199					:1;				/* ECMEMK199 */
					U4	xEMK200					:1;				/* ECMEMK200 */
					U4	xEMK201					:1;				/* ECMEMK201 */
					U4	xEMK202					:1;				/* ECMEMK202 */
					U4	xEMK203					:1;				/* ECMEMK203 */
					U4	xEMK204					:1;				/* ECMEMK204 */
					U4	xEMK205					:1;				/* ECMEMK205 */
					U4	xEMK206					:1;				/* ECMEMK206 */
					U4	xEMK207					:1;				/* ECMEMK207 */
					U4	xEMK208					:1;				/* ECMEMK208 */
					U4	xEMK209					:1;				/* ECMEMK209 */
					U4	xEMK210					:1;				/* ECMEMK210 */
					U4	xEMK211					:1;				/* ECMEMK211 */
					U4	xEMK212					:1;				/* ECMEMK212 */
					U4	xEMK213					:1;				/* ECMEMK213 */
					U4	xEMK214					:1;				/* ECMEMK214 */
					U4	xEMK215					:1;				/* ECMEMK215 */
					U4	xEMK216					:1;				/* ECMEMK216 */
					U4	xEMK217					:1;				/* ECMEMK217 */
					U4	xEMK218					:1;				/* ECMEMK218 */
					U4	xEMK219					:1;				/* ECMEMK219 */
					U4	xEMK220					:1;				/* ECMEMK220 */
					U4	xEMK221					:1;				/* ECMEMK221 */
					U4	xEMK222					:1;				/* ECMEMK222 */
					U4	xEMK223					:1;				/* ECMEMK223 */
				} stBit;
			} unECMEMK6;										/* 0xFFD38274 */

			union												/* ECMEMK7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK224					:1;				/* ECMEMK224 */
					U4	xEMK225					:1;				/* ECMEMK225 */
					U4	xEMK226					:1;				/* ECMEMK226 */
					U4	xEMK227					:1;				/* ECMEMK227 */
					U4	xEMK228					:1;				/* ECMEMK228 */
					U4	xEMK229					:1;				/* ECMEMK229 */
					U4	xEMK230					:1;				/* ECMEMK230 */
					U4	xEMK231					:1;				/* ECMEMK231 */
					U4	xEMK232					:1;				/* ECMEMK232 */
					U4	xEMK233					:1;				/* ECMEMK233 */
					U4	xEMK234					:1;				/* ECMEMK234 */
					U4	xEMK235					:1;				/* ECMEMK235 */
					U4	xEMK236					:1;				/* ECMEMK236 */
					U4	xEMK237					:1;				/* ECMEMK237 */
					U4	xEMK238					:1;				/* ECMEMK238 */
					U4	xEMK239					:1;				/* ECMEMK239 */
					U4	xEMK240					:1;				/* ECMEMK240 */
					U4	xEMK241					:1;				/* ECMEMK241 */
					U4	xEMK242					:1;				/* ECMEMK242 */
					U4	xEMK243					:1;				/* ECMEMK243 */
					U4	xEMK244					:1;				/* ECMEMK244 */
					U4	xEMK245					:1;				/* ECMEMK245 */
					U4	xEMK246					:1;				/* ECMEMK246 */
					U4	xEMK247					:1;				/* ECMEMK247 */
					U4	xEMK248					:1;				/* ECMEMK248 */
					U4	xEMK249					:1;				/* ECMEMK249 */
					U4	xEMK250					:1;				/* ECMEMK250 */
					U4	xEMK251					:1;				/* ECMEMK251 */
					U4	xEMK252					:1;				/* ECMEMK252 */
					U4	xEMK253					:1;				/* ECMEMK253 */
					U4	xEMK254					:1;				/* ECMEMK254 */
					U4	xEMK255					:1;				/* ECMEMK255 */
				} stBit;
			} unECMEMK7;										/* 0xFFD38278 */

			union												/* ECMEMK8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK256					:1;				/* ECMEMK256 */
					U4	xEMK257					:1;				/* ECMEMK257 */
					U4	xEMK258					:1;				/* ECMEMK258 */
					U4	xEMK259					:1;				/* ECMEMK259 */
					U4	xEMK260					:1;				/* ECMEMK260 */
					U4	xEMK261					:1;				/* ECMEMK261 */
					U4	xEMK262					:1;				/* ECMEMK262 */
					U4	xEMK263					:1;				/* ECMEMK263 */
					U4	xEMK264					:1;				/* ECMEMK264 */
					U4	xEMK265					:1;				/* ECMEMK265 */
					U4	xEMK266					:1;				/* ECMEMK266 */
					U4	xEMK267					:1;				/* ECMEMK267 */
					U4	xEMK268					:1;				/* ECMEMK268 */
					U4	xEMK269					:1;				/* ECMEMK269 */
					U4	xEMK270					:1;				/* ECMEMK270 */
					U4	xEMK271					:1;				/* ECMEMK271 */
					U4	xEMK272					:1;				/* ECMEMK272 */
					U4	xEMK273					:1;				/* ECMEMK273 */
					U4	xEMK274					:1;				/* ECMEMK274 */
					U4	xEMK275					:1;				/* ECMEMK275 */
					U4	xEMK276					:1;				/* ECMEMK276 */
					U4	xEMK277					:1;				/* ECMEMK277 */
					U4	xEMK278					:1;				/* ECMEMK278 */
					U4	xEMK279					:1;				/* ECMEMK279 */
					U4	xEMK280					:1;				/* ECMEMK280 */
					U4	xEMK281					:1;				/* ECMEMK281 */
					U4	xEMK282					:1;				/* ECMEMK282 */
					U4	xEMK283					:1;				/* ECMEMK283 */
					U4	xEMK284					:1;				/* ECMEMK284 */
					U4	xEMK285					:1;				/* ECMEMK285 */
					U4	xEMK286					:1;				/* ECMEMK286 */
					U4	xEMK287					:1;				/* ECMEMK287 */
				} stBit;
			} unECMEMK8;										/* 0xFFD3827C */

			union												/* ECMEMK9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK288					:1;				/* ECMEMK288 */
					U4	xEMK289					:1;				/* ECMEMK289 */
					U4	xEMK290					:1;				/* ECMEMK290 */
					U4	xEMK291					:1;				/* ECMEMK291 */
					U4	xEMK292					:1;				/* ECMEMK292 */
					U4	xEMK293					:1;				/* ECMEMK293 */
					U4	xEMK294					:1;				/* ECMEMK294 */
					U4	xEMK295					:1;				/* ECMEMK295 */
					U4	xEMK296					:1;				/* ECMEMK296 */
					U4	xEMK297					:1;				/* ECMEMK297 */
					U4	xEMK298					:1;				/* ECMEMK298 */
					U4	xEMK299					:1;				/* ECMEMK299 */
					U4	xEMK300					:1;				/* ECMEMK300 */
					U4	xEMK301					:1;				/* ECMEMK301 */
					U4	xEMK302					:1;				/* ECMEMK302 */
					U4	xEMK303					:1;				/* ECMEMK303 */
					U4	xEMK304					:1;				/* ECMEMK304 */
					U4	xEMK305					:1;				/* ECMEMK305 */
					U4	xEMK306					:1;				/* ECMEMK306 */
					U4	xEMK307					:1;				/* ECMEMK307 */
					U4	xEMK308					:1;				/* ECMEMK308 */
					U4	xEMK309					:1;				/* ECMEMK309 */
					U4	xEMK310					:1;				/* ECMEMK310 */
					U4	xEMK311					:1;				/* ECMEMK311 */
					U4	xEMK312					:1;				/* ECMEMK312 */
					U4	xEMK313					:1;				/* ECMEMK313 */
					U4	xEMK314					:1;				/* ECMEMK314 */
					U4	xEMK315					:1;				/* ECMEMK315 */
					U4	xEMK316					:1;				/* ECMEMK316 */
					U4	xEMK317					:1;				/* ECMEMK317 */
					U4	xEMK318					:1;				/* ECMEMK318 */
					U4	xEMK319					:1;				/* ECMEMK319 */
				} stBit;
			} unECMEMK9;										/* 0xFFD38280 */

			union												/* ECMEMK10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xEMK320					:1;				/* ECMEMK320 */
					U4	xEMK321					:1;				/* ECMEMK321 */
					U4	xEMK322					:1;				/* ECMEMK322 */
					U4	xEMK323					:1;				/* ECMEMK323 */
					U4	xEMK324					:1;				/* ECMEMK324 */
					U4	xEMK325					:1;				/* ECMEMK325 */
					U4	xEMK326					:1;				/* ECMEMK326 */
					U4	xEMK327					:1;				/* ECMEMK327 */
					U4	xEMK328					:1;				/* ECMEMK328 */
					U4	xEMK329					:1;				/* ECMEMK329 */
					U4	xEMK330					:1;				/* ECMEMK330 */
					U4	xEMK331					:1;				/* ECMEMK331 */
					U4	xEMK332					:1;				/* ECMEMK332 */
					U4	xEMK333					:1;				/* ECMEMK333 */
					U4	xEMK334					:1;				/* ECMEMK334 */
					U4	xEMK335					:1;				/* ECMEMK335 */
					U4	xEMK336					:1;				/* ECMEMK336 */
					U4	xEMK337					:1;				/* ECMEMK337 */
					U4	xEMK338					:1;				/* ECMEMK338 */
					U4	xEMK339					:1;				/* ECMEMK339 */
					U4	xEMK340					:1;				/* ECMEMK340 */
					U4	xEMK341					:1;				/* ECMEMK341 */
					U4	xEMK342					:1;				/* ECMEMK342 */
					U4	xEMK343					:1;				/* ECMEMK343 */
					U4	xEMK344					:1;				/* ECMEMK344 */
					U4	xEMK345					:1;				/* ECMEMK345 */
					U4	xEMK346					:1;				/* ECMEMK346 */
					U4	xEMK347					:1;				/* ECMEMK347 */
					U4	xEMK348					:1;				/* ECMEMK348 */
					U4	xEMK349					:1;				/* ECMEMK349 */
					U4	xEMK350					:1;				/* ECMEMK350 */
					U4	xEMK351					:1;				/* ECMEMK351 */
				} stBit;
			} unECMEMK10;										/* 0xFFD38284 */
		} stECMEMKn;
	} unECMEMKn;

	U1	u1Dummy9[16];	/* 0xFFD38288 - 0xFFD38298 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMETMK0_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	b20Dummy1					:20;			/* Reserved Bits */
					U4	xETMK0_020					:1;				/* ECMETMK0_020 */
					U4	xETMK0_021					:1;				/* ECMETMK0_021 */
					U4	xETMK0_022					:1;				/* ECMETMK0_022 */
					U4	xETMK0_023					:1;				/* ECMETMK0_023 */
					U4	xETMK0_024					:1;				/* ECMETMK0_024 */
					U4	xETMK0_025					:1;				/* ECMETMK0_025 */
					U4	xETMK0_026					:1;				/* ECMETMK0_026 */
					U4	xETMK0_027					:1;				/* ECMETMK0_027 */
					U4	xETMK0_028					:1;				/* ECMETMK0_028 */
					U4	xETMK0_029					:1;				/* ECMETMK0_029 */
					U4	xETMK0_030					:1;				/* ECMETMK0_030 */
					U4	xETMK0_031					:1;				/* ECMETMK0_031 */
				} stBit;
			} unECMETMK0_0;										/* 0xFFD38298 */

			union												/* ECMETMK0_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_032					:1;				/* ECMETMK0_032 */
					U4	xETMK0_033					:1;				/* ECMETMK0_033 */
					U4	xETMK0_034					:1;				/* ECMETMK0_034 */
					U4	xETMK0_035					:1;				/* ECMETMK0_035 */
					U4	xETMK0_036					:1;				/* ECMETMK0_036 */
					U4	xETMK0_037					:1;				/* ECMETMK0_037 */
					U4	xETMK0_038					:1;				/* ECMETMK0_038 */
					U4	xETMK0_039					:1;				/* ECMETMK0_039 */
					U4	xETMK0_040					:1;				/* ECMETMK0_040 */
					U4	xETMK0_041					:1;				/* ECMETMK0_041 */
					U4	xETMK0_042					:1;				/* ECMETMK0_042 */
					U4	xETMK0_043					:1;				/* ECMETMK0_043 */
					U4	xETMK0_044					:1;				/* ECMETMK0_044 */
					U4	xETMK0_045					:1;				/* ECMETMK0_045 */
					U4	xETMK0_046					:1;				/* ECMETMK0_046 */
					U4	xETMK0_047					:1;				/* ECMETMK0_047 */
					U4	xETMK0_048					:1;				/* ECMETMK0_048 */
					U4	xETMK0_049					:1;				/* ECMETMK0_049 */
					U4	xETMK0_050					:1;				/* ECMETMK0_050 */
					U4	xETMK0_051					:1;				/* ECMETMK0_051 */
					U4	xETMK0_052					:1;				/* ECMETMK0_052 */
					U4	xETMK0_053					:1;				/* ECMETMK0_053 */
					U4	xETMK0_054					:1;				/* ECMETMK0_054 */
					U4	xETMK0_055					:1;				/* ECMETMK0_055 */
					U4	xETMK0_056					:1;				/* ECMETMK0_056 */
					U4	xETMK0_057					:1;				/* ECMETMK0_057 */
					U4	xETMK0_058					:1;				/* ECMETMK0_058 */
					U4	xETMK0_059					:1;				/* ECMETMK0_059 */
					U4	xETMK0_060					:1;				/* ECMETMK0_060 */
					U4	xETMK0_061					:1;				/* ECMETMK0_061 */
					U4	xETMK0_062					:1;				/* ECMETMK0_062 */
					U4	xETMK0_063					:1;				/* ECMETMK0_063 */
				} stBit;
			} unECMETMK0_1;										/* 0xFFD3829C */

			union												/* ECMETMK0_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_064					:1;				/* ECMETMK0_064 */
					U4	xETMK0_065					:1;				/* ECMETMK0_065 */
					U4	xETMK0_066					:1;				/* ECMETMK0_066 */
					U4	xETMK0_067					:1;				/* ECMETMK0_067 */
					U4	xETMK0_068					:1;				/* ECMETMK0_068 */
					U4	xETMK0_069					:1;				/* ECMETMK0_069 */
					U4	xETMK0_070					:1;				/* ECMETMK0_070 */
					U4	xETMK0_071					:1;				/* ECMETMK0_071 */
					U4	xETMK0_072					:1;				/* ECMETMK0_072 */
					U4	xETMK0_073					:1;				/* ECMETMK0_073 */
					U4	xETMK0_074					:1;				/* ECMETMK0_074 */
					U4	xETMK0_075					:1;				/* ECMETMK0_075 */
					U4	xETMK0_076					:1;				/* ECMETMK0_076 */
					U4	xETMK0_077					:1;				/* ECMETMK0_077 */
					U4	xETMK0_078					:1;				/* ECMETMK0_078 */
					U4	xETMK0_079					:1;				/* ECMETMK0_079 */
					U4	xETMK0_080					:1;				/* ECMETMK0_080 */
					U4	xETMK0_081					:1;				/* ECMETMK0_081 */
					U4	xETMK0_082					:1;				/* ECMETMK0_082 */
					U4	xETMK0_083					:1;				/* ECMETMK0_083 */
					U4	xETMK0_084					:1;				/* ECMETMK0_084 */
					U4	xETMK0_085					:1;				/* ECMETMK0_085 */
					U4	xETMK0_086					:1;				/* ECMETMK0_086 */
					U4	xETMK0_087					:1;				/* ECMETMK0_087 */
					U4	xETMK0_088					:1;				/* ECMETMK0_088 */
					U4	xETMK0_089					:1;				/* ECMETMK0_089 */
					U4	xETMK0_090					:1;				/* ECMETMK0_090 */
					U4	xETMK0_091					:1;				/* ECMETMK0_091 */
					U4	xETMK0_092					:1;				/* ECMETMK0_092 */
					U4	xETMK0_093					:1;				/* ECMETMK0_093 */
					U4	xETMK0_094					:1;				/* ECMETMK0_094 */
					U4	xETMK0_095					:1;				/* ECMETMK0_095 */
				} stBit;
			} unECMETMK0_2;										/* 0xFFD382A0 */

			union												/* ECMETMK0_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_096					:1;				/* ECMETMK0_096 */
					U4	xETMK0_097					:1;				/* ECMETMK0_097 */
					U4	xETMK0_098					:1;				/* ECMETMK0_098 */
					U4	xETMK0_099					:1;				/* ECMETMK0_099 */
					U4	xETMK0_100					:1;				/* ECMETMK0_100 */
					U4	xETMK0_101					:1;				/* ECMETMK0_101 */
					U4	xETMK0_102					:1;				/* ECMETMK0_102 */
					U4	xETMK0_103					:1;				/* ECMETMK0_103 */
					U4	xETMK0_104					:1;				/* ECMETMK0_104 */
					U4	xETMK0_105					:1;				/* ECMETMK0_105 */
					U4	xETMK0_106					:1;				/* ECMETMK0_106 */
					U4	xETMK0_107					:1;				/* ECMETMK0_107 */
					U4	xETMK0_108					:1;				/* ECMETMK0_108 */
					U4	xETMK0_109					:1;				/* ECMETMK0_109 */
					U4	xETMK0_110					:1;				/* ECMETMK0_110 */
					U4	xETMK0_111					:1;				/* ECMETMK0_111 */
					U4	xETMK0_112					:1;				/* ECMETMK0_112 */
					U4	xETMK0_113					:1;				/* ECMETMK0_113 */
					U4	xETMK0_114					:1;				/* ECMETMK0_114 */
					U4	xETMK0_115					:1;				/* ECMETMK0_115 */
					U4	xETMK0_116					:1;				/* ECMETMK0_116 */
					U4	xETMK0_117					:1;				/* ECMETMK0_117 */
					U4	xETMK0_118					:1;				/* ECMETMK0_118 */
					U4	xETMK0_119					:1;				/* ECMETMK0_119 */
					U4	xETMK0_120					:1;				/* ECMETMK0_120 */
					U4	xETMK0_121					:1;				/* ECMETMK0_121 */
					U4	xETMK0_122					:1;				/* ECMETMK0_122 */
					U4	xETMK0_123					:1;				/* ECMETMK0_123 */
					U4	xETMK0_124					:1;				/* ECMETMK0_124 */
					U4	xETMK0_125					:1;				/* ECMETMK0_125 */
					U4	xETMK0_126					:1;				/* ECMETMK0_126 */
					U4	xETMK0_127					:1;				/* ECMETMK0_127 */
				} stBit;
			} unECMETMK0_3;										/* 0xFFD382A4 */

			union												/* ECMETMK0_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_128					:1;				/* ECMETMK0_128 */
					U4	xETMK0_129					:1;				/* ECMETMK0_129 */
					U4	xETMK0_130					:1;				/* ECMETMK0_130 */
					U4	xETMK0_131					:1;				/* ECMETMK0_131 */
					U4	xETMK0_132					:1;				/* ECMETMK0_132 */
					U4	xETMK0_133					:1;				/* ECMETMK0_133 */
					U4	xETMK0_134					:1;				/* ECMETMK0_134 */
					U4	xETMK0_135					:1;				/* ECMETMK0_135 */
					U4	xETMK0_136					:1;				/* ECMETMK0_136 */
					U4	xETMK0_137					:1;				/* ECMETMK0_137 */
					U4	xETMK0_138					:1;				/* ECMETMK0_138 */
					U4	xETMK0_139					:1;				/* ECMETMK0_139 */
					U4	xETMK0_140					:1;				/* ECMETMK0_140 */
					U4	xETMK0_141					:1;				/* ECMETMK0_141 */
					U4	xETMK0_142					:1;				/* ECMETMK0_142 */
					U4	xETMK0_143					:1;				/* ECMETMK0_143 */
					U4	xETMK0_144					:1;				/* ECMETMK0_144 */
					U4	xETMK0_145					:1;				/* ECMETMK0_145 */
					U4	xETMK0_146					:1;				/* ECMETMK0_146 */
					U4	xETMK0_147					:1;				/* ECMETMK0_147 */
					U4	xETMK0_148					:1;				/* ECMETMK0_148 */
					U4	xETMK0_149					:1;				/* ECMETMK0_149 */
					U4	xETMK0_150					:1;				/* ECMETMK0_150 */
					U4	xETMK0_151					:1;				/* ECMETMK0_151 */
					U4	xETMK0_152					:1;				/* ECMETMK0_152 */
					U4	xETMK0_153					:1;				/* ECMETMK0_153 */
					U4	xETMK0_154					:1;				/* ECMETMK0_154 */
					U4	xETMK0_155					:1;				/* ECMETMK0_155 */
					U4	xETMK0_156					:1;				/* ECMETMK0_156 */
					U4	xETMK0_157					:1;				/* ECMETMK0_157 */
					U4	xETMK0_158					:1;				/* ECMETMK0_158 */
					U4	xETMK0_159					:1;				/* ECMETMK0_159 */
				} stBit;
			} unECMETMK0_4;										/* 0xFFD382A8 */

			union												/* ECMETMK0_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_160					:1;				/* ECMETMK0_160 */
					U4	xETMK0_161					:1;				/* ECMETMK0_161 */
					U4	xETMK0_162					:1;				/* ECMETMK0_162 */
					U4	xETMK0_163					:1;				/* ECMETMK0_163 */
					U4	xETMK0_164					:1;				/* ECMETMK0_164 */
					U4	xETMK0_165					:1;				/* ECMETMK0_165 */
					U4	xETMK0_166					:1;				/* ECMETMK0_166 */
					U4	xETMK0_167					:1;				/* ECMETMK0_167 */
					U4	xETMK0_168					:1;				/* ECMETMK0_168 */
					U4	xETMK0_169					:1;				/* ECMETMK0_169 */
					U4	xETMK0_170					:1;				/* ECMETMK0_170 */
					U4	xETMK0_171					:1;				/* ECMETMK0_171 */
					U4	xETMK0_172					:1;				/* ECMETMK0_172 */
					U4	xETMK0_173					:1;				/* ECMETMK0_173 */
					U4	xETMK0_174					:1;				/* ECMETMK0_174 */
					U4	xETMK0_175					:1;				/* ECMETMK0_175 */
					U4	xETMK0_176					:1;				/* ECMETMK0_176 */
					U4	xETMK0_177					:1;				/* ECMETMK0_177 */
					U4	xETMK0_178					:1;				/* ECMETMK0_178 */
					U4	xETMK0_179					:1;				/* ECMETMK0_179 */
					U4	xETMK0_180					:1;				/* ECMETMK0_180 */
					U4	xETMK0_181					:1;				/* ECMETMK0_181 */
					U4	xETMK0_182					:1;				/* ECMETMK0_182 */
					U4	xETMK0_183					:1;				/* ECMETMK0_183 */
					U4	xETMK0_184					:1;				/* ECMETMK0_184 */
					U4	xETMK0_185					:1;				/* ECMETMK0_185 */
					U4	xETMK0_186					:1;				/* ECMETMK0_186 */
					U4	xETMK0_187					:1;				/* ECMETMK0_187 */
					U4	xETMK0_188					:1;				/* ECMETMK0_188 */
					U4	xETMK0_189					:1;				/* ECMETMK0_189 */
					U4	xETMK0_190					:1;				/* ECMETMK0_190 */
					U4	xETMK0_191					:1;				/* ECMETMK0_191 */
				} stBit;
			} unECMETMK0_5;										/* 0xFFD382AC */

			union												/* ECMETMK0_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_192					:1;				/* ECMETMK0_192 */
					U4	xETMK0_193					:1;				/* ECMETMK0_193 */
					U4	xETMK0_194					:1;				/* ECMETMK0_194 */
					U4	xETMK0_195					:1;				/* ECMETMK0_195 */
					U4	xETMK0_196					:1;				/* ECMETMK0_196 */
					U4	xETMK0_197					:1;				/* ECMETMK0_197 */
					U4	xETMK0_198					:1;				/* ECMETMK0_198 */
					U4	xETMK0_199					:1;				/* ECMETMK0_199 */
					U4	xETMK0_200					:1;				/* ECMETMK0_200 */
					U4	xETMK0_201					:1;				/* ECMETMK0_201 */
					U4	xETMK0_202					:1;				/* ECMETMK0_202 */
					U4	xETMK0_203					:1;				/* ECMETMK0_203 */
					U4	xETMK0_204					:1;				/* ECMETMK0_204 */
					U4	xETMK0_205					:1;				/* ECMETMK0_205 */
					U4	xETMK0_206					:1;				/* ECMETMK0_206 */
					U4	xETMK0_207					:1;				/* ECMETMK0_207 */
					U4	xETMK0_208					:1;				/* ECMETMK0_208 */
					U4	xETMK0_209					:1;				/* ECMETMK0_209 */
					U4	xETMK0_210					:1;				/* ECMETMK0_210 */
					U4	xETMK0_211					:1;				/* ECMETMK0_211 */
					U4	xETMK0_212					:1;				/* ECMETMK0_212 */
					U4	xETMK0_213					:1;				/* ECMETMK0_213 */
					U4	xETMK0_214					:1;				/* ECMETMK0_214 */
					U4	xETMK0_215					:1;				/* ECMETMK0_215 */
					U4	xETMK0_216					:1;				/* ECMETMK0_216 */
					U4	xETMK0_217					:1;				/* ECMETMK0_217 */
					U4	xETMK0_218					:1;				/* ECMETMK0_218 */
					U4	xETMK0_219					:1;				/* ECMETMK0_219 */
					U4	xETMK0_220					:1;				/* ECMETMK0_220 */
					U4	xETMK0_221					:1;				/* ECMETMK0_221 */
					U4	xETMK0_222					:1;				/* ECMETMK0_222 */
					U4	xETMK0_223					:1;				/* ECMETMK0_223 */
				} stBit;
			} unECMETMK0_6;										/* 0xFFD382B0 */

			union												/* ECMETMK0_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_224					:1;				/* ECMETMK0_224 */
					U4	xETMK0_225					:1;				/* ECMETMK0_225 */
					U4	xETMK0_226					:1;				/* ECMETMK0_226 */
					U4	xETMK0_227					:1;				/* ECMETMK0_227 */
					U4	xETMK0_228					:1;				/* ECMETMK0_228 */
					U4	xETMK0_229					:1;				/* ECMETMK0_229 */
					U4	xETMK0_230					:1;				/* ECMETMK0_230 */
					U4	xETMK0_231					:1;				/* ECMETMK0_231 */
					U4	xETMK0_232					:1;				/* ECMETMK0_232 */
					U4	xETMK0_233					:1;				/* ECMETMK0_233 */
					U4	xETMK0_234					:1;				/* ECMETMK0_234 */
					U4	xETMK0_235					:1;				/* ECMETMK0_235 */
					U4	xETMK0_236					:1;				/* ECMETMK0_236 */
					U4	xETMK0_237					:1;				/* ECMETMK0_237 */
					U4	xETMK0_238					:1;				/* ECMETMK0_238 */
					U4	xETMK0_239					:1;				/* ECMETMK0_239 */
					U4	xETMK0_240					:1;				/* ECMETMK0_240 */
					U4	xETMK0_241					:1;				/* ECMETMK0_241 */
					U4	xETMK0_242					:1;				/* ECMETMK0_242 */
					U4	xETMK0_243					:1;				/* ECMETMK0_243 */
					U4	xETMK0_244					:1;				/* ECMETMK0_244 */
					U4	xETMK0_245					:1;				/* ECMETMK0_245 */
					U4	xETMK0_246					:1;				/* ECMETMK0_246 */
					U4	xETMK0_247					:1;				/* ECMETMK0_247 */
					U4	xETMK0_248					:1;				/* ECMETMK0_248 */
					U4	xETMK0_249					:1;				/* ECMETMK0_249 */
					U4	xETMK0_250					:1;				/* ECMETMK0_250 */
					U4	xETMK0_251					:1;				/* ECMETMK0_251 */
					U4	xETMK0_252					:1;				/* ECMETMK0_252 */
					U4	xETMK0_253					:1;				/* ECMETMK0_253 */
					U4	xETMK0_254					:1;				/* ECMETMK0_254 */
					U4	xETMK0_255					:1;				/* ECMETMK0_255 */
				} stBit;
			} unECMETMK0_7;										/* 0xFFD382B4 */

			union												/* ECMETMK0_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_256					:1;				/* ECMETMK0_256 */
					U4	xETMK0_257					:1;				/* ECMETMK0_257 */
					U4	xETMK0_258					:1;				/* ECMETMK0_258 */
					U4	xETMK0_259					:1;				/* ECMETMK0_259 */
					U4	xETMK0_260					:1;				/* ECMETMK0_260 */
					U4	xETMK0_261					:1;				/* ECMETMK0_261 */
					U4	xETMK0_262					:1;				/* ECMETMK0_262 */
					U4	xETMK0_263					:1;				/* ECMETMK0_263 */
					U4	xETMK0_264					:1;				/* ECMETMK0_264 */
					U4	xETMK0_265					:1;				/* ECMETMK0_265 */
					U4	xETMK0_266					:1;				/* ECMETMK0_266 */
					U4	xETMK0_267					:1;				/* ECMETMK0_267 */
					U4	xETMK0_268					:1;				/* ECMETMK0_268 */
					U4	xETMK0_269					:1;				/* ECMETMK0_269 */
					U4	xETMK0_270					:1;				/* ECMETMK0_270 */
					U4	xETMK0_271					:1;				/* ECMETMK0_271 */
					U4	xETMK0_272					:1;				/* ECMETMK0_272 */
					U4	xETMK0_273					:1;				/* ECMETMK0_273 */
					U4	xETMK0_274					:1;				/* ECMETMK0_274 */
					U4	xETMK0_275					:1;				/* ECMETMK0_275 */
					U4	xETMK0_276					:1;				/* ECMETMK0_276 */
					U4	xETMK0_277					:1;				/* ECMETMK0_277 */
					U4	xETMK0_278					:1;				/* ECMETMK0_278 */
					U4	xETMK0_279					:1;				/* ECMETMK0_279 */
					U4	xETMK0_280					:1;				/* ECMETMK0_280 */
					U4	xETMK0_281					:1;				/* ECMETMK0_281 */
					U4	xETMK0_282					:1;				/* ECMETMK0_282 */
					U4	xETMK0_283					:1;				/* ECMETMK0_283 */
					U4	xETMK0_284					:1;				/* ECMETMK0_284 */
					U4	xETMK0_285					:1;				/* ECMETMK0_285 */
					U4	xETMK0_286					:1;				/* ECMETMK0_286 */
					U4	xETMK0_287					:1;				/* ECMETMK0_287 */
				} stBit;
			} unECMETMK0_8;										/* 0xFFD382B8 */

			union												/* ECMETMK0_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_288					:1;				/* ECMETMK0_288 */
					U4	xETMK0_289					:1;				/* ECMETMK0_289 */
					U4	xETMK0_290					:1;				/* ECMETMK0_290 */
					U4	xETMK0_291					:1;				/* ECMETMK0_291 */
					U4	xETMK0_292					:1;				/* ECMETMK0_292 */
					U4	xETMK0_293					:1;				/* ECMETMK0_293 */
					U4	xETMK0_294					:1;				/* ECMETMK0_294 */
					U4	xETMK0_295					:1;				/* ECMETMK0_295 */
					U4	xETMK0_296					:1;				/* ECMETMK0_296 */
					U4	xETMK0_297					:1;				/* ECMETMK0_297 */
					U4	xETMK0_298					:1;				/* ECMETMK0_298 */
					U4	xETMK0_299					:1;				/* ECMETMK0_299 */
					U4	xETMK0_300					:1;				/* ECMETMK0_300 */
					U4	xETMK0_301					:1;				/* ECMETMK0_301 */
					U4	xETMK0_302					:1;				/* ECMETMK0_302 */
					U4	xETMK0_303					:1;				/* ECMETMK0_303 */
					U4	xETMK0_304					:1;				/* ECMETMK0_304 */
					U4	xETMK0_305					:1;				/* ECMETMK0_305 */
					U4	xETMK0_306					:1;				/* ECMETMK0_306 */
					U4	xETMK0_307					:1;				/* ECMETMK0_307 */
					U4	xETMK0_308					:1;				/* ECMETMK0_308 */
					U4	xETMK0_309					:1;				/* ECMETMK0_309 */
					U4	xETMK0_310					:1;				/* ECMETMK0_310 */
					U4	xETMK0_311					:1;				/* ECMETMK0_311 */
					U4	xETMK0_312					:1;				/* ECMETMK0_312 */
					U4	xETMK0_313					:1;				/* ECMETMK0_313 */
					U4	xETMK0_314					:1;				/* ECMETMK0_314 */
					U4	xETMK0_315					:1;				/* ECMETMK0_315 */
					U4	xETMK0_316					:1;				/* ECMETMK0_316 */
					U4	xETMK0_317					:1;				/* ECMETMK0_317 */
					U4	xETMK0_318					:1;				/* ECMETMK0_318 */
					U4	xETMK0_319					:1;				/* ECMETMK0_319 */
				} stBit;
			} unECMETMK0_9;										/* 0xFFD382BC */

			union												/* ECMETMK0_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK0_320					:1;				/* ECMETMK0_320 */
					U4	xETMK0_321					:1;				/* ECMETMK0_321 */
					U4	xETMK0_322					:1;				/* ECMETMK0_322 */
					U4	xETMK0_323					:1;				/* ECMETMK0_323 */
					U4	xETMK0_324					:1;				/* ECMETMK0_324 */
					U4	xETMK0_325					:1;				/* ECMETMK0_325 */
					U4	xETMK0_326					:1;				/* ECMETMK0_326 */
					U4	xETMK0_327					:1;				/* ECMETMK0_327 */
					U4	xETMK0_328					:1;				/* ECMETMK0_328 */
					U4	xETMK0_329					:1;				/* ECMETMK0_329 */
					U4	xETMK0_330					:1;				/* ECMETMK0_330 */
					U4	xETMK0_331					:1;				/* ECMETMK0_331 */
					U4	xETMK0_332					:1;				/* ECMETMK0_332 */
					U4	xETMK0_333					:1;				/* ECMETMK0_333 */
					U4	xETMK0_334					:1;				/* ECMETMK0_334 */
					U4	xETMK0_335					:1;				/* ECMETMK0_335 */
					U4	xETMK0_336					:1;				/* ECMETMK0_336 */
					U4	xETMK0_337					:1;				/* ECMETMK0_337 */
					U4	xETMK0_338					:1;				/* ECMETMK0_338 */
					U4	xETMK0_339					:1;				/* ECMETMK0_339 */
					U4	xETMK0_340					:1;				/* ECMETMK0_340 */
					U4	xETMK0_341					:1;				/* ECMETMK0_341 */
					U4	xETMK0_342					:1;				/* ECMETMK0_342 */
					U4	xETMK0_343					:1;				/* ECMETMK0_343 */
					U4	xETMK0_344					:1;				/* ECMETMK0_344 */
					U4	xETMK0_345					:1;				/* ECMETMK0_345 */
					U4	xETMK0_346					:1;				/* ECMETMK0_346 */
					U4	xETMK0_347					:1;				/* ECMETMK0_347 */
					U4	xETMK0_348					:1;				/* ECMETMK0_348 */
					U4	xETMK0_349					:1;				/* ECMETMK0_349 */
					U4	xETMK0_350					:1;				/* ECMETMK0_350 */
					U4	xETMK0_351					:1;				/* ECMETMK0_351 */
				} stBit;
			} unECMETMK0_10;										/* 0xFFD382C0 */
		} stECMETMK0_n;
	} unECMETMK0_n;

	U1	u1Dummy10[16];	/* 0xFFD382C4 - 0xFFD382D4 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMETMK1_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	b20Dummy1					:20;			/* Reserved Bits */
					U4	xETMK1_020					:1;				/* ECMETMK1_020 */
					U4	xETMK1_021					:1;				/* ECMETMK1_021 */
					U4	xETMK1_022					:1;				/* ECMETMK1_022 */
					U4	xETMK1_023					:1;				/* ECMETMK1_023 */
					U4	xETMK1_024					:1;				/* ECMETMK1_024 */
					U4	xETMK1_025					:1;				/* ECMETMK1_025 */
					U4	xETMK1_026					:1;				/* ECMETMK1_026 */
					U4	xETMK1_027					:1;				/* ECMETMK1_027 */
					U4	xETMK1_028					:1;				/* ECMETMK1_028 */
					U4	xETMK1_029					:1;				/* ECMETMK1_029 */
					U4	xETMK1_030					:1;				/* ECMETMK1_030 */
					U4	xETMK1_031					:1;				/* ECMETMK1_031 */
				} stBit;
			} unECMETMK1_0;										/* 0xFFD382D4 */

			union												/* ECMETMK1_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_032					:1;				/* ECMETMK1_032 */
					U4	xETMK1_033					:1;				/* ECMETMK1_033 */
					U4	xETMK1_034					:1;				/* ECMETMK1_034 */
					U4	xETMK1_035					:1;				/* ECMETMK1_035 */
					U4	xETMK1_036					:1;				/* ECMETMK1_036 */
					U4	xETMK1_037					:1;				/* ECMETMK1_037 */
					U4	xETMK1_038					:1;				/* ECMETMK1_038 */
					U4	xETMK1_039					:1;				/* ECMETMK1_039 */
					U4	xETMK1_040					:1;				/* ECMETMK1_040 */
					U4	xETMK1_041					:1;				/* ECMETMK1_041 */
					U4	xETMK1_042					:1;				/* ECMETMK1_042 */
					U4	xETMK1_043					:1;				/* ECMETMK1_043 */
					U4	xETMK1_044					:1;				/* ECMETMK1_044 */
					U4	xETMK1_045					:1;				/* ECMETMK1_045 */
					U4	xETMK1_046					:1;				/* ECMETMK1_046 */
					U4	xETMK1_047					:1;				/* ECMETMK1_047 */
					U4	xETMK1_048					:1;				/* ECMETMK1_048 */
					U4	xETMK1_049					:1;				/* ECMETMK1_049 */
					U4	xETMK1_050					:1;				/* ECMETMK1_050 */
					U4	xETMK1_051					:1;				/* ECMETMK1_051 */
					U4	xETMK1_052					:1;				/* ECMETMK1_052 */
					U4	xETMK1_053					:1;				/* ECMETMK1_053 */
					U4	xETMK1_054					:1;				/* ECMETMK1_054 */
					U4	xETMK1_055					:1;				/* ECMETMK1_055 */
					U4	xETMK1_056					:1;				/* ECMETMK1_056 */
					U4	xETMK1_057					:1;				/* ECMETMK1_057 */
					U4	xETMK1_058					:1;				/* ECMETMK1_058 */
					U4	xETMK1_059					:1;				/* ECMETMK1_059 */
					U4	xETMK1_060					:1;				/* ECMETMK1_060 */
					U4	xETMK1_061					:1;				/* ECMETMK1_061 */
					U4	xETMK1_062					:1;				/* ECMETMK1_062 */
					U4	xETMK1_063					:1;				/* ECMETMK1_063 */
				} stBit;
			} unECMETMK1_1;										/* 0xFFD382D8 */

			union												/* ECMETMK1_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_064					:1;				/* ECMETMK1_064 */
					U4	xETMK1_065					:1;				/* ECMETMK1_065 */
					U4	xETMK1_066					:1;				/* ECMETMK1_066 */
					U4	xETMK1_067					:1;				/* ECMETMK1_067 */
					U4	xETMK1_068					:1;				/* ECMETMK1_068 */
					U4	xETMK1_069					:1;				/* ECMETMK1_069 */
					U4	xETMK1_070					:1;				/* ECMETMK1_070 */
					U4	xETMK1_071					:1;				/* ECMETMK1_071 */
					U4	xETMK1_072					:1;				/* ECMETMK1_072 */
					U4	xETMK1_073					:1;				/* ECMETMK1_073 */
					U4	xETMK1_074					:1;				/* ECMETMK1_074 */
					U4	xETMK1_075					:1;				/* ECMETMK1_075 */
					U4	xETMK1_076					:1;				/* ECMETMK1_076 */
					U4	xETMK1_077					:1;				/* ECMETMK1_077 */
					U4	xETMK1_078					:1;				/* ECMETMK1_078 */
					U4	xETMK1_079					:1;				/* ECMETMK1_079 */
					U4	xETMK1_080					:1;				/* ECMETMK1_080 */
					U4	xETMK1_081					:1;				/* ECMETMK1_081 */
					U4	xETMK1_082					:1;				/* ECMETMK1_082 */
					U4	xETMK1_083					:1;				/* ECMETMK1_083 */
					U4	xETMK1_084					:1;				/* ECMETMK1_084 */
					U4	xETMK1_085					:1;				/* ECMETMK1_085 */
					U4	xETMK1_086					:1;				/* ECMETMK1_086 */
					U4	xETMK1_087					:1;				/* ECMETMK1_087 */
					U4	xETMK1_088					:1;				/* ECMETMK1_088 */
					U4	xETMK1_089					:1;				/* ECMETMK1_089 */
					U4	xETMK1_090					:1;				/* ECMETMK1_090 */
					U4	xETMK1_091					:1;				/* ECMETMK1_091 */
					U4	xETMK1_092					:1;				/* ECMETMK1_092 */
					U4	xETMK1_093					:1;				/* ECMETMK1_093 */
					U4	xETMK1_094					:1;				/* ECMETMK1_094 */
					U4	xETMK1_095					:1;				/* ECMETMK1_095 */
				} stBit;
			} unECMETMK1_2;										/* 0xFFD382DC */

			union												/* ECMETMK1_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_096					:1;				/* ECMETMK1_096 */
					U4	xETMK1_097					:1;				/* ECMETMK1_097 */
					U4	xETMK1_098					:1;				/* ECMETMK1_098 */
					U4	xETMK1_099					:1;				/* ECMETMK1_099 */
					U4	xETMK1_100					:1;				/* ECMETMK1_100 */
					U4	xETMK1_101					:1;				/* ECMETMK1_101 */
					U4	xETMK1_102					:1;				/* ECMETMK1_102 */
					U4	xETMK1_103					:1;				/* ECMETMK1_103 */
					U4	xETMK1_104					:1;				/* ECMETMK1_104 */
					U4	xETMK1_105					:1;				/* ECMETMK1_105 */
					U4	xETMK1_106					:1;				/* ECMETMK1_106 */
					U4	xETMK1_107					:1;				/* ECMETMK1_107 */
					U4	xETMK1_108					:1;				/* ECMETMK1_108 */
					U4	xETMK1_109					:1;				/* ECMETMK1_109 */
					U4	xETMK1_110					:1;				/* ECMETMK1_110 */
					U4	xETMK1_111					:1;				/* ECMETMK1_111 */
					U4	xETMK1_112					:1;				/* ECMETMK1_112 */
					U4	xETMK1_113					:1;				/* ECMETMK1_113 */
					U4	xETMK1_114					:1;				/* ECMETMK1_114 */
					U4	xETMK1_115					:1;				/* ECMETMK1_115 */
					U4	xETMK1_116					:1;				/* ECMETMK1_116 */
					U4	xETMK1_117					:1;				/* ECMETMK1_117 */
					U4	xETMK1_118					:1;				/* ECMETMK1_118 */
					U4	xETMK1_119					:1;				/* ECMETMK1_119 */
					U4	xETMK1_120					:1;				/* ECMETMK1_120 */
					U4	xETMK1_121					:1;				/* ECMETMK1_121 */
					U4	xETMK1_122					:1;				/* ECMETMK1_122 */
					U4	xETMK1_123					:1;				/* ECMETMK1_123 */
					U4	xETMK1_124					:1;				/* ECMETMK1_124 */
					U4	xETMK1_125					:1;				/* ECMETMK1_125 */
					U4	xETMK1_126					:1;				/* ECMETMK1_126 */
					U4	xETMK1_127					:1;				/* ECMETMK1_127 */
				} stBit;
			} unECMETMK1_3;										/* 0xFFD382E0 */

			union												/* ECMETMK1_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_128					:1;				/* ECMETMK1_128 */
					U4	xETMK1_129					:1;				/* ECMETMK1_129 */
					U4	xETMK1_130					:1;				/* ECMETMK1_130 */
					U4	xETMK1_131					:1;				/* ECMETMK1_131 */
					U4	xETMK1_132					:1;				/* ECMETMK1_132 */
					U4	xETMK1_133					:1;				/* ECMETMK1_133 */
					U4	xETMK1_134					:1;				/* ECMETMK1_134 */
					U4	xETMK1_135					:1;				/* ECMETMK1_135 */
					U4	xETMK1_136					:1;				/* ECMETMK1_136 */
					U4	xETMK1_137					:1;				/* ECMETMK1_137 */
					U4	xETMK1_138					:1;				/* ECMETMK1_138 */
					U4	xETMK1_139					:1;				/* ECMETMK1_139 */
					U4	xETMK1_140					:1;				/* ECMETMK1_140 */
					U4	xETMK1_141					:1;				/* ECMETMK1_141 */
					U4	xETMK1_142					:1;				/* ECMETMK1_142 */
					U4	xETMK1_143					:1;				/* ECMETMK1_143 */
					U4	xETMK1_144					:1;				/* ECMETMK1_144 */
					U4	xETMK1_145					:1;				/* ECMETMK1_145 */
					U4	xETMK1_146					:1;				/* ECMETMK1_146 */
					U4	xETMK1_147					:1;				/* ECMETMK1_147 */
					U4	xETMK1_148					:1;				/* ECMETMK1_148 */
					U4	xETMK1_149					:1;				/* ECMETMK1_149 */
					U4	xETMK1_150					:1;				/* ECMETMK1_150 */
					U4	xETMK1_151					:1;				/* ECMETMK1_151 */
					U4	xETMK1_152					:1;				/* ECMETMK1_152 */
					U4	xETMK1_153					:1;				/* ECMETMK1_153 */
					U4	xETMK1_154					:1;				/* ECMETMK1_154 */
					U4	xETMK1_155					:1;				/* ECMETMK1_155 */
					U4	xETMK1_156					:1;				/* ECMETMK1_156 */
					U4	xETMK1_157					:1;				/* ECMETMK1_157 */
					U4	xETMK1_158					:1;				/* ECMETMK1_158 */
					U4	xETMK1_159					:1;				/* ECMETMK1_159 */
				} stBit;
			} unECMETMK1_4;										/* 0xFFD382E4 */

			union												/* ECMETMK1_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_160					:1;				/* ECMETMK1_160 */
					U4	xETMK1_161					:1;				/* ECMETMK1_161 */
					U4	xETMK1_162					:1;				/* ECMETMK1_162 */
					U4	xETMK1_163					:1;				/* ECMETMK1_163 */
					U4	xETMK1_164					:1;				/* ECMETMK1_164 */
					U4	xETMK1_165					:1;				/* ECMETMK1_165 */
					U4	xETMK1_166					:1;				/* ECMETMK1_166 */
					U4	xETMK1_167					:1;				/* ECMETMK1_167 */
					U4	xETMK1_168					:1;				/* ECMETMK1_168 */
					U4	xETMK1_169					:1;				/* ECMETMK1_169 */
					U4	xETMK1_170					:1;				/* ECMETMK1_170 */
					U4	xETMK1_171					:1;				/* ECMETMK1_171 */
					U4	xETMK1_172					:1;				/* ECMETMK1_172 */
					U4	xETMK1_173					:1;				/* ECMETMK1_173 */
					U4	xETMK1_174					:1;				/* ECMETMK1_174 */
					U4	xETMK1_175					:1;				/* ECMETMK1_175 */
					U4	xETMK1_176					:1;				/* ECMETMK1_176 */
					U4	xETMK1_177					:1;				/* ECMETMK1_177 */
					U4	xETMK1_178					:1;				/* ECMETMK1_178 */
					U4	xETMK1_179					:1;				/* ECMETMK1_179 */
					U4	xETMK1_180					:1;				/* ECMETMK1_180 */
					U4	xETMK1_181					:1;				/* ECMETMK1_181 */
					U4	xETMK1_182					:1;				/* ECMETMK1_182 */
					U4	xETMK1_183					:1;				/* ECMETMK1_183 */
					U4	xETMK1_184					:1;				/* ECMETMK1_184 */
					U4	xETMK1_185					:1;				/* ECMETMK1_185 */
					U4	xETMK1_186					:1;				/* ECMETMK1_186 */
					U4	xETMK1_187					:1;				/* ECMETMK1_187 */
					U4	xETMK1_188					:1;				/* ECMETMK1_188 */
					U4	xETMK1_189					:1;				/* ECMETMK1_189 */
					U4	xETMK1_190					:1;				/* ECMETMK1_190 */
					U4	xETMK1_191					:1;				/* ECMETMK1_191 */
				} stBit;
			} unECMETMK1_5;										/* 0xFFD382E8 */

			union												/* ECMETMK1_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_192					:1;				/* ECMETMK1_192 */
					U4	xETMK1_193					:1;				/* ECMETMK1_193 */
					U4	xETMK1_194					:1;				/* ECMETMK1_194 */
					U4	xETMK1_195					:1;				/* ECMETMK1_195 */
					U4	xETMK1_196					:1;				/* ECMETMK1_196 */
					U4	xETMK1_197					:1;				/* ECMETMK1_197 */
					U4	xETMK1_198					:1;				/* ECMETMK1_198 */
					U4	xETMK1_199					:1;				/* ECMETMK1_199 */
					U4	xETMK1_200					:1;				/* ECMETMK1_200 */
					U4	xETMK1_201					:1;				/* ECMETMK1_201 */
					U4	xETMK1_202					:1;				/* ECMETMK1_202 */
					U4	xETMK1_203					:1;				/* ECMETMK1_203 */
					U4	xETMK1_204					:1;				/* ECMETMK1_204 */
					U4	xETMK1_205					:1;				/* ECMETMK1_205 */
					U4	xETMK1_206					:1;				/* ECMETMK1_206 */
					U4	xETMK1_207					:1;				/* ECMETMK1_207 */
					U4	xETMK1_208					:1;				/* ECMETMK1_208 */
					U4	xETMK1_209					:1;				/* ECMETMK1_209 */
					U4	xETMK1_210					:1;				/* ECMETMK1_210 */
					U4	xETMK1_211					:1;				/* ECMETMK1_211 */
					U4	xETMK1_212					:1;				/* ECMETMK1_212 */
					U4	xETMK1_213					:1;				/* ECMETMK1_213 */
					U4	xETMK1_214					:1;				/* ECMETMK1_214 */
					U4	xETMK1_215					:1;				/* ECMETMK1_215 */
					U4	xETMK1_216					:1;				/* ECMETMK1_216 */
					U4	xETMK1_217					:1;				/* ECMETMK1_217 */
					U4	xETMK1_218					:1;				/* ECMETMK1_218 */
					U4	xETMK1_219					:1;				/* ECMETMK1_219 */
					U4	xETMK1_220					:1;				/* ECMETMK1_220 */
					U4	xETMK1_221					:1;				/* ECMETMK1_221 */
					U4	xETMK1_222					:1;				/* ECMETMK1_222 */
					U4	xETMK1_223					:1;				/* ECMETMK1_223 */
				} stBit;
			} unECMETMK1_6;										/* 0xFFD382EC */

			union												/* ECMETMK1_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_224					:1;				/* ECMETMK1_224 */
					U4	xETMK1_225					:1;				/* ECMETMK1_225 */
					U4	xETMK1_226					:1;				/* ECMETMK1_226 */
					U4	xETMK1_227					:1;				/* ECMETMK1_227 */
					U4	xETMK1_228					:1;				/* ECMETMK1_228 */
					U4	xETMK1_229					:1;				/* ECMETMK1_229 */
					U4	xETMK1_230					:1;				/* ECMETMK1_230 */
					U4	xETMK1_231					:1;				/* ECMETMK1_231 */
					U4	xETMK1_232					:1;				/* ECMETMK1_232 */
					U4	xETMK1_233					:1;				/* ECMETMK1_233 */
					U4	xETMK1_234					:1;				/* ECMETMK1_234 */
					U4	xETMK1_235					:1;				/* ECMETMK1_235 */
					U4	xETMK1_236					:1;				/* ECMETMK1_236 */
					U4	xETMK1_237					:1;				/* ECMETMK1_237 */
					U4	xETMK1_238					:1;				/* ECMETMK1_238 */
					U4	xETMK1_239					:1;				/* ECMETMK1_239 */
					U4	xETMK1_240					:1;				/* ECMETMK1_240 */
					U4	xETMK1_241					:1;				/* ECMETMK1_241 */
					U4	xETMK1_242					:1;				/* ECMETMK1_242 */
					U4	xETMK1_243					:1;				/* ECMETMK1_243 */
					U4	xETMK1_244					:1;				/* ECMETMK1_244 */
					U4	xETMK1_245					:1;				/* ECMETMK1_245 */
					U4	xETMK1_246					:1;				/* ECMETMK1_246 */
					U4	xETMK1_247					:1;				/* ECMETMK1_247 */
					U4	xETMK1_248					:1;				/* ECMETMK1_248 */
					U4	xETMK1_249					:1;				/* ECMETMK1_249 */
					U4	xETMK1_250					:1;				/* ECMETMK1_250 */
					U4	xETMK1_251					:1;				/* ECMETMK1_251 */
					U4	xETMK1_252					:1;				/* ECMETMK1_252 */
					U4	xETMK1_253					:1;				/* ECMETMK1_253 */
					U4	xETMK1_254					:1;				/* ECMETMK1_254 */
					U4	xETMK1_255					:1;				/* ECMETMK1_255 */
				} stBit;
			} unECMETMK1_7;										/* 0xFFD382F0 */

			union												/* ECMETMK1_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_256					:1;				/* ECMETMK1_256 */
					U4	xETMK1_257					:1;				/* ECMETMK1_257 */
					U4	xETMK1_258					:1;				/* ECMETMK1_258 */
					U4	xETMK1_259					:1;				/* ECMETMK1_259 */
					U4	xETMK1_260					:1;				/* ECMETMK1_260 */
					U4	xETMK1_261					:1;				/* ECMETMK1_261 */
					U4	xETMK1_262					:1;				/* ECMETMK1_262 */
					U4	xETMK1_263					:1;				/* ECMETMK1_263 */
					U4	xETMK1_264					:1;				/* ECMETMK1_264 */
					U4	xETMK1_265					:1;				/* ECMETMK1_265 */
					U4	xETMK1_266					:1;				/* ECMETMK1_266 */
					U4	xETMK1_267					:1;				/* ECMETMK1_267 */
					U4	xETMK1_268					:1;				/* ECMETMK1_268 */
					U4	xETMK1_269					:1;				/* ECMETMK1_269 */
					U4	xETMK1_270					:1;				/* ECMETMK1_270 */
					U4	xETMK1_271					:1;				/* ECMETMK1_271 */
					U4	xETMK1_272					:1;				/* ECMETMK1_272 */
					U4	xETMK1_273					:1;				/* ECMETMK1_273 */
					U4	xETMK1_274					:1;				/* ECMETMK1_274 */
					U4	xETMK1_275					:1;				/* ECMETMK1_275 */
					U4	xETMK1_276					:1;				/* ECMETMK1_276 */
					U4	xETMK1_277					:1;				/* ECMETMK1_277 */
					U4	xETMK1_278					:1;				/* ECMETMK1_278 */
					U4	xETMK1_279					:1;				/* ECMETMK1_279 */
					U4	xETMK1_280					:1;				/* ECMETMK1_280 */
					U4	xETMK1_281					:1;				/* ECMETMK1_281 */
					U4	xETMK1_282					:1;				/* ECMETMK1_282 */
					U4	xETMK1_283					:1;				/* ECMETMK1_283 */
					U4	xETMK1_284					:1;				/* ECMETMK1_284 */
					U4	xETMK1_285					:1;				/* ECMETMK1_285 */
					U4	xETMK1_286					:1;				/* ECMETMK1_286 */
					U4	xETMK1_287					:1;				/* ECMETMK1_287 */
				} stBit;
			} unECMETMK1_8;										/* 0xFFD382F4 */

			union												/* ECMETMK1_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_288					:1;				/* ECMETMK1_288 */
					U4	xETMK1_289					:1;				/* ECMETMK1_289 */
					U4	xETMK1_290					:1;				/* ECMETMK1_290 */
					U4	xETMK1_291					:1;				/* ECMETMK1_291 */
					U4	xETMK1_292					:1;				/* ECMETMK1_292 */
					U4	xETMK1_293					:1;				/* ECMETMK1_293 */
					U4	xETMK1_294					:1;				/* ECMETMK1_294 */
					U4	xETMK1_295					:1;				/* ECMETMK1_295 */
					U4	xETMK1_296					:1;				/* ECMETMK1_296 */
					U4	xETMK1_297					:1;				/* ECMETMK1_297 */
					U4	xETMK1_298					:1;				/* ECMETMK1_298 */
					U4	xETMK1_299					:1;				/* ECMETMK1_299 */
					U4	xETMK1_300					:1;				/* ECMETMK1_300 */
					U4	xETMK1_301					:1;				/* ECMETMK1_301 */
					U4	xETMK1_302					:1;				/* ECMETMK1_302 */
					U4	xETMK1_303					:1;				/* ECMETMK1_303 */
					U4	xETMK1_304					:1;				/* ECMETMK1_304 */
					U4	xETMK1_305					:1;				/* ECMETMK1_305 */
					U4	xETMK1_306					:1;				/* ECMETMK1_306 */
					U4	xETMK1_307					:1;				/* ECMETMK1_307 */
					U4	xETMK1_308					:1;				/* ECMETMK1_308 */
					U4	xETMK1_309					:1;				/* ECMETMK1_309 */
					U4	xETMK1_310					:1;				/* ECMETMK1_310 */
					U4	xETMK1_311					:1;				/* ECMETMK1_311 */
					U4	xETMK1_312					:1;				/* ECMETMK1_312 */
					U4	xETMK1_313					:1;				/* ECMETMK1_313 */
					U4	xETMK1_314					:1;				/* ECMETMK1_314 */
					U4	xETMK1_315					:1;				/* ECMETMK1_315 */
					U4	xETMK1_316					:1;				/* ECMETMK1_316 */
					U4	xETMK1_317					:1;				/* ECMETMK1_317 */
					U4	xETMK1_318					:1;				/* ECMETMK1_318 */
					U4	xETMK1_319					:1;				/* ECMETMK1_319 */
				} stBit;
			} unECMETMK1_9;										/* 0xFFD382F8 */

			union												/* ECMETMK1_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK1_320					:1;				/* ECMETMK1_320 */
					U4	xETMK1_321					:1;				/* ECMETMK1_321 */
					U4	xETMK1_322					:1;				/* ECMETMK1_322 */
					U4	xETMK1_323					:1;				/* ECMETMK1_323 */
					U4	xETMK1_324					:1;				/* ECMETMK1_324 */
					U4	xETMK1_325					:1;				/* ECMETMK1_325 */
					U4	xETMK1_326					:1;				/* ECMETMK1_326 */
					U4	xETMK1_327					:1;				/* ECMETMK1_327 */
					U4	xETMK1_328					:1;				/* ECMETMK1_328 */
					U4	xETMK1_329					:1;				/* ECMETMK1_329 */
					U4	xETMK1_330					:1;				/* ECMETMK1_330 */
					U4	xETMK1_331					:1;				/* ECMETMK1_331 */
					U4	xETMK1_332					:1;				/* ECMETMK1_332 */
					U4	xETMK1_333					:1;				/* ECMETMK1_333 */
					U4	xETMK1_334					:1;				/* ECMETMK1_334 */
					U4	xETMK1_335					:1;				/* ECMETMK1_335 */
					U4	xETMK1_336					:1;				/* ECMETMK1_336 */
					U4	xETMK1_337					:1;				/* ECMETMK1_337 */
					U4	xETMK1_338					:1;				/* ECMETMK1_338 */
					U4	xETMK1_339					:1;				/* ECMETMK1_339 */
					U4	xETMK1_340					:1;				/* ECMETMK1_340 */
					U4	xETMK1_341					:1;				/* ECMETMK1_341 */
					U4	xETMK1_342					:1;				/* ECMETMK1_342 */
					U4	xETMK1_343					:1;				/* ECMETMK1_343 */
					U4	xETMK1_344					:1;				/* ECMETMK1_344 */
					U4	xETMK1_345					:1;				/* ECMETMK1_345 */
					U4	xETMK1_346					:1;				/* ECMETMK1_346 */
					U4	xETMK1_347					:1;				/* ECMETMK1_347 */
					U4	xETMK1_348					:1;				/* ECMETMK1_348 */
					U4	xETMK1_349					:1;				/* ECMETMK1_349 */
					U4	xETMK1_350					:1;				/* ECMETMK1_350 */
					U4	xETMK1_351					:1;				/* ECMETMK1_351 */
				} stBit;
			} unECMETMK1_10;										/* 0xFFD382FC */
		} stECMETMK1_n;
	} unECMETMK1_n;

	U1	u1Dummy11[16];	/* 0xFFD38300 - 0xFFD38310 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMETMK2_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	b20Dummy1					:20;			/* Reserved Bits */
					U4	xETMK2_020					:1;				/* ECMETMK2_020 */
					U4	xETMK2_021					:1;				/* ECMETMK2_021 */
					U4	xETMK2_022					:1;				/* ECMETMK2_022 */
					U4	xETMK2_023					:1;				/* ECMETMK2_023 */
					U4	xETMK2_024					:1;				/* ECMETMK2_024 */
					U4	xETMK2_025					:1;				/* ECMETMK2_025 */
					U4	xETMK2_026					:1;				/* ECMETMK2_026 */
					U4	xETMK2_027					:1;				/* ECMETMK2_027 */
					U4	xETMK2_028					:1;				/* ECMETMK2_028 */
					U4	xETMK2_029					:1;				/* ECMETMK2_029 */
					U4	xETMK2_030					:1;				/* ECMETMK2_030 */
					U4	xETMK2_031					:1;				/* ECMETMK2_031 */
				} stBit;
			} unECMETMK2_0;										/* 0xFFD38310 */

			union												/* ECMETMK2_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_032					:1;				/* ECMETMK2_032 */
					U4	xETMK2_033					:1;				/* ECMETMK2_033 */
					U4	xETMK2_034					:1;				/* ECMETMK2_034 */
					U4	xETMK2_035					:1;				/* ECMETMK2_035 */
					U4	xETMK2_036					:1;				/* ECMETMK2_036 */
					U4	xETMK2_037					:1;				/* ECMETMK2_037 */
					U4	xETMK2_038					:1;				/* ECMETMK2_038 */
					U4	xETMK2_039					:1;				/* ECMETMK2_039 */
					U4	xETMK2_040					:1;				/* ECMETMK2_040 */
					U4	xETMK2_041					:1;				/* ECMETMK2_041 */
					U4	xETMK2_042					:1;				/* ECMETMK2_042 */
					U4	xETMK2_043					:1;				/* ECMETMK2_043 */
					U4	xETMK2_044					:1;				/* ECMETMK2_044 */
					U4	xETMK2_045					:1;				/* ECMETMK2_045 */
					U4	xETMK2_046					:1;				/* ECMETMK2_046 */
					U4	xETMK2_047					:1;				/* ECMETMK2_047 */
					U4	xETMK2_048					:1;				/* ECMETMK2_048 */
					U4	xETMK2_049					:1;				/* ECMETMK2_049 */
					U4	xETMK2_050					:1;				/* ECMETMK2_050 */
					U4	xETMK2_051					:1;				/* ECMETMK2_051 */
					U4	xETMK2_052					:1;				/* ECMETMK2_052 */
					U4	xETMK2_053					:1;				/* ECMETMK2_053 */
					U4	xETMK2_054					:1;				/* ECMETMK2_054 */
					U4	xETMK2_055					:1;				/* ECMETMK2_055 */
					U4	xETMK2_056					:1;				/* ECMETMK2_056 */
					U4	xETMK2_057					:1;				/* ECMETMK2_057 */
					U4	xETMK2_058					:1;				/* ECMETMK2_058 */
					U4	xETMK2_059					:1;				/* ECMETMK2_059 */
					U4	xETMK2_060					:1;				/* ECMETMK2_060 */
					U4	xETMK2_061					:1;				/* ECMETMK2_061 */
					U4	xETMK2_062					:1;				/* ECMETMK2_062 */
					U4	xETMK2_063					:1;				/* ECMETMK2_063 */
				} stBit;
			} unECMETMK2_1;										/* 0xFFD38314 */

			union												/* ECMETMK2_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_064					:1;				/* ECMETMK2_064 */
					U4	xETMK2_065					:1;				/* ECMETMK2_065 */
					U4	xETMK2_066					:1;				/* ECMETMK2_066 */
					U4	xETMK2_067					:1;				/* ECMETMK2_067 */
					U4	xETMK2_068					:1;				/* ECMETMK2_068 */
					U4	xETMK2_069					:1;				/* ECMETMK2_069 */
					U4	xETMK2_070					:1;				/* ECMETMK2_070 */
					U4	xETMK2_071					:1;				/* ECMETMK2_071 */
					U4	xETMK2_072					:1;				/* ECMETMK2_072 */
					U4	xETMK2_073					:1;				/* ECMETMK2_073 */
					U4	xETMK2_074					:1;				/* ECMETMK2_074 */
					U4	xETMK2_075					:1;				/* ECMETMK2_075 */
					U4	xETMK2_076					:1;				/* ECMETMK2_076 */
					U4	xETMK2_077					:1;				/* ECMETMK2_077 */
					U4	xETMK2_078					:1;				/* ECMETMK2_078 */
					U4	xETMK2_079					:1;				/* ECMETMK2_079 */
					U4	xETMK2_080					:1;				/* ECMETMK2_080 */
					U4	xETMK2_081					:1;				/* ECMETMK2_081 */
					U4	xETMK2_082					:1;				/* ECMETMK2_082 */
					U4	xETMK2_083					:1;				/* ECMETMK2_083 */
					U4	xETMK2_084					:1;				/* ECMETMK2_084 */
					U4	xETMK2_085					:1;				/* ECMETMK2_085 */
					U4	xETMK2_086					:1;				/* ECMETMK2_086 */
					U4	xETMK2_087					:1;				/* ECMETMK2_087 */
					U4	xETMK2_088					:1;				/* ECMETMK2_088 */
					U4	xETMK2_089					:1;				/* ECMETMK2_089 */
					U4	xETMK2_090					:1;				/* ECMETMK2_090 */
					U4	xETMK2_091					:1;				/* ECMETMK2_091 */
					U4	xETMK2_092					:1;				/* ECMETMK2_092 */
					U4	xETMK2_093					:1;				/* ECMETMK2_093 */
					U4	xETMK2_094					:1;				/* ECMETMK2_094 */
					U4	xETMK2_095					:1;				/* ECMETMK2_095 */
				} stBit;
			} unECMETMK2_2;										/* 0xFFD38318 */

			union												/* ECMETMK2_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_096					:1;				/* ECMETMK2_096 */
					U4	xETMK2_097					:1;				/* ECMETMK2_097 */
					U4	xETMK2_098					:1;				/* ECMETMK2_098 */
					U4	xETMK2_099					:1;				/* ECMETMK2_099 */
					U4	xETMK2_100					:1;				/* ECMETMK2_100 */
					U4	xETMK2_101					:1;				/* ECMETMK2_101 */
					U4	xETMK2_102					:1;				/* ECMETMK2_102 */
					U4	xETMK2_103					:1;				/* ECMETMK2_103 */
					U4	xETMK2_104					:1;				/* ECMETMK2_104 */
					U4	xETMK2_105					:1;				/* ECMETMK2_105 */
					U4	xETMK2_106					:1;				/* ECMETMK2_106 */
					U4	xETMK2_107					:1;				/* ECMETMK2_107 */
					U4	xETMK2_108					:1;				/* ECMETMK2_108 */
					U4	xETMK2_109					:1;				/* ECMETMK2_109 */
					U4	xETMK2_110					:1;				/* ECMETMK2_110 */
					U4	xETMK2_111					:1;				/* ECMETMK2_111 */
					U4	xETMK2_112					:1;				/* ECMETMK2_112 */
					U4	xETMK2_113					:1;				/* ECMETMK2_113 */
					U4	xETMK2_114					:1;				/* ECMETMK2_114 */
					U4	xETMK2_115					:1;				/* ECMETMK2_115 */
					U4	xETMK2_116					:1;				/* ECMETMK2_116 */
					U4	xETMK2_117					:1;				/* ECMETMK2_117 */
					U4	xETMK2_118					:1;				/* ECMETMK2_118 */
					U4	xETMK2_119					:1;				/* ECMETMK2_119 */
					U4	xETMK2_120					:1;				/* ECMETMK2_120 */
					U4	xETMK2_121					:1;				/* ECMETMK2_121 */
					U4	xETMK2_122					:1;				/* ECMETMK2_122 */
					U4	xETMK2_123					:1;				/* ECMETMK2_123 */
					U4	xETMK2_124					:1;				/* ECMETMK2_124 */
					U4	xETMK2_125					:1;				/* ECMETMK2_125 */
					U4	xETMK2_126					:1;				/* ECMETMK2_126 */
					U4	xETMK2_127					:1;				/* ECMETMK2_127 */
				} stBit;
			} unECMETMK2_3;										/* 0xFFD3831C */

			union												/* ECMETMK2_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_128					:1;				/* ECMETMK2_128 */
					U4	xETMK2_129					:1;				/* ECMETMK2_129 */
					U4	xETMK2_130					:1;				/* ECMETMK2_130 */
					U4	xETMK2_131					:1;				/* ECMETMK2_131 */
					U4	xETMK2_132					:1;				/* ECMETMK2_132 */
					U4	xETMK2_133					:1;				/* ECMETMK2_133 */
					U4	xETMK2_134					:1;				/* ECMETMK2_134 */
					U4	xETMK2_135					:1;				/* ECMETMK2_135 */
					U4	xETMK2_136					:1;				/* ECMETMK2_136 */
					U4	xETMK2_137					:1;				/* ECMETMK2_137 */
					U4	xETMK2_138					:1;				/* ECMETMK2_138 */
					U4	xETMK2_139					:1;				/* ECMETMK2_139 */
					U4	xETMK2_140					:1;				/* ECMETMK2_140 */
					U4	xETMK2_141					:1;				/* ECMETMK2_141 */
					U4	xETMK2_142					:1;				/* ECMETMK2_142 */
					U4	xETMK2_143					:1;				/* ECMETMK2_143 */
					U4	xETMK2_144					:1;				/* ECMETMK2_144 */
					U4	xETMK2_145					:1;				/* ECMETMK2_145 */
					U4	xETMK2_146					:1;				/* ECMETMK2_146 */
					U4	xETMK2_147					:1;				/* ECMETMK2_147 */
					U4	xETMK2_148					:1;				/* ECMETMK2_148 */
					U4	xETMK2_149					:1;				/* ECMETMK2_149 */
					U4	xETMK2_150					:1;				/* ECMETMK2_150 */
					U4	xETMK2_151					:1;				/* ECMETMK2_151 */
					U4	xETMK2_152					:1;				/* ECMETMK2_152 */
					U4	xETMK2_153					:1;				/* ECMETMK2_153 */
					U4	xETMK2_154					:1;				/* ECMETMK2_154 */
					U4	xETMK2_155					:1;				/* ECMETMK2_155 */
					U4	xETMK2_156					:1;				/* ECMETMK2_156 */
					U4	xETMK2_157					:1;				/* ECMETMK2_157 */
					U4	xETMK2_158					:1;				/* ECMETMK2_158 */
					U4	xETMK2_159					:1;				/* ECMETMK2_159 */
				} stBit;
			} unECMETMK2_4;										/* 0xFFD38320 */

			union												/* ECMETMK2_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_160					:1;				/* ECMETMK2_160 */
					U4	xETMK2_161					:1;				/* ECMETMK2_161 */
					U4	xETMK2_162					:1;				/* ECMETMK2_162 */
					U4	xETMK2_163					:1;				/* ECMETMK2_163 */
					U4	xETMK2_164					:1;				/* ECMETMK2_164 */
					U4	xETMK2_165					:1;				/* ECMETMK2_165 */
					U4	xETMK2_166					:1;				/* ECMETMK2_166 */
					U4	xETMK2_167					:1;				/* ECMETMK2_167 */
					U4	xETMK2_168					:1;				/* ECMETMK2_168 */
					U4	xETMK2_169					:1;				/* ECMETMK2_169 */
					U4	xETMK2_170					:1;				/* ECMETMK2_170 */
					U4	xETMK2_171					:1;				/* ECMETMK2_171 */
					U4	xETMK2_172					:1;				/* ECMETMK2_172 */
					U4	xETMK2_173					:1;				/* ECMETMK2_173 */
					U4	xETMK2_174					:1;				/* ECMETMK2_174 */
					U4	xETMK2_175					:1;				/* ECMETMK2_175 */
					U4	xETMK2_176					:1;				/* ECMETMK2_176 */
					U4	xETMK2_177					:1;				/* ECMETMK2_177 */
					U4	xETMK2_178					:1;				/* ECMETMK2_178 */
					U4	xETMK2_179					:1;				/* ECMETMK2_179 */
					U4	xETMK2_180					:1;				/* ECMETMK2_180 */
					U4	xETMK2_181					:1;				/* ECMETMK2_181 */
					U4	xETMK2_182					:1;				/* ECMETMK2_182 */
					U4	xETMK2_183					:1;				/* ECMETMK2_183 */
					U4	xETMK2_184					:1;				/* ECMETMK2_184 */
					U4	xETMK2_185					:1;				/* ECMETMK2_185 */
					U4	xETMK2_186					:1;				/* ECMETMK2_186 */
					U4	xETMK2_187					:1;				/* ECMETMK2_187 */
					U4	xETMK2_188					:1;				/* ECMETMK2_188 */
					U4	xETMK2_189					:1;				/* ECMETMK2_189 */
					U4	xETMK2_190					:1;				/* ECMETMK2_190 */
					U4	xETMK2_191					:1;				/* ECMETMK2_191 */
				} stBit;
			} unECMETMK2_5;										/* 0xFFD38324 */

			union												/* ECMETMK2_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_192					:1;				/* ECMETMK2_192 */
					U4	xETMK2_193					:1;				/* ECMETMK2_193 */
					U4	xETMK2_194					:1;				/* ECMETMK2_194 */
					U4	xETMK2_195					:1;				/* ECMETMK2_195 */
					U4	xETMK2_196					:1;				/* ECMETMK2_196 */
					U4	xETMK2_197					:1;				/* ECMETMK2_197 */
					U4	xETMK2_198					:1;				/* ECMETMK2_198 */
					U4	xETMK2_199					:1;				/* ECMETMK2_199 */
					U4	xETMK2_200					:1;				/* ECMETMK2_200 */
					U4	xETMK2_201					:1;				/* ECMETMK2_201 */
					U4	xETMK2_202					:1;				/* ECMETMK2_202 */
					U4	xETMK2_203					:1;				/* ECMETMK2_203 */
					U4	xETMK2_204					:1;				/* ECMETMK2_204 */
					U4	xETMK2_205					:1;				/* ECMETMK2_205 */
					U4	xETMK2_206					:1;				/* ECMETMK2_206 */
					U4	xETMK2_207					:1;				/* ECMETMK2_207 */
					U4	xETMK2_208					:1;				/* ECMETMK2_208 */
					U4	xETMK2_209					:1;				/* ECMETMK2_209 */
					U4	xETMK2_210					:1;				/* ECMETMK2_210 */
					U4	xETMK2_211					:1;				/* ECMETMK2_211 */
					U4	xETMK2_212					:1;				/* ECMETMK2_212 */
					U4	xETMK2_213					:1;				/* ECMETMK2_213 */
					U4	xETMK2_214					:1;				/* ECMETMK2_214 */
					U4	xETMK2_215					:1;				/* ECMETMK2_215 */
					U4	xETMK2_216					:1;				/* ECMETMK2_216 */
					U4	xETMK2_217					:1;				/* ECMETMK2_217 */
					U4	xETMK2_218					:1;				/* ECMETMK2_218 */
					U4	xETMK2_219					:1;				/* ECMETMK2_219 */
					U4	xETMK2_220					:1;				/* ECMETMK2_220 */
					U4	xETMK2_221					:1;				/* ECMETMK2_221 */
					U4	xETMK2_222					:1;				/* ECMETMK2_222 */
					U4	xETMK2_223					:1;				/* ECMETMK2_223 */
				} stBit;
			} unECMETMK2_6;										/* 0xFFD38328 */

			union												/* ECMETMK2_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_224					:1;				/* ECMETMK2_224 */
					U4	xETMK2_225					:1;				/* ECMETMK2_225 */
					U4	xETMK2_226					:1;				/* ECMETMK2_226 */
					U4	xETMK2_227					:1;				/* ECMETMK2_227 */
					U4	xETMK2_228					:1;				/* ECMETMK2_228 */
					U4	xETMK2_229					:1;				/* ECMETMK2_229 */
					U4	xETMK2_230					:1;				/* ECMETMK2_230 */
					U4	xETMK2_231					:1;				/* ECMETMK2_231 */
					U4	xETMK2_232					:1;				/* ECMETMK2_232 */
					U4	xETMK2_233					:1;				/* ECMETMK2_233 */
					U4	xETMK2_234					:1;				/* ECMETMK2_234 */
					U4	xETMK2_235					:1;				/* ECMETMK2_235 */
					U4	xETMK2_236					:1;				/* ECMETMK2_236 */
					U4	xETMK2_237					:1;				/* ECMETMK2_237 */
					U4	xETMK2_238					:1;				/* ECMETMK2_238 */
					U4	xETMK2_239					:1;				/* ECMETMK2_239 */
					U4	xETMK2_240					:1;				/* ECMETMK2_240 */
					U4	xETMK2_241					:1;				/* ECMETMK2_241 */
					U4	xETMK2_242					:1;				/* ECMETMK2_242 */
					U4	xETMK2_243					:1;				/* ECMETMK2_243 */
					U4	xETMK2_244					:1;				/* ECMETMK2_244 */
					U4	xETMK2_245					:1;				/* ECMETMK2_245 */
					U4	xETMK2_246					:1;				/* ECMETMK2_246 */
					U4	xETMK2_247					:1;				/* ECMETMK2_247 */
					U4	xETMK2_248					:1;				/* ECMETMK2_248 */
					U4	xETMK2_249					:1;				/* ECMETMK2_249 */
					U4	xETMK2_250					:1;				/* ECMETMK2_250 */
					U4	xETMK2_251					:1;				/* ECMETMK2_251 */
					U4	xETMK2_252					:1;				/* ECMETMK2_252 */
					U4	xETMK2_253					:1;				/* ECMETMK2_253 */
					U4	xETMK2_254					:1;				/* ECMETMK2_254 */
					U4	xETMK2_255					:1;				/* ECMETMK2_255 */
				} stBit;
			} unECMETMK2_7;										/* 0xFFD3832C */

			union												/* ECMETMK2_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_256					:1;				/* ECMETMK2_256 */
					U4	xETMK2_257					:1;				/* ECMETMK2_257 */
					U4	xETMK2_258					:1;				/* ECMETMK2_258 */
					U4	xETMK2_259					:1;				/* ECMETMK2_259 */
					U4	xETMK2_260					:1;				/* ECMETMK2_260 */
					U4	xETMK2_261					:1;				/* ECMETMK2_261 */
					U4	xETMK2_262					:1;				/* ECMETMK2_262 */
					U4	xETMK2_263					:1;				/* ECMETMK2_263 */
					U4	xETMK2_264					:1;				/* ECMETMK2_264 */
					U4	xETMK2_265					:1;				/* ECMETMK2_265 */
					U4	xETMK2_266					:1;				/* ECMETMK2_266 */
					U4	xETMK2_267					:1;				/* ECMETMK2_267 */
					U4	xETMK2_268					:1;				/* ECMETMK2_268 */
					U4	xETMK2_269					:1;				/* ECMETMK2_269 */
					U4	xETMK2_270					:1;				/* ECMETMK2_270 */
					U4	xETMK2_271					:1;				/* ECMETMK2_271 */
					U4	xETMK2_272					:1;				/* ECMETMK2_272 */
					U4	xETMK2_273					:1;				/* ECMETMK2_273 */
					U4	xETMK2_274					:1;				/* ECMETMK2_274 */
					U4	xETMK2_275					:1;				/* ECMETMK2_275 */
					U4	xETMK2_276					:1;				/* ECMETMK2_276 */
					U4	xETMK2_277					:1;				/* ECMETMK2_277 */
					U4	xETMK2_278					:1;				/* ECMETMK2_278 */
					U4	xETMK2_279					:1;				/* ECMETMK2_279 */
					U4	xETMK2_280					:1;				/* ECMETMK2_280 */
					U4	xETMK2_281					:1;				/* ECMETMK2_281 */
					U4	xETMK2_282					:1;				/* ECMETMK2_282 */
					U4	xETMK2_283					:1;				/* ECMETMK2_283 */
					U4	xETMK2_284					:1;				/* ECMETMK2_284 */
					U4	xETMK2_285					:1;				/* ECMETMK2_285 */
					U4	xETMK2_286					:1;				/* ECMETMK2_286 */
					U4	xETMK2_287					:1;				/* ECMETMK2_287 */
				} stBit;
			} unECMETMK2_8;										/* 0xFFD38330 */

			union												/* ECMETMK2_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_288					:1;				/* ECMETMK2_288 */
					U4	xETMK2_289					:1;				/* ECMETMK2_289 */
					U4	xETMK2_290					:1;				/* ECMETMK2_290 */
					U4	xETMK2_291					:1;				/* ECMETMK2_291 */
					U4	xETMK2_292					:1;				/* ECMETMK2_292 */
					U4	xETMK2_293					:1;				/* ECMETMK2_293 */
					U4	xETMK2_294					:1;				/* ECMETMK2_294 */
					U4	xETMK2_295					:1;				/* ECMETMK2_295 */
					U4	xETMK2_296					:1;				/* ECMETMK2_296 */
					U4	xETMK2_297					:1;				/* ECMETMK2_297 */
					U4	xETMK2_298					:1;				/* ECMETMK2_298 */
					U4	xETMK2_299					:1;				/* ECMETMK2_299 */
					U4	xETMK2_300					:1;				/* ECMETMK2_300 */
					U4	xETMK2_301					:1;				/* ECMETMK2_301 */
					U4	xETMK2_302					:1;				/* ECMETMK2_302 */
					U4	xETMK2_303					:1;				/* ECMETMK2_303 */
					U4	xETMK2_304					:1;				/* ECMETMK2_304 */
					U4	xETMK2_305					:1;				/* ECMETMK2_305 */
					U4	xETMK2_306					:1;				/* ECMETMK2_306 */
					U4	xETMK2_307					:1;				/* ECMETMK2_307 */
					U4	xETMK2_308					:1;				/* ECMETMK2_308 */
					U4	xETMK2_309					:1;				/* ECMETMK2_309 */
					U4	xETMK2_310					:1;				/* ECMETMK2_310 */
					U4	xETMK2_311					:1;				/* ECMETMK2_311 */
					U4	xETMK2_312					:1;				/* ECMETMK2_312 */
					U4	xETMK2_313					:1;				/* ECMETMK2_313 */
					U4	xETMK2_314					:1;				/* ECMETMK2_314 */
					U4	xETMK2_315					:1;				/* ECMETMK2_315 */
					U4	xETMK2_316					:1;				/* ECMETMK2_316 */
					U4	xETMK2_317					:1;				/* ECMETMK2_317 */
					U4	xETMK2_318					:1;				/* ECMETMK2_318 */
					U4	xETMK2_319					:1;				/* ECMETMK2_319 */
				} stBit;
			} unECMETMK2_9;										/* 0xFFD38334 */

			union												/* ECMETMK2_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK2_320					:1;				/* ECMETMK2_320 */
					U4	xETMK2_321					:1;				/* ECMETMK2_321 */
					U4	xETMK2_322					:1;				/* ECMETMK2_322 */
					U4	xETMK2_323					:1;				/* ECMETMK2_323 */
					U4	xETMK2_324					:1;				/* ECMETMK2_324 */
					U4	xETMK2_325					:1;				/* ECMETMK2_325 */
					U4	xETMK2_326					:1;				/* ECMETMK2_326 */
					U4	xETMK2_327					:1;				/* ECMETMK2_327 */
					U4	xETMK2_328					:1;				/* ECMETMK2_328 */
					U4	xETMK2_329					:1;				/* ECMETMK2_329 */
					U4	xETMK2_330					:1;				/* ECMETMK2_330 */
					U4	xETMK2_331					:1;				/* ECMETMK2_331 */
					U4	xETMK2_332					:1;				/* ECMETMK2_332 */
					U4	xETMK2_333					:1;				/* ECMETMK2_333 */
					U4	xETMK2_334					:1;				/* ECMETMK2_334 */
					U4	xETMK2_335					:1;				/* ECMETMK2_335 */
					U4	xETMK2_336					:1;				/* ECMETMK2_336 */
					U4	xETMK2_337					:1;				/* ECMETMK2_337 */
					U4	xETMK2_338					:1;				/* ECMETMK2_338 */
					U4	xETMK2_339					:1;				/* ECMETMK2_339 */
					U4	xETMK2_340					:1;				/* ECMETMK2_340 */
					U4	xETMK2_341					:1;				/* ECMETMK2_341 */
					U4	xETMK2_342					:1;				/* ECMETMK2_342 */
					U4	xETMK2_343					:1;				/* ECMETMK2_343 */
					U4	xETMK2_344					:1;				/* ECMETMK2_344 */
					U4	xETMK2_345					:1;				/* ECMETMK2_345 */
					U4	xETMK2_346					:1;				/* ECMETMK2_346 */
					U4	xETMK2_347					:1;				/* ECMETMK2_347 */
					U4	xETMK2_348					:1;				/* ECMETMK2_348 */
					U4	xETMK2_349					:1;				/* ECMETMK2_349 */
					U4	xETMK2_350					:1;				/* ECMETMK2_350 */
					U4	xETMK2_351					:1;				/* ECMETMK2_351 */
				} stBit;
			} unECMETMK2_10;										/* 0xFFD38338 */
		} stECMETMK2_n;
	} unECMETMK2_n;

	U1	u1Dummy12[16];	/* 0xFFD3833C - 0xFFD3834C */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMETMK3_0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	b20Dummy1					:20;			/* Reserved Bits */
					U4	xETMK3_020					:1;				/* ECMETMK3_020 */
					U4	xETMK3_021					:1;				/* ECMETMK3_021 */
					U4	xETMK3_022					:1;				/* ECMETMK3_022 */
					U4	xETMK3_023					:1;				/* ECMETMK3_023 */
					U4	xETMK3_024					:1;				/* ECMETMK3_024 */
					U4	xETMK3_025					:1;				/* ECMETMK3_025 */
					U4	xETMK3_026					:1;				/* ECMETMK3_026 */
					U4	xETMK3_027					:1;				/* ECMETMK3_027 */
					U4	xETMK3_028					:1;				/* ECMETMK3_028 */
					U4	xETMK3_029					:1;				/* ECMETMK3_029 */
					U4	xETMK3_030					:1;				/* ECMETMK3_030 */
					U4	xETMK3_031					:1;				/* ECMETMK3_031 */
				} stBit;
			} unECMETMK3_0;										/* 0xFFD3834C */

			union												/* ECMETMK3_1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_032					:1;				/* ECMETMK3_032 */
					U4	xETMK3_033					:1;				/* ECMETMK3_033 */
					U4	xETMK3_034					:1;				/* ECMETMK3_034 */
					U4	xETMK3_035					:1;				/* ECMETMK3_035 */
					U4	xETMK3_036					:1;				/* ECMETMK3_036 */
					U4	xETMK3_037					:1;				/* ECMETMK3_037 */
					U4	xETMK3_038					:1;				/* ECMETMK3_038 */
					U4	xETMK3_039					:1;				/* ECMETMK3_039 */
					U4	xETMK3_040					:1;				/* ECMETMK3_040 */
					U4	xETMK3_041					:1;				/* ECMETMK3_041 */
					U4	xETMK3_042					:1;				/* ECMETMK3_042 */
					U4	xETMK3_043					:1;				/* ECMETMK3_043 */
					U4	xETMK3_044					:1;				/* ECMETMK3_044 */
					U4	xETMK3_045					:1;				/* ECMETMK3_045 */
					U4	xETMK3_046					:1;				/* ECMETMK3_046 */
					U4	xETMK3_047					:1;				/* ECMETMK3_047 */
					U4	xETMK3_048					:1;				/* ECMETMK3_048 */
					U4	xETMK3_049					:1;				/* ECMETMK3_049 */
					U4	xETMK3_050					:1;				/* ECMETMK3_050 */
					U4	xETMK3_051					:1;				/* ECMETMK3_051 */
					U4	xETMK3_052					:1;				/* ECMETMK3_052 */
					U4	xETMK3_053					:1;				/* ECMETMK3_053 */
					U4	xETMK3_054					:1;				/* ECMETMK3_054 */
					U4	xETMK3_055					:1;				/* ECMETMK3_055 */
					U4	xETMK3_056					:1;				/* ECMETMK3_056 */
					U4	xETMK3_057					:1;				/* ECMETMK3_057 */
					U4	xETMK3_058					:1;				/* ECMETMK3_058 */
					U4	xETMK3_059					:1;				/* ECMETMK3_059 */
					U4	xETMK3_060					:1;				/* ECMETMK3_060 */
					U4	xETMK3_061					:1;				/* ECMETMK3_061 */
					U4	xETMK3_062					:1;				/* ECMETMK3_062 */
					U4	xETMK3_063					:1;				/* ECMETMK3_063 */
				} stBit;
			} unECMETMK3_1;										/* 0xFFD38350 */

			union												/* ECMETMK3_2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_064					:1;				/* ECMETMK3_064 */
					U4	xETMK3_065					:1;				/* ECMETMK3_065 */
					U4	xETMK3_066					:1;				/* ECMETMK3_066 */
					U4	xETMK3_067					:1;				/* ECMETMK3_067 */
					U4	xETMK3_068					:1;				/* ECMETMK3_068 */
					U4	xETMK3_069					:1;				/* ECMETMK3_069 */
					U4	xETMK3_070					:1;				/* ECMETMK3_070 */
					U4	xETMK3_071					:1;				/* ECMETMK3_071 */
					U4	xETMK3_072					:1;				/* ECMETMK3_072 */
					U4	xETMK3_073					:1;				/* ECMETMK3_073 */
					U4	xETMK3_074					:1;				/* ECMETMK3_074 */
					U4	xETMK3_075					:1;				/* ECMETMK3_075 */
					U4	xETMK3_076					:1;				/* ECMETMK3_076 */
					U4	xETMK3_077					:1;				/* ECMETMK3_077 */
					U4	xETMK3_078					:1;				/* ECMETMK3_078 */
					U4	xETMK3_079					:1;				/* ECMETMK3_079 */
					U4	xETMK3_080					:1;				/* ECMETMK3_080 */
					U4	xETMK3_081					:1;				/* ECMETMK3_081 */
					U4	xETMK3_082					:1;				/* ECMETMK3_082 */
					U4	xETMK3_083					:1;				/* ECMETMK3_083 */
					U4	xETMK3_084					:1;				/* ECMETMK3_084 */
					U4	xETMK3_085					:1;				/* ECMETMK3_085 */
					U4	xETMK3_086					:1;				/* ECMETMK3_086 */
					U4	xETMK3_087					:1;				/* ECMETMK3_087 */
					U4	xETMK3_088					:1;				/* ECMETMK3_088 */
					U4	xETMK3_089					:1;				/* ECMETMK3_089 */
					U4	xETMK3_090					:1;				/* ECMETMK3_090 */
					U4	xETMK3_091					:1;				/* ECMETMK3_091 */
					U4	xETMK3_092					:1;				/* ECMETMK3_092 */
					U4	xETMK3_093					:1;				/* ECMETMK3_093 */
					U4	xETMK3_094					:1;				/* ECMETMK3_094 */
					U4	xETMK3_095					:1;				/* ECMETMK3_095 */
				} stBit;
			} unECMETMK3_2;										/* 0xFFD38354 */

			union												/* ECMETMK3_3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_096					:1;				/* ECMETMK3_096 */
					U4	xETMK3_097					:1;				/* ECMETMK3_097 */
					U4	xETMK3_098					:1;				/* ECMETMK3_098 */
					U4	xETMK3_099					:1;				/* ECMETMK3_099 */
					U4	xETMK3_100					:1;				/* ECMETMK3_100 */
					U4	xETMK3_101					:1;				/* ECMETMK3_101 */
					U4	xETMK3_102					:1;				/* ECMETMK3_102 */
					U4	xETMK3_103					:1;				/* ECMETMK3_103 */
					U4	xETMK3_104					:1;				/* ECMETMK3_104 */
					U4	xETMK3_105					:1;				/* ECMETMK3_105 */
					U4	xETMK3_106					:1;				/* ECMETMK3_106 */
					U4	xETMK3_107					:1;				/* ECMETMK3_107 */
					U4	xETMK3_108					:1;				/* ECMETMK3_108 */
					U4	xETMK3_109					:1;				/* ECMETMK3_109 */
					U4	xETMK3_110					:1;				/* ECMETMK3_110 */
					U4	xETMK3_111					:1;				/* ECMETMK3_111 */
					U4	xETMK3_112					:1;				/* ECMETMK3_112 */
					U4	xETMK3_113					:1;				/* ECMETMK3_113 */
					U4	xETMK3_114					:1;				/* ECMETMK3_114 */
					U4	xETMK3_115					:1;				/* ECMETMK3_115 */
					U4	xETMK3_116					:1;				/* ECMETMK3_116 */
					U4	xETMK3_117					:1;				/* ECMETMK3_117 */
					U4	xETMK3_118					:1;				/* ECMETMK3_118 */
					U4	xETMK3_119					:1;				/* ECMETMK3_119 */
					U4	xETMK3_120					:1;				/* ECMETMK3_120 */
					U4	xETMK3_121					:1;				/* ECMETMK3_121 */
					U4	xETMK3_122					:1;				/* ECMETMK3_122 */
					U4	xETMK3_123					:1;				/* ECMETMK3_123 */
					U4	xETMK3_124					:1;				/* ECMETMK3_124 */
					U4	xETMK3_125					:1;				/* ECMETMK3_125 */
					U4	xETMK3_126					:1;				/* ECMETMK3_126 */
					U4	xETMK3_127					:1;				/* ECMETMK3_127 */
				} stBit;
			} unECMETMK3_3;										/* 0xFFD38358 */

			union												/* ECMETMK3_4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_128					:1;				/* ECMETMK3_128 */
					U4	xETMK3_129					:1;				/* ECMETMK3_129 */
					U4	xETMK3_130					:1;				/* ECMETMK3_130 */
					U4	xETMK3_131					:1;				/* ECMETMK3_131 */
					U4	xETMK3_132					:1;				/* ECMETMK3_132 */
					U4	xETMK3_133					:1;				/* ECMETMK3_133 */
					U4	xETMK3_134					:1;				/* ECMETMK3_134 */
					U4	xETMK3_135					:1;				/* ECMETMK3_135 */
					U4	xETMK3_136					:1;				/* ECMETMK3_136 */
					U4	xETMK3_137					:1;				/* ECMETMK3_137 */
					U4	xETMK3_138					:1;				/* ECMETMK3_138 */
					U4	xETMK3_139					:1;				/* ECMETMK3_139 */
					U4	xETMK3_140					:1;				/* ECMETMK3_140 */
					U4	xETMK3_141					:1;				/* ECMETMK3_141 */
					U4	xETMK3_142					:1;				/* ECMETMK3_142 */
					U4	xETMK3_143					:1;				/* ECMETMK3_143 */
					U4	xETMK3_144					:1;				/* ECMETMK3_144 */
					U4	xETMK3_145					:1;				/* ECMETMK3_145 */
					U4	xETMK3_146					:1;				/* ECMETMK3_146 */
					U4	xETMK3_147					:1;				/* ECMETMK3_147 */
					U4	xETMK3_148					:1;				/* ECMETMK3_148 */
					U4	xETMK3_149					:1;				/* ECMETMK3_149 */
					U4	xETMK3_150					:1;				/* ECMETMK3_150 */
					U4	xETMK3_151					:1;				/* ECMETMK3_151 */
					U4	xETMK3_152					:1;				/* ECMETMK3_152 */
					U4	xETMK3_153					:1;				/* ECMETMK3_153 */
					U4	xETMK3_154					:1;				/* ECMETMK3_154 */
					U4	xETMK3_155					:1;				/* ECMETMK3_155 */
					U4	xETMK3_156					:1;				/* ECMETMK3_156 */
					U4	xETMK3_157					:1;				/* ECMETMK3_157 */
					U4	xETMK3_158					:1;				/* ECMETMK3_158 */
					U4	xETMK3_159					:1;				/* ECMETMK3_159 */
				} stBit;
			} unECMETMK3_4;										/* 0xFFD3835C */

			union												/* ECMETMK3_5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_160					:1;				/* ECMETMK3_160 */
					U4	xETMK3_161					:1;				/* ECMETMK3_161 */
					U4	xETMK3_162					:1;				/* ECMETMK3_162 */
					U4	xETMK3_163					:1;				/* ECMETMK3_163 */
					U4	xETMK3_164					:1;				/* ECMETMK3_164 */
					U4	xETMK3_165					:1;				/* ECMETMK3_165 */
					U4	xETMK3_166					:1;				/* ECMETMK3_166 */
					U4	xETMK3_167					:1;				/* ECMETMK3_167 */
					U4	xETMK3_168					:1;				/* ECMETMK3_168 */
					U4	xETMK3_169					:1;				/* ECMETMK3_169 */
					U4	xETMK3_170					:1;				/* ECMETMK3_170 */
					U4	xETMK3_171					:1;				/* ECMETMK3_171 */
					U4	xETMK3_172					:1;				/* ECMETMK3_172 */
					U4	xETMK3_173					:1;				/* ECMETMK3_173 */
					U4	xETMK3_174					:1;				/* ECMETMK3_174 */
					U4	xETMK3_175					:1;				/* ECMETMK3_175 */
					U4	xETMK3_176					:1;				/* ECMETMK3_176 */
					U4	xETMK3_177					:1;				/* ECMETMK3_177 */
					U4	xETMK3_178					:1;				/* ECMETMK3_178 */
					U4	xETMK3_179					:1;				/* ECMETMK3_179 */
					U4	xETMK3_180					:1;				/* ECMETMK3_180 */
					U4	xETMK3_181					:1;				/* ECMETMK3_181 */
					U4	xETMK3_182					:1;				/* ECMETMK3_182 */
					U4	xETMK3_183					:1;				/* ECMETMK3_183 */
					U4	xETMK3_184					:1;				/* ECMETMK3_184 */
					U4	xETMK3_185					:1;				/* ECMETMK3_185 */
					U4	xETMK3_186					:1;				/* ECMETMK3_186 */
					U4	xETMK3_187					:1;				/* ECMETMK3_187 */
					U4	xETMK3_188					:1;				/* ECMETMK3_188 */
					U4	xETMK3_189					:1;				/* ECMETMK3_189 */
					U4	xETMK3_190					:1;				/* ECMETMK3_190 */
					U4	xETMK3_191					:1;				/* ECMETMK3_191 */
				} stBit;
			} unECMETMK3_5;										/* 0xFFD38360 */

			union												/* ECMETMK3_6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_192					:1;				/* ECMETMK3_192 */
					U4	xETMK3_193					:1;				/* ECMETMK3_193 */
					U4	xETMK3_194					:1;				/* ECMETMK3_194 */
					U4	xETMK3_195					:1;				/* ECMETMK3_195 */
					U4	xETMK3_196					:1;				/* ECMETMK3_196 */
					U4	xETMK3_197					:1;				/* ECMETMK3_197 */
					U4	xETMK3_198					:1;				/* ECMETMK3_198 */
					U4	xETMK3_199					:1;				/* ECMETMK3_199 */
					U4	xETMK3_200					:1;				/* ECMETMK3_200 */
					U4	xETMK3_201					:1;				/* ECMETMK3_201 */
					U4	xETMK3_202					:1;				/* ECMETMK3_202 */
					U4	xETMK3_203					:1;				/* ECMETMK3_203 */
					U4	xETMK3_204					:1;				/* ECMETMK3_204 */
					U4	xETMK3_205					:1;				/* ECMETMK3_205 */
					U4	xETMK3_206					:1;				/* ECMETMK3_206 */
					U4	xETMK3_207					:1;				/* ECMETMK3_207 */
					U4	xETMK3_208					:1;				/* ECMETMK3_208 */
					U4	xETMK3_209					:1;				/* ECMETMK3_209 */
					U4	xETMK3_210					:1;				/* ECMETMK3_210 */
					U4	xETMK3_211					:1;				/* ECMETMK3_211 */
					U4	xETMK3_212					:1;				/* ECMETMK3_212 */
					U4	xETMK3_213					:1;				/* ECMETMK3_213 */
					U4	xETMK3_214					:1;				/* ECMETMK3_214 */
					U4	xETMK3_215					:1;				/* ECMETMK3_215 */
					U4	xETMK3_216					:1;				/* ECMETMK3_216 */
					U4	xETMK3_217					:1;				/* ECMETMK3_217 */
					U4	xETMK3_218					:1;				/* ECMETMK3_218 */
					U4	xETMK3_219					:1;				/* ECMETMK3_219 */
					U4	xETMK3_220					:1;				/* ECMETMK3_220 */
					U4	xETMK3_221					:1;				/* ECMETMK3_221 */
					U4	xETMK3_222					:1;				/* ECMETMK3_222 */
					U4	xETMK3_223					:1;				/* ECMETMK3_223 */
				} stBit;
			} unECMETMK3_6;										/* 0xFFD38364 */

			union												/* ECMETMK3_7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_224					:1;				/* ECMETMK3_224 */
					U4	xETMK3_225					:1;				/* ECMETMK3_225 */
					U4	xETMK3_226					:1;				/* ECMETMK3_226 */
					U4	xETMK3_227					:1;				/* ECMETMK3_227 */
					U4	xETMK3_228					:1;				/* ECMETMK3_228 */
					U4	xETMK3_229					:1;				/* ECMETMK3_229 */
					U4	xETMK3_230					:1;				/* ECMETMK3_230 */
					U4	xETMK3_231					:1;				/* ECMETMK3_231 */
					U4	xETMK3_232					:1;				/* ECMETMK3_232 */
					U4	xETMK3_233					:1;				/* ECMETMK3_233 */
					U4	xETMK3_234					:1;				/* ECMETMK3_234 */
					U4	xETMK3_235					:1;				/* ECMETMK3_235 */
					U4	xETMK3_236					:1;				/* ECMETMK3_236 */
					U4	xETMK3_237					:1;				/* ECMETMK3_237 */
					U4	xETMK3_238					:1;				/* ECMETMK3_238 */
					U4	xETMK3_239					:1;				/* ECMETMK3_239 */
					U4	xETMK3_240					:1;				/* ECMETMK3_240 */
					U4	xETMK3_241					:1;				/* ECMETMK3_241 */
					U4	xETMK3_242					:1;				/* ECMETMK3_242 */
					U4	xETMK3_243					:1;				/* ECMETMK3_243 */
					U4	xETMK3_244					:1;				/* ECMETMK3_244 */
					U4	xETMK3_245					:1;				/* ECMETMK3_245 */
					U4	xETMK3_246					:1;				/* ECMETMK3_246 */
					U4	xETMK3_247					:1;				/* ECMETMK3_247 */
					U4	xETMK3_248					:1;				/* ECMETMK3_248 */
					U4	xETMK3_249					:1;				/* ECMETMK3_249 */
					U4	xETMK3_250					:1;				/* ECMETMK3_250 */
					U4	xETMK3_251					:1;				/* ECMETMK3_251 */
					U4	xETMK3_252					:1;				/* ECMETMK3_252 */
					U4	xETMK3_253					:1;				/* ECMETMK3_253 */
					U4	xETMK3_254					:1;				/* ECMETMK3_254 */
					U4	xETMK3_255					:1;				/* ECMETMK3_255 */
				} stBit;
			} unECMETMK3_7;										/* 0xFFD38368 */

			union												/* ECMETMK3_8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_256					:1;				/* ECMETMK3_256 */
					U4	xETMK3_257					:1;				/* ECMETMK3_257 */
					U4	xETMK3_258					:1;				/* ECMETMK3_258 */
					U4	xETMK3_259					:1;				/* ECMETMK3_259 */
					U4	xETMK3_260					:1;				/* ECMETMK3_260 */
					U4	xETMK3_261					:1;				/* ECMETMK3_261 */
					U4	xETMK3_262					:1;				/* ECMETMK3_262 */
					U4	xETMK3_263					:1;				/* ECMETMK3_263 */
					U4	xETMK3_264					:1;				/* ECMETMK3_264 */
					U4	xETMK3_265					:1;				/* ECMETMK3_265 */
					U4	xETMK3_266					:1;				/* ECMETMK3_266 */
					U4	xETMK3_267					:1;				/* ECMETMK3_267 */
					U4	xETMK3_268					:1;				/* ECMETMK3_268 */
					U4	xETMK3_269					:1;				/* ECMETMK3_269 */
					U4	xETMK3_270					:1;				/* ECMETMK3_270 */
					U4	xETMK3_271					:1;				/* ECMETMK3_271 */
					U4	xETMK3_272					:1;				/* ECMETMK3_272 */
					U4	xETMK3_273					:1;				/* ECMETMK3_273 */
					U4	xETMK3_274					:1;				/* ECMETMK3_274 */
					U4	xETMK3_275					:1;				/* ECMETMK3_275 */
					U4	xETMK3_276					:1;				/* ECMETMK3_276 */
					U4	xETMK3_277					:1;				/* ECMETMK3_277 */
					U4	xETMK3_278					:1;				/* ECMETMK3_278 */
					U4	xETMK3_279					:1;				/* ECMETMK3_279 */
					U4	xETMK3_280					:1;				/* ECMETMK3_280 */
					U4	xETMK3_281					:1;				/* ECMETMK3_281 */
					U4	xETMK3_282					:1;				/* ECMETMK3_282 */
					U4	xETMK3_283					:1;				/* ECMETMK3_283 */
					U4	xETMK3_284					:1;				/* ECMETMK3_284 */
					U4	xETMK3_285					:1;				/* ECMETMK3_285 */
					U4	xETMK3_286					:1;				/* ECMETMK3_286 */
					U4	xETMK3_287					:1;				/* ECMETMK3_287 */
				} stBit;
			} unECMETMK3_8;										/* 0xFFD3836C */

			union												/* ECMETMK3_9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_288					:1;				/* ECMETMK3_288 */
					U4	xETMK3_289					:1;				/* ECMETMK3_289 */
					U4	xETMK3_290					:1;				/* ECMETMK3_290 */
					U4	xETMK3_291					:1;				/* ECMETMK3_291 */
					U4	xETMK3_292					:1;				/* ECMETMK3_292 */
					U4	xETMK3_293					:1;				/* ECMETMK3_293 */
					U4	xETMK3_294					:1;				/* ECMETMK3_294 */
					U4	xETMK3_295					:1;				/* ECMETMK3_295 */
					U4	xETMK3_296					:1;				/* ECMETMK3_296 */
					U4	xETMK3_297					:1;				/* ECMETMK3_297 */
					U4	xETMK3_298					:1;				/* ECMETMK3_298 */
					U4	xETMK3_299					:1;				/* ECMETMK3_299 */
					U4	xETMK3_300					:1;				/* ECMETMK3_300 */
					U4	xETMK3_301					:1;				/* ECMETMK3_301 */
					U4	xETMK3_302					:1;				/* ECMETMK3_302 */
					U4	xETMK3_303					:1;				/* ECMETMK3_303 */
					U4	xETMK3_304					:1;				/* ECMETMK3_304 */
					U4	xETMK3_305					:1;				/* ECMETMK3_305 */
					U4	xETMK3_306					:1;				/* ECMETMK3_306 */
					U4	xETMK3_307					:1;				/* ECMETMK3_307 */
					U4	xETMK3_308					:1;				/* ECMETMK3_308 */
					U4	xETMK3_309					:1;				/* ECMETMK3_309 */
					U4	xETMK3_310					:1;				/* ECMETMK3_310 */
					U4	xETMK3_311					:1;				/* ECMETMK3_311 */
					U4	xETMK3_312					:1;				/* ECMETMK3_312 */
					U4	xETMK3_313					:1;				/* ECMETMK3_313 */
					U4	xETMK3_314					:1;				/* ECMETMK3_314 */
					U4	xETMK3_315					:1;				/* ECMETMK3_315 */
					U4	xETMK3_316					:1;				/* ECMETMK3_316 */
					U4	xETMK3_317					:1;				/* ECMETMK3_317 */
					U4	xETMK3_318					:1;				/* ECMETMK3_318 */
					U4	xETMK3_319					:1;				/* ECMETMK3_319 */
				} stBit;
			} unECMETMK3_9;										/* 0xFFD38370 */

			union												/* ECMETMK3_10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xETMK3_320					:1;				/* ECMETMK3_320 */
					U4	xETMK3_321					:1;				/* ECMETMK3_321 */
					U4	xETMK3_322					:1;				/* ECMETMK3_322 */
					U4	xETMK3_323					:1;				/* ECMETMK3_323 */
					U4	xETMK3_324					:1;				/* ECMETMK3_324 */
					U4	xETMK3_325					:1;				/* ECMETMK3_325 */
					U4	xETMK3_326					:1;				/* ECMETMK3_326 */
					U4	xETMK3_327					:1;				/* ECMETMK3_327 */
					U4	xETMK3_328					:1;				/* ECMETMK3_328 */
					U4	xETMK3_329					:1;				/* ECMETMK3_329 */
					U4	xETMK3_330					:1;				/* ECMETMK3_330 */
					U4	xETMK3_331					:1;				/* ECMETMK3_331 */
					U4	xETMK3_332					:1;				/* ECMETMK3_332 */
					U4	xETMK3_333					:1;				/* ECMETMK3_333 */
					U4	xETMK3_334					:1;				/* ECMETMK3_334 */
					U4	xETMK3_335					:1;				/* ECMETMK3_335 */
					U4	xETMK3_336					:1;				/* ECMETMK3_336 */
					U4	xETMK3_337					:1;				/* ECMETMK3_337 */
					U4	xETMK3_338					:1;				/* ECMETMK3_338 */
					U4	xETMK3_339					:1;				/* ECMETMK3_339 */
					U4	xETMK3_340					:1;				/* ECMETMK3_340 */
					U4	xETMK3_341					:1;				/* ECMETMK3_341 */
					U4	xETMK3_342					:1;				/* ECMETMK3_342 */
					U4	xETMK3_343					:1;				/* ECMETMK3_343 */
					U4	xETMK3_344					:1;				/* ECMETMK3_344 */
					U4	xETMK3_345					:1;				/* ECMETMK3_345 */
					U4	xETMK3_346					:1;				/* ECMETMK3_346 */
					U4	xETMK3_347					:1;				/* ECMETMK3_347 */
					U4	xETMK3_348					:1;				/* ECMETMK3_348 */
					U4	xETMK3_349					:1;				/* ECMETMK3_349 */
					U4	xETMK3_350					:1;				/* ECMETMK3_350 */
					U4	xETMK3_351					:1;				/* ECMETMK3_351 */
				} stBit;
			} unECMETMK3_10;										/* 0xFFD38374 */
		} stECMETMK3_n;
	} unECMETMK3_n;

	U1	u1Dummy15[256];	/* 0xFFD38378 - 0xFFD38478 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMESSTC0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE000					:1;				/* ECMCLSSE000 */
					U4	xCLSSE001					:1;				/* ECMCLSSE001 */
					U4	xCLSSE002					:1;				/* ECMCLSSE002 */
					U4	xCLSSE003					:1;				/* ECMCLSSE003 */
					U4	xCLSSE004					:1;				/* ECMCLSSE004 */
					U4	xCLSSE005					:1;				/* ECMCLSSE005 */
					U4	xCLSSE006					:1;				/* ECMCLSSE006 */
					U4	xCLSSE007					:1;				/* ECMCLSSE007 */
					U4	xCLSSE008					:1;				/* ECMCLSSE008 */
					U4	xCLSSE009					:1;				/* ECMCLSSE009 */
					U4	xCLSSE010					:1;				/* ECMCLSSE010 */
					U4	xCLSSE011					:1;				/* ECMCLSSE011 */
					U4	xCLSSE012					:1;				/* ECMCLSSE012 */
					U4	xCLSSE013					:1;				/* ECMCLSSE013 */
					U4	xCLSSE014					:1;				/* ECMCLSSE014 */
					U4	xCLSSE015					:1;				/* ECMCLSSE015 */
					U4	xCLSSE016					:1;				/* ECMCLSSE016 */
					U4	xCLSSE017					:1;				/* ECMCLSSE017 */
					U4	xCLSSE018					:1;				/* ECMCLSSE018 */
					U4	xCLSSE019					:1;				/* ECMCLSSE019 */
					U4	xCLSSE020					:1;				/* ECMCLSSE020 */
					U4	xCLSSE021					:1;				/* ECMCLSSE021 */
					U4	xCLSSE022					:1;				/* ECMCLSSE022 */
					U4	xCLSSE023					:1;				/* ECMCLSSE023 */
					U4	xCLSSE024					:1;				/* ECMCLSSE024 */
					U4	xCLSSE025					:1;				/* ECMCLSSE025 */
					U4	xCLSSE026					:1;				/* ECMCLSSE026 */
					U4	xCLSSE027					:1;				/* ECMCLSSE027 */
					U4	xCLSSE028					:1;				/* ECMCLSSE028 */
					U4	xCLSSE029					:1;				/* ECMCLSSE029 */
					U4	xCLSSE030					:1;				/* ECMCLSSE030 */
					U4	xCLSSE031					:1;				/* ECMCLSSE031 */
				} stBit;
			} unECMESSTC0;										/* 0xFFD38478 */

			union												/* ECMESSTC1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE032					:1;				/* ECMCLSSE032 */
					U4	xCLSSE033					:1;				/* ECMCLSSE033 */
					U4	xCLSSE034					:1;				/* ECMCLSSE034 */
					U4	xCLSSE035					:1;				/* ECMCLSSE035 */
					U4	xCLSSE036					:1;				/* ECMCLSSE036 */
					U4	xCLSSE037					:1;				/* ECMCLSSE037 */
					U4	xCLSSE038					:1;				/* ECMCLSSE038 */
					U4	xCLSSE039					:1;				/* ECMCLSSE039 */
					U4	xCLSSE040					:1;				/* ECMCLSSE040 */
					U4	xCLSSE041					:1;				/* ECMCLSSE041 */
					U4	xCLSSE042					:1;				/* ECMCLSSE042 */
					U4	xCLSSE043					:1;				/* ECMCLSSE043 */
					U4	xCLSSE044					:1;				/* ECMCLSSE044 */
					U4	xCLSSE045					:1;				/* ECMCLSSE045 */
					U4	xCLSSE046					:1;				/* ECMCLSSE046 */
					U4	xCLSSE047					:1;				/* ECMCLSSE047 */
					U4	xCLSSE048					:1;				/* ECMCLSSE048 */
					U4	xCLSSE049					:1;				/* ECMCLSSE049 */
					U4	xCLSSE050					:1;				/* ECMCLSSE050 */
					U4	xCLSSE051					:1;				/* ECMCLSSE051 */
					U4	xCLSSE052					:1;				/* ECMCLSSE052 */
					U4	xCLSSE053					:1;				/* ECMCLSSE053 */
					U4	xCLSSE054					:1;				/* ECMCLSSE054 */
					U4	xCLSSE055					:1;				/* ECMCLSSE055 */
					U4	xCLSSE056					:1;				/* ECMCLSSE056 */
					U4	xCLSSE057					:1;				/* ECMCLSSE057 */
					U4	xCLSSE058					:1;				/* ECMCLSSE058 */
					U4	xCLSSE059					:1;				/* ECMCLSSE059 */
					U4	xCLSSE060					:1;				/* ECMCLSSE060 */
					U4	xCLSSE061					:1;				/* ECMCLSSE061 */
					U4	xCLSSE062					:1;				/* ECMCLSSE062 */
					U4	xCLSSE063					:1;				/* ECMCLSSE063 */
				} stBit;
			} unECMESSTC1;										/* 0xFFD3847C */

			union												/* ECMESSTC2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE064					:1;				/* ECMCLSSE064 */
					U4	xCLSSE065					:1;				/* ECMCLSSE065 */
					U4	xCLSSE066					:1;				/* ECMCLSSE066 */
					U4	xCLSSE067					:1;				/* ECMCLSSE067 */
					U4	xCLSSE068					:1;				/* ECMCLSSE068 */
					U4	xCLSSE069					:1;				/* ECMCLSSE069 */
					U4	xCLSSE070					:1;				/* ECMCLSSE070 */
					U4	xCLSSE071					:1;				/* ECMCLSSE071 */
					U4	xCLSSE072					:1;				/* ECMCLSSE072 */
					U4	xCLSSE073					:1;				/* ECMCLSSE073 */
					U4	xCLSSE074					:1;				/* ECMCLSSE074 */
					U4	xCLSSE075					:1;				/* ECMCLSSE075 */
					U4	xCLSSE076					:1;				/* ECMCLSSE076 */
					U4	xCLSSE077					:1;				/* ECMCLSSE077 */
					U4	xCLSSE078					:1;				/* ECMCLSSE078 */
					U4	xCLSSE079					:1;				/* ECMCLSSE079 */
					U4	xCLSSE080					:1;				/* ECMCLSSE080 */
					U4	xCLSSE081					:1;				/* ECMCLSSE081 */
					U4	xCLSSE082					:1;				/* ECMCLSSE082 */
					U4	xCLSSE083					:1;				/* ECMCLSSE083 */
					U4	xCLSSE084					:1;				/* ECMCLSSE084 */
					U4	xCLSSE085					:1;				/* ECMCLSSE085 */
					U4	xCLSSE086					:1;				/* ECMCLSSE086 */
					U4	xCLSSE087					:1;				/* ECMCLSSE087 */
					U4	xCLSSE088					:1;				/* ECMCLSSE088 */
					U4	xCLSSE089					:1;				/* ECMCLSSE089 */
					U4	xCLSSE090					:1;				/* ECMCLSSE090 */
					U4	xCLSSE091					:1;				/* ECMCLSSE091 */
					U4	xCLSSE092					:1;				/* ECMCLSSE092 */
					U4	xCLSSE093					:1;				/* ECMCLSSE093 */
					U4	xCLSSE094					:1;				/* ECMCLSSE094 */
					U4	xCLSSE095					:1;				/* ECMCLSSE095 */
				} stBit;
			} unECMESSTC2;										/* 0xFFD38480 */

			union												/* ECMESSTC3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE096					:1;				/* ECMCLSSE096 */
					U4	xCLSSE097					:1;				/* ECMCLSSE097 */
					U4	xCLSSE098					:1;				/* ECMCLSSE098 */
					U4	xCLSSE099					:1;				/* ECMCLSSE099 */
					U4	xCLSSE100					:1;				/* ECMCLSSE100 */
					U4	xCLSSE101					:1;				/* ECMCLSSE101 */
					U4	xCLSSE102					:1;				/* ECMCLSSE102 */
					U4	xCLSSE103					:1;				/* ECMCLSSE103 */
					U4	xCLSSE104					:1;				/* ECMCLSSE104 */
					U4	xCLSSE105					:1;				/* ECMCLSSE105 */
					U4	xCLSSE106					:1;				/* ECMCLSSE106 */
					U4	xCLSSE107					:1;				/* ECMCLSSE107 */
					U4	xCLSSE108					:1;				/* ECMCLSSE108 */
					U4	xCLSSE109					:1;				/* ECMCLSSE109 */
					U4	xCLSSE110					:1;				/* ECMCLSSE110 */
					U4	xCLSSE111					:1;				/* ECMCLSSE111 */
					U4	xCLSSE112					:1;				/* ECMCLSSE112 */
					U4	xCLSSE113					:1;				/* ECMCLSSE113 */
					U4	xCLSSE114					:1;				/* ECMCLSSE114 */
					U4	xCLSSE115					:1;				/* ECMCLSSE115 */
					U4	xCLSSE116					:1;				/* ECMCLSSE116 */
					U4	xCLSSE117					:1;				/* ECMCLSSE117 */
					U4	xCLSSE118					:1;				/* ECMCLSSE118 */
					U4	xCLSSE119					:1;				/* ECMCLSSE119 */
					U4	xCLSSE120					:1;				/* ECMCLSSE120 */
					U4	xCLSSE121					:1;				/* ECMCLSSE121 */
					U4	xCLSSE122					:1;				/* ECMCLSSE122 */
					U4	xCLSSE123					:1;				/* ECMCLSSE123 */
					U4	xCLSSE124					:1;				/* ECMCLSSE124 */
					U4	xCLSSE125					:1;				/* ECMCLSSE125 */
					U4	xCLSSE126					:1;				/* ECMCLSSE126 */
					U4	xCLSSE127					:1;				/* ECMCLSSE127 */
				} stBit;
			} unECMESSTC3;										/* 0xFFD38484 */

			union												/* ECMESSTC4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE128					:1;				/* ECMCLSSE128 */
					U4	xCLSSE129					:1;				/* ECMCLSSE129 */
					U4	xCLSSE130					:1;				/* ECMCLSSE130 */
					U4	xCLSSE131					:1;				/* ECMCLSSE131 */
					U4	xCLSSE132					:1;				/* ECMCLSSE132 */
					U4	xCLSSE133					:1;				/* ECMCLSSE133 */
					U4	xCLSSE134					:1;				/* ECMCLSSE134 */
					U4	xCLSSE135					:1;				/* ECMCLSSE135 */
					U4	xCLSSE136					:1;				/* ECMCLSSE136 */
					U4	xCLSSE137					:1;				/* ECMCLSSE137 */
					U4	xCLSSE138					:1;				/* ECMCLSSE138 */
					U4	xCLSSE139					:1;				/* ECMCLSSE139 */
					U4	xCLSSE140					:1;				/* ECMCLSSE140 */
					U4	xCLSSE141					:1;				/* ECMCLSSE141 */
					U4	xCLSSE142					:1;				/* ECMCLSSE142 */
					U4	xCLSSE143					:1;				/* ECMCLSSE143 */
					U4	xCLSSE144					:1;				/* ECMCLSSE144 */
					U4	xCLSSE145					:1;				/* ECMCLSSE145 */
					U4	xCLSSE146					:1;				/* ECMCLSSE146 */
					U4	xCLSSE147					:1;				/* ECMCLSSE147 */
					U4	xCLSSE148					:1;				/* ECMCLSSE148 */
					U4	xCLSSE149					:1;				/* ECMCLSSE149 */
					U4	xCLSSE150					:1;				/* ECMCLSSE150 */
					U4	xCLSSE151					:1;				/* ECMCLSSE151 */
					U4	xCLSSE152					:1;				/* ECMCLSSE152 */
					U4	xCLSSE153					:1;				/* ECMCLSSE153 */
					U4	xCLSSE154					:1;				/* ECMCLSSE154 */
					U4	xCLSSE155					:1;				/* ECMCLSSE155 */
					U4	xCLSSE156					:1;				/* ECMCLSSE156 */
					U4	xCLSSE157					:1;				/* ECMCLSSE157 */
					U4	xCLSSE158					:1;				/* ECMCLSSE158 */
					U4	xCLSSE159					:1;				/* ECMCLSSE159 */
				} stBit;
			} unECMESSTC4;										/* 0xFFD38488 */

			union												/* ECMESSTC5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE160					:1;				/* ECMCLSSE160 */
					U4	xCLSSE161					:1;				/* ECMCLSSE161 */
					U4	xCLSSE162					:1;				/* ECMCLSSE162 */
					U4	xCLSSE163					:1;				/* ECMCLSSE163 */
					U4	xCLSSE164					:1;				/* ECMCLSSE164 */
					U4	xCLSSE165					:1;				/* ECMCLSSE165 */
					U4	xCLSSE166					:1;				/* ECMCLSSE166 */
					U4	xCLSSE167					:1;				/* ECMCLSSE167 */
					U4	xCLSSE168					:1;				/* ECMCLSSE168 */
					U4	xCLSSE169					:1;				/* ECMCLSSE169 */
					U4	xCLSSE170					:1;				/* ECMCLSSE170 */
					U4	xCLSSE171					:1;				/* ECMCLSSE171 */
					U4	xCLSSE172					:1;				/* ECMCLSSE172 */
					U4	xCLSSE173					:1;				/* ECMCLSSE173 */
					U4	xCLSSE174					:1;				/* ECMCLSSE174 */
					U4	xCLSSE175					:1;				/* ECMCLSSE175 */
					U4	xCLSSE176					:1;				/* ECMCLSSE176 */
					U4	xCLSSE177					:1;				/* ECMCLSSE177 */
					U4	xCLSSE178					:1;				/* ECMCLSSE178 */
					U4	xCLSSE179					:1;				/* ECMCLSSE179 */
					U4	xCLSSE180					:1;				/* ECMCLSSE180 */
					U4	xCLSSE181					:1;				/* ECMCLSSE181 */
					U4	xCLSSE182					:1;				/* ECMCLSSE182 */
					U4	xCLSSE183					:1;				/* ECMCLSSE183 */
					U4	xCLSSE184					:1;				/* ECMCLSSE184 */
					U4	xCLSSE185					:1;				/* ECMCLSSE185 */
					U4	xCLSSE186					:1;				/* ECMCLSSE186 */
					U4	xCLSSE187					:1;				/* ECMCLSSE187 */
					U4	xCLSSE188					:1;				/* ECMCLSSE188 */
					U4	xCLSSE189					:1;				/* ECMCLSSE189 */
					U4	xCLSSE190					:1;				/* ECMCLSSE190 */
					U4	xCLSSE191					:1;				/* ECMCLSSE191 */
				} stBit;
			} unECMESSTC5;										/* 0xFFD3848C */

			union												/* ECMESSTC6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE192					:1;				/* ECMCLSSE192 */
					U4	xCLSSE193					:1;				/* ECMCLSSE193 */
					U4	xCLSSE194					:1;				/* ECMCLSSE194 */
					U4	xCLSSE195					:1;				/* ECMCLSSE195 */
					U4	xCLSSE196					:1;				/* ECMCLSSE196 */
					U4	xCLSSE197					:1;				/* ECMCLSSE197 */
					U4	xCLSSE198					:1;				/* ECMCLSSE198 */
					U4	xCLSSE199					:1;				/* ECMCLSSE199 */
					U4	xCLSSE200					:1;				/* ECMCLSSE200 */
					U4	xCLSSE201					:1;				/* ECMCLSSE201 */
					U4	xCLSSE202					:1;				/* ECMCLSSE202 */
					U4	xCLSSE203					:1;				/* ECMCLSSE203 */
					U4	xCLSSE204					:1;				/* ECMCLSSE204 */
					U4	xCLSSE205					:1;				/* ECMCLSSE205 */
					U4	xCLSSE206					:1;				/* ECMCLSSE206 */
					U4	xCLSSE207					:1;				/* ECMCLSSE207 */
					U4	xCLSSE208					:1;				/* ECMCLSSE208 */
					U4	xCLSSE209					:1;				/* ECMCLSSE209 */
					U4	xCLSSE210					:1;				/* ECMCLSSE210 */
					U4	xCLSSE211					:1;				/* ECMCLSSE211 */
					U4	xCLSSE212					:1;				/* ECMCLSSE212 */
					U4	xCLSSE213					:1;				/* ECMCLSSE213 */
					U4	xCLSSE214					:1;				/* ECMCLSSE214 */
					U4	xCLSSE215					:1;				/* ECMCLSSE215 */
					U4	xCLSSE216					:1;				/* ECMCLSSE216 */
					U4	xCLSSE217					:1;				/* ECMCLSSE217 */
					U4	xCLSSE218					:1;				/* ECMCLSSE218 */
					U4	xCLSSE219					:1;				/* ECMCLSSE219 */
					U4	xCLSSE220					:1;				/* ECMCLSSE220 */
					U4	xCLSSE221					:1;				/* ECMCLSSE221 */
					U4	xCLSSE222					:1;				/* ECMCLSSE222 */
					U4	xCLSSE223					:1;				/* ECMCLSSE223 */
				} stBit;
			} unECMESSTC6;										/* 0xFFD38490 */

			union												/* ECMESSTC7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE224					:1;				/* ECMCLSSE224 */
					U4	xCLSSE225					:1;				/* ECMCLSSE225 */
					U4	xCLSSE226					:1;				/* ECMCLSSE226 */
					U4	xCLSSE227					:1;				/* ECMCLSSE227 */
					U4	xCLSSE228					:1;				/* ECMCLSSE228 */
					U4	xCLSSE229					:1;				/* ECMCLSSE229 */
					U4	xCLSSE230					:1;				/* ECMCLSSE230 */
					U4	xCLSSE231					:1;				/* ECMCLSSE231 */
					U4	xCLSSE232					:1;				/* ECMCLSSE232 */
					U4	xCLSSE233					:1;				/* ECMCLSSE233 */
					U4	xCLSSE234					:1;				/* ECMCLSSE234 */
					U4	xCLSSE235					:1;				/* ECMCLSSE235 */
					U4	xCLSSE236					:1;				/* ECMCLSSE236 */
					U4	xCLSSE237					:1;				/* ECMCLSSE237 */
					U4	xCLSSE238					:1;				/* ECMCLSSE238 */
					U4	xCLSSE239					:1;				/* ECMCLSSE239 */
					U4	xCLSSE240					:1;				/* ECMCLSSE240 */
					U4	xCLSSE241					:1;				/* ECMCLSSE241 */
					U4	xCLSSE242					:1;				/* ECMCLSSE242 */
					U4	xCLSSE243					:1;				/* ECMCLSSE243 */
					U4	xCLSSE244					:1;				/* ECMCLSSE244 */
					U4	xCLSSE245					:1;				/* ECMCLSSE245 */
					U4	xCLSSE246					:1;				/* ECMCLSSE246 */
					U4	xCLSSE247					:1;				/* ECMCLSSE247 */
					U4	xCLSSE248					:1;				/* ECMCLSSE248 */
					U4	xCLSSE249					:1;				/* ECMCLSSE249 */
					U4	xCLSSE250					:1;				/* ECMCLSSE250 */
					U4	xCLSSE251					:1;				/* ECMCLSSE251 */
					U4	xCLSSE252					:1;				/* ECMCLSSE252 */
					U4	xCLSSE253					:1;				/* ECMCLSSE253 */
					U4	xCLSSE254					:1;				/* ECMCLSSE254 */
					U4	xCLSSE255					:1;				/* ECMCLSSE255 */
				} stBit;
			} unECMESSTC7;										/* 0xFFD38494 */

			union												/* ECMESSTC8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE256					:1;				/* ECMCLSSE256 */
					U4	xCLSSE257					:1;				/* ECMCLSSE257 */
					U4	xCLSSE258					:1;				/* ECMCLSSE258 */
					U4	xCLSSE259					:1;				/* ECMCLSSE259 */
					U4	xCLSSE260					:1;				/* ECMCLSSE260 */
					U4	xCLSSE261					:1;				/* ECMCLSSE261 */
					U4	xCLSSE262					:1;				/* ECMCLSSE262 */
					U4	xCLSSE263					:1;				/* ECMCLSSE263 */
					U4	xCLSSE264					:1;				/* ECMCLSSE264 */
					U4	xCLSSE265					:1;				/* ECMCLSSE265 */
					U4	xCLSSE266					:1;				/* ECMCLSSE266 */
					U4	xCLSSE267					:1;				/* ECMCLSSE267 */
					U4	xCLSSE268					:1;				/* ECMCLSSE268 */
					U4	xCLSSE269					:1;				/* ECMCLSSE269 */
					U4	xCLSSE270					:1;				/* ECMCLSSE270 */
					U4	xCLSSE271					:1;				/* ECMCLSSE271 */
					U4	xCLSSE272					:1;				/* ECMCLSSE272 */
					U4	xCLSSE273					:1;				/* ECMCLSSE273 */
					U4	xCLSSE274					:1;				/* ECMCLSSE274 */
					U4	xCLSSE275					:1;				/* ECMCLSSE275 */
					U4	xCLSSE276					:1;				/* ECMCLSSE276 */
					U4	xCLSSE277					:1;				/* ECMCLSSE277 */
					U4	xCLSSE278					:1;				/* ECMCLSSE278 */
					U4	xCLSSE279					:1;				/* ECMCLSSE279 */
					U4	xCLSSE280					:1;				/* ECMCLSSE280 */
					U4	xCLSSE281					:1;				/* ECMCLSSE281 */
					U4	xCLSSE282					:1;				/* ECMCLSSE282 */
					U4	xCLSSE283					:1;				/* ECMCLSSE283 */
					U4	xCLSSE284					:1;				/* ECMCLSSE284 */
					U4	xCLSSE285					:1;				/* ECMCLSSE285 */
					U4	xCLSSE286					:1;				/* ECMCLSSE286 */
					U4	xCLSSE287					:1;				/* ECMCLSSE287 */
				} stBit;
			} unECMESSTC8;										/* 0xFFD38498 */

			union												/* ECMESSTC9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE288					:1;				/* ECMCLSSE288 */
					U4	xCLSSE289					:1;				/* ECMCLSSE289 */
					U4	xCLSSE290					:1;				/* ECMCLSSE290 */
					U4	xCLSSE291					:1;				/* ECMCLSSE291 */
					U4	xCLSSE292					:1;				/* ECMCLSSE292 */
					U4	xCLSSE293					:1;				/* ECMCLSSE293 */
					U4	xCLSSE294					:1;				/* ECMCLSSE294 */
					U4	xCLSSE295					:1;				/* ECMCLSSE295 */
					U4	xCLSSE296					:1;				/* ECMCLSSE296 */
					U4	xCLSSE297					:1;				/* ECMCLSSE297 */
					U4	xCLSSE298					:1;				/* ECMCLSSE298 */
					U4	xCLSSE299					:1;				/* ECMCLSSE299 */
					U4	xCLSSE300					:1;				/* ECMCLSSE300 */
					U4	xCLSSE301					:1;				/* ECMCLSSE301 */
					U4	xCLSSE302					:1;				/* ECMCLSSE302 */
					U4	xCLSSE303					:1;				/* ECMCLSSE303 */
					U4	xCLSSE304					:1;				/* ECMCLSSE304 */
					U4	xCLSSE305					:1;				/* ECMCLSSE305 */
					U4	xCLSSE306					:1;				/* ECMCLSSE306 */
					U4	xCLSSE307					:1;				/* ECMCLSSE307 */
					U4	xCLSSE308					:1;				/* ECMCLSSE308 */
					U4	xCLSSE309					:1;				/* ECMCLSSE309 */
					U4	xCLSSE310					:1;				/* ECMCLSSE310 */
					U4	xCLSSE311					:1;				/* ECMCLSSE311 */
					U4	xCLSSE312					:1;				/* ECMCLSSE312 */
					U4	xCLSSE313					:1;				/* ECMCLSSE313 */
					U4	xCLSSE314					:1;				/* ECMCLSSE314 */
					U4	xCLSSE315					:1;				/* ECMCLSSE315 */
					U4	xCLSSE316					:1;				/* ECMCLSSE316 */
					U4	xCLSSE317					:1;				/* ECMCLSSE317 */
					U4	xCLSSE318					:1;				/* ECMCLSSE318 */
					U4	xCLSSE319					:1;				/* ECMCLSSE319 */
				} stBit;
			} unECMESSTC9;										/* 0xFFD3849C */

			union												/* ECMESSTC10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xCLSSE320					:1;				/* ECMCLSSE320 */
					U4	xCLSSE321					:1;				/* ECMCLSSE321 */
					U4	xCLSSE322					:1;				/* ECMCLSSE322 */
					U4	xCLSSE323					:1;				/* ECMCLSSE323 */
					U4	xCLSSE324					:1;				/* ECMCLSSE324 */
					U4	xCLSSE325					:1;				/* ECMCLSSE325 */
					U4	xCLSSE326					:1;				/* ECMCLSSE326 */
					U4	xCLSSE327					:1;				/* ECMCLSSE327 */
					U4	xCLSSE328					:1;				/* ECMCLSSE328 */
					U4	xCLSSE329					:1;				/* ECMCLSSE329 */
					U4	xCLSSE330					:1;				/* ECMCLSSE330 */
					U4	xCLSSE331					:1;				/* ECMCLSSE331 */
					U4	xCLSSE332					:1;				/* ECMCLSSE332 */
					U4	xCLSSE333					:1;				/* ECMCLSSE333 */
					U4	xCLSSE334					:1;				/* ECMCLSSE334 */
					U4	xCLSSE335					:1;				/* ECMCLSSE335 */
					U4	xCLSSE336					:1;				/* ECMCLSSE336 */
					U4	xCLSSE337					:1;				/* ECMCLSSE337 */
					U4	xCLSSE338					:1;				/* ECMCLSSE338 */
					U4	xCLSSE339					:1;				/* ECMCLSSE339 */
					U4	xCLSSE340					:1;				/* ECMCLSSE340 */
					U4	xCLSSE341					:1;				/* ECMCLSSE341 */
					U4	xCLSSE342					:1;				/* ECMCLSSE342 */
					U4	xCLSSE343					:1;				/* ECMCLSSE343 */
					U4	xCLSSE344					:1;				/* ECMCLSSE344 */
					U4	xCLSSE345					:1;				/* ECMCLSSE345 */
					U4	xCLSSE346					:1;				/* ECMCLSSE346 */
					U4	xCLSSE347					:1;				/* ECMCLSSE347 */
					U4	xCLSSE348					:1;				/* ECMCLSSE348 */
					U4	xCLSSE349					:1;				/* ECMCLSSE349 */
					U4	xCLSSE350					:1;				/* ECMCLSSE350 */
					U4	xCLSSE351					:1;				/* ECMCLSSE351 */
				} stBit;
			} unECMESSTC10;										/* 0xFFD384A0 */
		} stECMESSTCn;
	} unECMESSTCn;

	U1	u1Dummy16[16];	/* 0xFFD384A4 - 0xFFD384B4 */

	union
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	xKCE					:1;						/* KCE	*/
			U4	b31KCPROT				:31;					/* KCPROT */
		} stBit;
	} unECMKCPROT;												/* 0xFFD384B4 */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMPE0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE000					:1;				/* ECMPE000 */
					U4	xPE001					:1;				/* ECMPE001 */
					U4	xPE002					:1;				/* ECMPE002 */
					U4	xPE003					:1;				/* ECMPE003 */
					U4	xPE004					:1;				/* ECMPE004 */
					U4	xPE005					:1;				/* ECMPE005 */
					U4	xPE006					:1;				/* ECMPE006 */
					U4	xPE007					:1;				/* ECMPE007 */
					U4	xPE008					:1;				/* ECMPE008 */
					U4	xPE009					:1;				/* ECMPE009 */
					U4	xPE010					:1;				/* ECMPE010 */
					U4	xPE011					:1;				/* ECMPE011 */
					U4	xPE012					:1;				/* ECMPE012 */
					U4	xPE013					:1;				/* ECMPE013 */
					U4	xPE014					:1;				/* ECMPE014 */
					U4	xPE015					:1;				/* ECMPE015 */
					U4	xPE016					:1;				/* ECMPE016 */
					U4	xPE017					:1;				/* ECMPE017 */
					U4	xPE018					:1;				/* ECMPE018 */
					U4	xPE019					:1;				/* ECMPE019 */
					U4	xPE020					:1;				/* ECMPE020 */
					U4	xPE021					:1;				/* ECMPE021 */
					U4	xPE022					:1;				/* ECMPE022 */
					U4	xPE023					:1;				/* ECMPE023 */
					U4	xPE024					:1;				/* ECMPE024 */
					U4	xPE025					:1;				/* ECMPE025 */
					U4	xPE026					:1;				/* ECMPE026 */
					U4	xPE027					:1;				/* ECMPE027 */
					U4	xPE028					:1;				/* ECMPE028 */
					U4	xPE029					:1;				/* ECMPE029 */
					U4	xPE030					:1;				/* ECMPE030 */
					U4	xPE031					:1;				/* ECMPE031 */
				} stBit;
			} unECMPE0;										/* 0xFFD384B8 */

			union												/* ECMPE1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE032					:1;				/* ECMPE032 */
					U4	xPE033					:1;				/* ECMPE033 */
					U4	xPE034					:1;				/* ECMPE034 */
					U4	xPE035					:1;				/* ECMPE035 */
					U4	xPE036					:1;				/* ECMPE036 */
					U4	xPE037					:1;				/* ECMPE037 */
					U4	xPE038					:1;				/* ECMPE038 */
					U4	xPE039					:1;				/* ECMPE039 */
					U4	xPE040					:1;				/* ECMPE040 */
					U4	xPE041					:1;				/* ECMPE041 */
					U4	xPE042					:1;				/* ECMPE042 */
					U4	xPE043					:1;				/* ECMPE043 */
					U4	xPE044					:1;				/* ECMPE044 */
					U4	xPE045					:1;				/* ECMPE045 */
					U4	xPE046					:1;				/* ECMPE046 */
					U4	xPE047					:1;				/* ECMPE047 */
					U4	xPE048					:1;				/* ECMPE048 */
					U4	xPE049					:1;				/* ECMPE049 */
					U4	xPE050					:1;				/* ECMPE050 */
					U4	xPE051					:1;				/* ECMPE051 */
					U4	xPE052					:1;				/* ECMPE052 */
					U4	xPE053					:1;				/* ECMPE053 */
					U4	xPE054					:1;				/* ECMPE054 */
					U4	xPE055					:1;				/* ECMPE055 */
					U4	xPE056					:1;				/* ECMPE056 */
					U4	xPE057					:1;				/* ECMPE057 */
					U4	xPE058					:1;				/* ECMPE058 */
					U4	xPE059					:1;				/* ECMPE059 */
					U4	xPE060					:1;				/* ECMPE060 */
					U4	xPE061					:1;				/* ECMPE061 */
					U4	xPE062					:1;				/* ECMPE062 */
					U4	xPE063					:1;				/* ECMPE063 */
				} stBit;
			} unECMPE1;										/* 0xFFD384BC */

			union												/* ECMPE2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE064					:1;				/* ECMPE064 */
					U4	xPE065					:1;				/* ECMPE065 */
					U4	xPE066					:1;				/* ECMPE066 */
					U4	xPE067					:1;				/* ECMPE067 */
					U4	xPE068					:1;				/* ECMPE068 */
					U4	xPE069					:1;				/* ECMPE069 */
					U4	xPE070					:1;				/* ECMPE070 */
					U4	xPE071					:1;				/* ECMPE071 */
					U4	xPE072					:1;				/* ECMPE072 */
					U4	xPE073					:1;				/* ECMPE073 */
					U4	xPE074					:1;				/* ECMPE074 */
					U4	xPE075					:1;				/* ECMPE075 */
					U4	xPE076					:1;				/* ECMPE076 */
					U4	xPE077					:1;				/* ECMPE077 */
					U4	xPE078					:1;				/* ECMPE078 */
					U4	xPE079					:1;				/* ECMPE079 */
					U4	xPE080					:1;				/* ECMPE080 */
					U4	xPE081					:1;				/* ECMPE081 */
					U4	xPE082					:1;				/* ECMPE082 */
					U4	xPE083					:1;				/* ECMPE083 */
					U4	xPE084					:1;				/* ECMPE084 */
					U4	xPE085					:1;				/* ECMPE085 */
					U4	xPE086					:1;				/* ECMPE086 */
					U4	xPE087					:1;				/* ECMPE087 */
					U4	xPE088					:1;				/* ECMPE088 */
					U4	xPE089					:1;				/* ECMPE089 */
					U4	xPE090					:1;				/* ECMPE090 */
					U4	xPE091					:1;				/* ECMPE091 */
					U4	xPE092					:1;				/* ECMPE092 */
					U4	xPE093					:1;				/* ECMPE093 */
					U4	xPE094					:1;				/* ECMPE094 */
					U4	xPE095					:1;				/* ECMPE095 */
				} stBit;
			} unECMPE2;										/* 0xFFD384C0 */

			union												/* ECMPE3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE096					:1;				/* ECMPE096 */
					U4	xPE097					:1;				/* ECMPE097 */
					U4	xPE098					:1;				/* ECMPE098 */
					U4	xPE099					:1;				/* ECMPE099 */
					U4	xPE100					:1;				/* ECMPE100 */
					U4	xPE101					:1;				/* ECMPE101 */
					U4	xPE102					:1;				/* ECMPE102 */
					U4	xPE103					:1;				/* ECMPE103 */
					U4	xPE104					:1;				/* ECMPE104 */
					U4	xPE105					:1;				/* ECMPE105 */
					U4	xPE106					:1;				/* ECMPE106 */
					U4	xPE107					:1;				/* ECMPE107 */
					U4	xPE108					:1;				/* ECMPE108 */
					U4	xPE109					:1;				/* ECMPE109 */
					U4	xPE110					:1;				/* ECMPE110 */
					U4	xPE111					:1;				/* ECMPE111 */
					U4	xPE112					:1;				/* ECMPE112 */
					U4	xPE113					:1;				/* ECMPE113 */
					U4	xPE114					:1;				/* ECMPE114 */
					U4	xPE115					:1;				/* ECMPE115 */
					U4	xPE116					:1;				/* ECMPE116 */
					U4	xPE117					:1;				/* ECMPE117 */
					U4	xPE118					:1;				/* ECMPE118 */
					U4	xPE119					:1;				/* ECMPE119 */
					U4	xPE120					:1;				/* ECMPE120 */
					U4	xPE121					:1;				/* ECMPE121 */
					U4	xPE122					:1;				/* ECMPE122 */
					U4	xPE123					:1;				/* ECMPE123 */
					U4	xPE124					:1;				/* ECMPE124 */
					U4	xPE125					:1;				/* ECMPE125 */
					U4	xPE126					:1;				/* ECMPE126 */
					U4	xPE127					:1;				/* ECMPE127 */
				} stBit;
			} unECMPE3;										/* 0xFFD384C4 */

			union												/* ECMPE4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE128					:1;				/* ECMPE128 */
					U4	xPE129					:1;				/* ECMPE129 */
					U4	xPE130					:1;				/* ECMPE130 */
					U4	xPE131					:1;				/* ECMPE131 */
					U4	xPE132					:1;				/* ECMPE132 */
					U4	xPE133					:1;				/* ECMPE133 */
					U4	xPE134					:1;				/* ECMPE134 */
					U4	xPE135					:1;				/* ECMPE135 */
					U4	xPE136					:1;				/* ECMPE136 */
					U4	xPE137					:1;				/* ECMPE137 */
					U4	xPE138					:1;				/* ECMPE138 */
					U4	xPE139					:1;				/* ECMPE139 */
					U4	xPE140					:1;				/* ECMPE140 */
					U4	xPE141					:1;				/* ECMPE141 */
					U4	xPE142					:1;				/* ECMPE142 */
					U4	xPE143					:1;				/* ECMPE143 */
					U4	xPE144					:1;				/* ECMPE144 */
					U4	xPE145					:1;				/* ECMPE145 */
					U4	xPE146					:1;				/* ECMPE146 */
					U4	xPE147					:1;				/* ECMPE147 */
					U4	xPE148					:1;				/* ECMPE148 */
					U4	xPE149					:1;				/* ECMPE149 */
					U4	xPE150					:1;				/* ECMPE150 */
					U4	xPE151					:1;				/* ECMPE151 */
					U4	xPE152					:1;				/* ECMPE152 */
					U4	xPE153					:1;				/* ECMPE153 */
					U4	xPE154					:1;				/* ECMPE154 */
					U4	xPE155					:1;				/* ECMPE155 */
					U4	xPE156					:1;				/* ECMPE156 */
					U4	xPE157					:1;				/* ECMPE157 */
					U4	xPE158					:1;				/* ECMPE158 */
					U4	xPE159					:1;				/* ECMPE159 */
				} stBit;
			} unECMPE4;										/* 0xFFD384C8 */

			union												/* ECMPE5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE160					:1;				/* ECMPE160 */
					U4	xPE161					:1;				/* ECMPE161 */
					U4	xPE162					:1;				/* ECMPE162 */
					U4	xPE163					:1;				/* ECMPE163 */
					U4	xPE164					:1;				/* ECMPE164 */
					U4	xPE165					:1;				/* ECMPE165 */
					U4	xPE166					:1;				/* ECMPE166 */
					U4	xPE167					:1;				/* ECMPE167 */
					U4	xPE168					:1;				/* ECMPE168 */
					U4	xPE169					:1;				/* ECMPE169 */
					U4	xPE170					:1;				/* ECMPE170 */
					U4	xPE171					:1;				/* ECMPE171 */
					U4	xPE172					:1;				/* ECMPE172 */
					U4	xPE173					:1;				/* ECMPE173 */
					U4	xPE174					:1;				/* ECMPE174 */
					U4	xPE175					:1;				/* ECMPE175 */
					U4	xPE176					:1;				/* ECMPE176 */
					U4	xPE177					:1;				/* ECMPE177 */
					U4	xPE178					:1;				/* ECMPE178 */
					U4	xPE179					:1;				/* ECMPE179 */
					U4	xPE180					:1;				/* ECMPE180 */
					U4	xPE181					:1;				/* ECMPE181 */
					U4	xPE182					:1;				/* ECMPE182 */
					U4	xPE183					:1;				/* ECMPE183 */
					U4	xPE184					:1;				/* ECMPE184 */
					U4	xPE185					:1;				/* ECMPE185 */
					U4	xPE186					:1;				/* ECMPE186 */
					U4	xPE187					:1;				/* ECMPE187 */
					U4	xPE188					:1;				/* ECMPE188 */
					U4	xPE189					:1;				/* ECMPE189 */
					U4	xPE190					:1;				/* ECMPE190 */
					U4	xPE191					:1;				/* ECMPE191 */
				} stBit;
			} unECMPE5;										/* 0xFFD384CC */

			union												/* ECMPE6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE192					:1;				/* ECMPE192 */
					U4	xPE193					:1;				/* ECMPE193 */
					U4	xPE194					:1;				/* ECMPE194 */
					U4	xPE195					:1;				/* ECMPE195 */
					U4	xPE196					:1;				/* ECMPE196 */
					U4	xPE197					:1;				/* ECMPE197 */
					U4	xPE198					:1;				/* ECMPE198 */
					U4	xPE199					:1;				/* ECMPE199 */
					U4	xPE200					:1;				/* ECMPE200 */
					U4	xPE201					:1;				/* ECMPE201 */
					U4	xPE202					:1;				/* ECMPE202 */
					U4	xPE203					:1;				/* ECMPE203 */
					U4	xPE204					:1;				/* ECMPE204 */
					U4	xPE205					:1;				/* ECMPE205 */
					U4	xPE206					:1;				/* ECMPE206 */
					U4	xPE207					:1;				/* ECMPE207 */
					U4	xPE208					:1;				/* ECMPE208 */
					U4	xPE209					:1;				/* ECMPE209 */
					U4	xPE210					:1;				/* ECMPE210 */
					U4	xPE211					:1;				/* ECMPE211 */
					U4	xPE212					:1;				/* ECMPE212 */
					U4	xPE213					:1;				/* ECMPE213 */
					U4	xPE214					:1;				/* ECMPE214 */
					U4	xPE215					:1;				/* ECMPE215 */
					U4	xPE216					:1;				/* ECMPE216 */
					U4	xPE217					:1;				/* ECMPE217 */
					U4	xPE218					:1;				/* ECMPE218 */
					U4	xPE219					:1;				/* ECMPE219 */
					U4	xPE220					:1;				/* ECMPE220 */
					U4	xPE221					:1;				/* ECMPE221 */
					U4	xPE222					:1;				/* ECMPE222 */
					U4	xPE223					:1;				/* ECMPE223 */
				} stBit;
			} unECMPE6;										/* 0xFFD384D0 */

			union												/* ECMPE7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE224					:1;				/* ECMPE224 */
					U4	xPE225					:1;				/* ECMPE225 */
					U4	xPE226					:1;				/* ECMPE226 */
					U4	xPE227					:1;				/* ECMPE227 */
					U4	xPE228					:1;				/* ECMPE228 */
					U4	xPE229					:1;				/* ECMPE229 */
					U4	xPE230					:1;				/* ECMPE230 */
					U4	xPE231					:1;				/* ECMPE231 */
					U4	xPE232					:1;				/* ECMPE232 */
					U4	xPE233					:1;				/* ECMPE233 */
					U4	xPE234					:1;				/* ECMPE234 */
					U4	xPE235					:1;				/* ECMPE235 */
					U4	xPE236					:1;				/* ECMPE236 */
					U4	xPE237					:1;				/* ECMPE237 */
					U4	xPE238					:1;				/* ECMPE238 */
					U4	xPE239					:1;				/* ECMPE239 */
					U4	xPE240					:1;				/* ECMPE240 */
					U4	xPE241					:1;				/* ECMPE241 */
					U4	xPE242					:1;				/* ECMPE242 */
					U4	xPE243					:1;				/* ECMPE243 */
					U4	xPE244					:1;				/* ECMPE244 */
					U4	xPE245					:1;				/* ECMPE245 */
					U4	xPE246					:1;				/* ECMPE246 */
					U4	xPE247					:1;				/* ECMPE247 */
					U4	xPE248					:1;				/* ECMPE248 */
					U4	xPE249					:1;				/* ECMPE249 */
					U4	xPE250					:1;				/* ECMPE250 */
					U4	xPE251					:1;				/* ECMPE251 */
					U4	xPE252					:1;				/* ECMPE252 */
					U4	xPE253					:1;				/* ECMPE253 */
					U4	xPE254					:1;				/* ECMPE254 */
					U4	xPE255					:1;				/* ECMPE255 */
				} stBit;
			} unECMPE7;										/* 0xFFD384D4 */

			union												/* ECMPE8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE256					:1;				/* ECMPE256 */
					U4	xPE257					:1;				/* ECMPE257 */
					U4	xPE258					:1;				/* ECMPE258 */
					U4	xPE259					:1;				/* ECMPE259 */
					U4	xPE260					:1;				/* ECMPE260 */
					U4	xPE261					:1;				/* ECMPE261 */
					U4	xPE262					:1;				/* ECMPE262 */
					U4	xPE263					:1;				/* ECMPE263 */
					U4	xPE264					:1;				/* ECMPE264 */
					U4	xPE265					:1;				/* ECMPE265 */
					U4	xPE266					:1;				/* ECMPE266 */
					U4	xPE267					:1;				/* ECMPE267 */
					U4	xPE268					:1;				/* ECMPE268 */
					U4	xPE269					:1;				/* ECMPE269 */
					U4	xPE270					:1;				/* ECMPE270 */
					U4	xPE271					:1;				/* ECMPE271 */
					U4	xPE272					:1;				/* ECMPE272 */
					U4	xPE273					:1;				/* ECMPE273 */
					U4	xPE274					:1;				/* ECMPE274 */
					U4	xPE275					:1;				/* ECMPE275 */
					U4	xPE276					:1;				/* ECMPE276 */
					U4	xPE277					:1;				/* ECMPE277 */
					U4	xPE278					:1;				/* ECMPE278 */
					U4	xPE279					:1;				/* ECMPE279 */
					U4	xPE280					:1;				/* ECMPE280 */
					U4	xPE281					:1;				/* ECMPE281 */
					U4	xPE282					:1;				/* ECMPE282 */
					U4	xPE283					:1;				/* ECMPE283 */
					U4	xPE284					:1;				/* ECMPE284 */
					U4	xPE285					:1;				/* ECMPE285 */
					U4	xPE286					:1;				/* ECMPE286 */
					U4	xPE287					:1;				/* ECMPE287 */
				} stBit;
			} unECMPE8;										/* 0xFFD384D8 */

			union												/* ECMPE9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE288					:1;				/* ECMPE288 */
					U4	xPE289					:1;				/* ECMPE289 */
					U4	xPE290					:1;				/* ECMPE290 */
					U4	xPE291					:1;				/* ECMPE291 */
					U4	xPE292					:1;				/* ECMPE292 */
					U4	xPE293					:1;				/* ECMPE293 */
					U4	xPE294					:1;				/* ECMPE294 */
					U4	xPE295					:1;				/* ECMPE295 */
					U4	xPE296					:1;				/* ECMPE296 */
					U4	xPE297					:1;				/* ECMPE297 */
					U4	xPE298					:1;				/* ECMPE298 */
					U4	xPE299					:1;				/* ECMPE299 */
					U4	xPE300					:1;				/* ECMPE300 */
					U4	xPE301					:1;				/* ECMPE301 */
					U4	xPE302					:1;				/* ECMPE302 */
					U4	xPE303					:1;				/* ECMPE303 */
					U4	xPE304					:1;				/* ECMPE304 */
					U4	xPE305					:1;				/* ECMPE305 */
					U4	xPE306					:1;				/* ECMPE306 */
					U4	xPE307					:1;				/* ECMPE307 */
					U4	xPE308					:1;				/* ECMPE308 */
					U4	xPE309					:1;				/* ECMPE309 */
					U4	xPE310					:1;				/* ECMPE310 */
					U4	xPE311					:1;				/* ECMPE311 */
					U4	xPE312					:1;				/* ECMPE312 */
					U4	xPE313					:1;				/* ECMPE313 */
					U4	xPE314					:1;				/* ECMPE314 */
					U4	xPE315					:1;				/* ECMPE315 */
					U4	xPE316					:1;				/* ECMPE316 */
					U4	xPE317					:1;				/* ECMPE317 */
					U4	xPE318					:1;				/* ECMPE318 */
					U4	xPE319					:1;				/* ECMPE319 */
				} stBit;
			} unECMPE9;										/* 0xFFD384DC */

			union												/* ECMPE10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xPE320					:1;				/* ECMPE320 */
					U4	xPE321					:1;				/* ECMPE321 */
					U4	xPE322					:1;				/* ECMPE322 */
					U4	xPE323					:1;				/* ECMPE323 */
					U4	xPE324					:1;				/* ECMPE324 */
					U4	xPE325					:1;				/* ECMPE325 */
					U4	xPE326					:1;				/* ECMPE326 */
					U4	xPE327					:1;				/* ECMPE327 */
					U4	xPE328					:1;				/* ECMPE328 */
					U4	xPE329					:1;				/* ECMPE329 */
					U4	xPE330					:1;				/* ECMPE330 */
					U4	xPE331					:1;				/* ECMPE331 */
					U4	xPE332					:1;				/* ECMPE332 */
					U4	xPE333					:1;				/* ECMPE333 */
					U4	xPE334					:1;				/* ECMPE334 */
					U4	xPE335					:1;				/* ECMPE335 */
					U4	xPE336					:1;				/* ECMPE336 */
					U4	xPE337					:1;				/* ECMPE337 */
					U4	xPE338					:1;				/* ECMPE338 */
					U4	xPE339					:1;				/* ECMPE339 */
					U4	xPE340					:1;				/* ECMPE340 */
					U4	xPE341					:1;				/* ECMPE341 */
					U4	xPE342					:1;				/* ECMPE342 */
					U4	xPE343					:1;				/* ECMPE343 */
					U4	xPE344					:1;				/* ECMPE344 */
					U4	xPE345					:1;				/* ECMPE345 */
					U4	xPE346					:1;				/* ECMPE346 */
					U4	xPE347					:1;				/* ECMPE347 */
					U4	xPE348					:1;				/* ECMPE348 */
					U4	xPE349					:1;				/* ECMPE349 */
					U4	xPE350					:1;				/* ECMPE350 */
					U4	xPE351					:1;				/* ECMPE351 */
				} stBit;
			} unECMPE10;										/* 0xFFD384E0 */
		} stECMPEn;
	} unECMPEn;

	U1	u1Dummy17[16];	/* 0xFFD384E4 - 0xFFD384F4 */

	union														/* ECMDTMCTL */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	xECMSTA					:1;						/* ECMSTA */
			U4	xECMSTP					:1;						/* ECMSTP */
			U4	b2Dummy1				:2;
			U4	xDTMSTACNTCLK			:1;						/* DTMSTACNTCLK */
			U4	b27Dummy2				:27;
		} stBit;
	} unECMDTMCTL;												/* 0xFFD384F4 */

	union														/* ECMDTMR */
	{
		U4	u4Data;												/* 32-bit Access  */
		struct													/* Bit Access	*/
		{
			U4	b24ECMDTMR				:24;					/* ECMDTMR */
			U4	b8Dummy1				:8;
		} stBit;
	} unECMDTMR;												/* 0xFFD384F8 */

	union														/* ECMDTMCMP */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	b24DTMCMP				:24;					/* ECMDTMCMP */
			U4	xCMPW					:1;						/* CMPW */
			U4	b7Dummy1				:7;
		} stBit;
	} unECMDTMCMP;												/* 0xFFD384FC */

	union
	{
		U4	u4Data[11];											/* 32-bit Access */

		struct
		{
			union												/* ECMDTMCFG0 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME000					:1;				/* ECMDTMCFG000 */
					U4	xECMDTME001					:1;				/* ECMDTMCFG001 */
					U4	xECMDTME002					:1;				/* ECMDTMCFG002 */
					U4	xECMDTME003					:1;				/* ECMDTMCFG003 */
					U4	xECMDTME004					:1;				/* ECMDTMCFG004 */
					U4	xECMDTME005					:1;				/* ECMDTMCFG005 */
					U4	xECMDTME006					:1;				/* ECMDTMCFG006 */
					U4	xECMDTME007					:1;				/* ECMDTMCFG007 */
					U4	xECMDTME008					:1;				/* ECMDTMCFG008 */
					U4	xECMDTME009					:1;				/* ECMDTMCFG009 */
					U4	xECMDTME010					:1;				/* ECMDTMCFG010 */
					U4	xECMDTME011					:1;				/* ECMDTMCFG011 */
					U4	xECMDTME012					:1;				/* ECMDTMCFG012 */
					U4	xECMDTME013					:1;				/* ECMDTMCFG013 */
					U4	xECMDTME014					:1;				/* ECMDTMCFG014 */
					U4	xECMDTME015					:1;				/* ECMDTMCFG015 */
					U4	xECMDTME016					:1;				/* ECMDTMCFG016 */
					U4	xECMDTME017					:1;				/* ECMDTMCFG017 */
					U4	xECMDTME018					:1;				/* ECMDTMCFG018 */
					U4	xECMDTME019					:1;				/* ECMDTMCFG019 */
					U4	xECMDTME020					:1;				/* ECMDTMCFG020 */
					U4	xECMDTME021					:1;				/* ECMDTMCFG021 */
					U4	xECMDTME022					:1;				/* ECMDTMCFG022 */
					U4	xECMDTME023					:1;				/* ECMDTMCFG023 */
					U4	xECMDTME024					:1;				/* ECMDTMCFG024 */
					U4	xECMDTME025					:1;				/* ECMDTMCFG025 */
					U4	xECMDTME026					:1;				/* ECMDTMCFG026 */
					U4	xECMDTME027					:1;				/* ECMDTMCFG027 */
					U4	xECMDTME028					:1;				/* ECMDTMCFG028 */
					U4	xECMDTME029					:1;				/* ECMDTMCFG029 */
					U4	xECMDTME030					:1;				/* ECMDTMCFG030 */
					U4	xECMDTME031					:1;				/* ECMDTMCFG031 */
				} stBit;
			} unECMDTMCFG0;										/* 0xFFD38500 */

			union												/* ECMDTMCFG1 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME032					:1;				/* ECMDTMCFG032 */
					U4	xECMDTME033					:1;				/* ECMDTMCFG033 */
					U4	xECMDTME034					:1;				/* ECMDTMCFG034 */
					U4	xECMDTME035					:1;				/* ECMDTMCFG035 */
					U4	xECMDTME036					:1;				/* ECMDTMCFG036 */
					U4	xECMDTME037					:1;				/* ECMDTMCFG037 */
					U4	xECMDTME038					:1;				/* ECMDTMCFG038 */
					U4	xECMDTME039					:1;				/* ECMDTMCFG039 */
					U4	xECMDTME040					:1;				/* ECMDTMCFG040 */
					U4	xECMDTME041					:1;				/* ECMDTMCFG041 */
					U4	xECMDTME042					:1;				/* ECMDTMCFG042 */
					U4	xECMDTME043					:1;				/* ECMDTMCFG043 */
					U4	xECMDTME044					:1;				/* ECMDTMCFG044 */
					U4	xECMDTME045					:1;				/* ECMDTMCFG045 */
					U4	xECMDTME046					:1;				/* ECMDTMCFG046 */
					U4	xECMDTME047					:1;				/* ECMDTMCFG047 */
					U4	xECMDTME048					:1;				/* ECMDTMCFG048 */
					U4	xECMDTME049					:1;				/* ECMDTMCFG049 */
					U4	xECMDTME050					:1;				/* ECMDTMCFG050 */
					U4	xECMDTME051					:1;				/* ECMDTMCFG051 */
					U4	xECMDTME052					:1;				/* ECMDTMCFG052 */
					U4	xECMDTME053					:1;				/* ECMDTMCFG053 */
					U4	xECMDTME054					:1;				/* ECMDTMCFG054 */
					U4	xECMDTME055					:1;				/* ECMDTMCFG055 */
					U4	xECMDTME056					:1;				/* ECMDTMCFG056 */
					U4	xECMDTME057					:1;				/* ECMDTMCFG057 */
					U4	xECMDTME058					:1;				/* ECMDTMCFG058 */
					U4	xECMDTME059					:1;				/* ECMDTMCFG059 */
					U4	xECMDTME060					:1;				/* ECMDTMCFG060 */
					U4	xECMDTME061					:1;				/* ECMDTMCFG061 */
					U4	xECMDTME062					:1;				/* ECMDTMCFG062 */
					U4	xECMDTME063					:1;				/* ECMDTMCFG063 */
				} stBit;
			} unECMDTMCFG1;										/* 0xFFD38504 */

			union												/* ECMDTMCFG2 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME064					:1;				/* ECMDTMCFG064 */
					U4	xECMDTME065					:1;				/* ECMDTMCFG065 */
					U4	xECMDTME066					:1;				/* ECMDTMCFG066 */
					U4	xECMDTME067					:1;				/* ECMDTMCFG067 */
					U4	xECMDTME068					:1;				/* ECMDTMCFG068 */
					U4	xECMDTME069					:1;				/* ECMDTMCFG069 */
					U4	xECMDTME070					:1;				/* ECMDTMCFG070 */
					U4	xECMDTME071					:1;				/* ECMDTMCFG071 */
					U4	xECMDTME072					:1;				/* ECMDTMCFG072 */
					U4	xECMDTME073					:1;				/* ECMDTMCFG073 */
					U4	xECMDTME074					:1;				/* ECMDTMCFG074 */
					U4	xECMDTME075					:1;				/* ECMDTMCFG075 */
					U4	xECMDTME076					:1;				/* ECMDTMCFG076 */
					U4	xECMDTME077					:1;				/* ECMDTMCFG077 */
					U4	xECMDTME078					:1;				/* ECMDTMCFG078 */
					U4	xECMDTME079					:1;				/* ECMDTMCFG079 */
					U4	xECMDTME080					:1;				/* ECMDTMCFG080 */
					U4	xECMDTME081					:1;				/* ECMDTMCFG081 */
					U4	xECMDTME082					:1;				/* ECMDTMCFG082 */
					U4	xECMDTME083					:1;				/* ECMDTMCFG083 */
					U4	xECMDTME084					:1;				/* ECMDTMCFG084 */
					U4	xECMDTME085					:1;				/* ECMDTMCFG085 */
					U4	xECMDTME086					:1;				/* ECMDTMCFG086 */
					U4	xECMDTME087					:1;				/* ECMDTMCFG087 */
					U4	xECMDTME088					:1;				/* ECMDTMCFG088 */
					U4	xECMDTME089					:1;				/* ECMDTMCFG089 */
					U4	xECMDTME090					:1;				/* ECMDTMCFG090 */
					U4	xECMDTME091					:1;				/* ECMDTMCFG091 */
					U4	xECMDTME092					:1;				/* ECMDTMCFG092 */
					U4	xECMDTME093					:1;				/* ECMDTMCFG093 */
					U4	xECMDTME094					:1;				/* ECMDTMCFG094 */
					U4	xECMDTME095					:1;				/* ECMDTMCFG095 */
				} stBit;
			} unECMDTMCFG2;										/* 0xFFD38508 */

			union												/* ECMDTMCFG3 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME096					:1;				/* ECMDTMCFG096 */
					U4	xECMDTME097					:1;				/* ECMDTMCFG097 */
					U4	xECMDTME098					:1;				/* ECMDTMCFG098 */
					U4	xECMDTME099					:1;				/* ECMDTMCFG099 */
					U4	xECMDTME100					:1;				/* ECMDTMCFG100 */
					U4	xECMDTME101					:1;				/* ECMDTMCFG101 */
					U4	xECMDTME102					:1;				/* ECMDTMCFG102 */
					U4	xECMDTME103					:1;				/* ECMDTMCFG103 */
					U4	xECMDTME104					:1;				/* ECMDTMCFG104 */
					U4	xECMDTME105					:1;				/* ECMDTMCFG105 */
					U4	xECMDTME106					:1;				/* ECMDTMCFG106 */
					U4	xECMDTME107					:1;				/* ECMDTMCFG107 */
					U4	xECMDTME108					:1;				/* ECMDTMCFG108 */
					U4	xECMDTME109					:1;				/* ECMDTMCFG109 */
					U4	xECMDTME110					:1;				/* ECMDTMCFG110 */
					U4	xECMDTME111					:1;				/* ECMDTMCFG111 */
					U4	xECMDTME112					:1;				/* ECMDTMCFG112 */
					U4	xECMDTME113					:1;				/* ECMDTMCFG113 */
					U4	xECMDTME114					:1;				/* ECMDTMCFG114 */
					U4	xECMDTME115					:1;				/* ECMDTMCFG115 */
					U4	xECMDTME116					:1;				/* ECMDTMCFG116 */
					U4	xECMDTME117					:1;				/* ECMDTMCFG117 */
					U4	xECMDTME118					:1;				/* ECMDTMCFG118 */
					U4	xECMDTME119					:1;				/* ECMDTMCFG119 */
					U4	xECMDTME120					:1;				/* ECMDTMCFG120 */
					U4	xECMDTME121					:1;				/* ECMDTMCFG121 */
					U4	xECMDTME122					:1;				/* ECMDTMCFG122 */
					U4	xECMDTME123					:1;				/* ECMDTMCFG123 */
					U4	xECMDTME124					:1;				/* ECMDTMCFG124 */
					U4	xECMDTME125					:1;				/* ECMDTMCFG125 */
					U4	xECMDTME126					:1;				/* ECMDTMCFG126 */
					U4	xECMDTME127					:1;				/* ECMDTMCFG127 */
				} stBit;
			} unECMDTMCFG3;										/* 0xFFD3850C */

			union												/* ECMDTMCFG4 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME128					:1;				/* ECMDTMCFG128 */
					U4	xECMDTME129					:1;				/* ECMDTMCFG129 */
					U4	xECMDTME130					:1;				/* ECMDTMCFG130 */
					U4	xECMDTME131					:1;				/* ECMDTMCFG131 */
					U4	xECMDTME132					:1;				/* ECMDTMCFG132 */
					U4	xECMDTME133					:1;				/* ECMDTMCFG133 */
					U4	xECMDTME134					:1;				/* ECMDTMCFG134 */
					U4	xECMDTME135					:1;				/* ECMDTMCFG135 */
					U4	xECMDTME136					:1;				/* ECMDTMCFG136 */
					U4	xECMDTME137					:1;				/* ECMDTMCFG137 */
					U4	xECMDTME138					:1;				/* ECMDTMCFG138 */
					U4	xECMDTME139					:1;				/* ECMDTMCFG139 */
					U4	xECMDTME140					:1;				/* ECMDTMCFG140 */
					U4	xECMDTME141					:1;				/* ECMDTMCFG141 */
					U4	xECMDTME142					:1;				/* ECMDTMCFG142 */
					U4	xECMDTME143					:1;				/* ECMDTMCFG143 */
					U4	xECMDTME144					:1;				/* ECMDTMCFG144 */
					U4	xECMDTME145					:1;				/* ECMDTMCFG145 */
					U4	xECMDTME146					:1;				/* ECMDTMCFG146 */
					U4	xECMDTME147					:1;				/* ECMDTMCFG147 */
					U4	xECMDTME148					:1;				/* ECMDTMCFG148 */
					U4	xECMDTME149					:1;				/* ECMDTMCFG149 */
					U4	xECMDTME150					:1;				/* ECMDTMCFG150 */
					U4	xECMDTME151					:1;				/* ECMDTMCFG151 */
					U4	xECMDTME152					:1;				/* ECMDTMCFG152 */
					U4	xECMDTME153					:1;				/* ECMDTMCFG153 */
					U4	xECMDTME154					:1;				/* ECMDTMCFG154 */
					U4	xECMDTME155					:1;				/* ECMDTMCFG155 */
					U4	xECMDTME156					:1;				/* ECMDTMCFG156 */
					U4	xECMDTME157					:1;				/* ECMDTMCFG157 */
					U4	xECMDTME158					:1;				/* ECMDTMCFG158 */
					U4	xECMDTME159					:1;				/* ECMDTMCFG159 */
				} stBit;
			} unECMDTMCFG4;										/* 0xFFD38510 */

			union												/* ECMDTMCFG5 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME160					:1;				/* ECMDTMCFG160 */
					U4	xECMDTME161					:1;				/* ECMDTMCFG161 */
					U4	xECMDTME162					:1;				/* ECMDTMCFG162 */
					U4	xECMDTME163					:1;				/* ECMDTMCFG163 */
					U4	xECMDTME164					:1;				/* ECMDTMCFG164 */
					U4	xECMDTME165					:1;				/* ECMDTMCFG165 */
					U4	xECMDTME166					:1;				/* ECMDTMCFG166 */
					U4	xECMDTME167					:1;				/* ECMDTMCFG167 */
					U4	xECMDTME168					:1;				/* ECMDTMCFG168 */
					U4	xECMDTME169					:1;				/* ECMDTMCFG169 */
					U4	xECMDTME170					:1;				/* ECMDTMCFG170 */
					U4	xECMDTME171					:1;				/* ECMDTMCFG171 */
					U4	xECMDTME172					:1;				/* ECMDTMCFG172 */
					U4	xECMDTME173					:1;				/* ECMDTMCFG173 */
					U4	xECMDTME174					:1;				/* ECMDTMCFG174 */
					U4	xECMDTME175					:1;				/* ECMDTMCFG175 */
					U4	xECMDTME176					:1;				/* ECMDTMCFG176 */
					U4	xECMDTME177					:1;				/* ECMDTMCFG177 */
					U4	xECMDTME178					:1;				/* ECMDTMCFG178 */
					U4	xECMDTME179					:1;				/* ECMDTMCFG179 */
					U4	xECMDTME180					:1;				/* ECMDTMCFG180 */
					U4	xECMDTME181					:1;				/* ECMDTMCFG181 */
					U4	xECMDTME182					:1;				/* ECMDTMCFG182 */
					U4	xECMDTME183					:1;				/* ECMDTMCFG183 */
					U4	xECMDTME184					:1;				/* ECMDTMCFG184 */
					U4	xECMDTME185					:1;				/* ECMDTMCFG185 */
					U4	xECMDTME186					:1;				/* ECMDTMCFG186 */
					U4	xECMDTME187					:1;				/* ECMDTMCFG187 */
					U4	xECMDTME188					:1;				/* ECMDTMCFG188 */
					U4	xECMDTME189					:1;				/* ECMDTMCFG189 */
					U4	xECMDTME190					:1;				/* ECMDTMCFG190 */
					U4	xECMDTME191					:1;				/* ECMDTMCFG191 */
				} stBit;
			} unECMDTMCFG5;										/* 0xFFD38514 */

			union												/* ECMDTMCFG6 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME192					:1;				/* ECMDTMCFG192 */
					U4	xECMDTME193					:1;				/* ECMDTMCFG193 */
					U4	xECMDTME194					:1;				/* ECMDTMCFG194 */
					U4	xECMDTME195					:1;				/* ECMDTMCFG195 */
					U4	xECMDTME196					:1;				/* ECMDTMCFG196 */
					U4	xECMDTME197					:1;				/* ECMDTMCFG197 */
					U4	xECMDTME198					:1;				/* ECMDTMCFG198 */
					U4	xECMDTME199					:1;				/* ECMDTMCFG199 */
					U4	xECMDTME200					:1;				/* ECMDTMCFG200 */
					U4	xECMDTME201					:1;				/* ECMDTMCFG201 */
					U4	xECMDTME202					:1;				/* ECMDTMCFG202 */
					U4	xECMDTME203					:1;				/* ECMDTMCFG203 */
					U4	xECMDTME204					:1;				/* ECMDTMCFG204 */
					U4	xECMDTME205					:1;				/* ECMDTMCFG205 */
					U4	xECMDTME206					:1;				/* ECMDTMCFG206 */
					U4	xECMDTME207					:1;				/* ECMDTMCFG207 */
					U4	xECMDTME208					:1;				/* ECMDTMCFG208 */
					U4	xECMDTME209					:1;				/* ECMDTMCFG209 */
					U4	xECMDTME210					:1;				/* ECMDTMCFG210 */
					U4	xECMDTME211					:1;				/* ECMDTMCFG211 */
					U4	xECMDTME212					:1;				/* ECMDTMCFG212 */
					U4	xECMDTME213					:1;				/* ECMDTMCFG213 */
					U4	xECMDTME214					:1;				/* ECMDTMCFG214 */
					U4	xECMDTME215					:1;				/* ECMDTMCFG215 */
					U4	xECMDTME216					:1;				/* ECMDTMCFG216 */
					U4	xECMDTME217					:1;				/* ECMDTMCFG217 */
					U4	xECMDTME218					:1;				/* ECMDTMCFG218 */
					U4	xECMDTME219					:1;				/* ECMDTMCFG219 */
					U4	xECMDTME220					:1;				/* ECMDTMCFG220 */
					U4	xECMDTME221					:1;				/* ECMDTMCFG221 */
					U4	xECMDTME222					:1;				/* ECMDTMCFG222 */
					U4	xECMDTME223					:1;				/* ECMDTMCFG223 */
				} stBit;
			} unECMDTMCFG6;										/* 0xFFD38518 */

			union												/* ECMDTMCFG7 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME224					:1;				/* ECMDTMCFG224 */
					U4	xECMDTME225					:1;				/* ECMDTMCFG225 */
					U4	xECMDTME226					:1;				/* ECMDTMCFG226 */
					U4	xECMDTME227					:1;				/* ECMDTMCFG227 */
					U4	xECMDTME228					:1;				/* ECMDTMCFG228 */
					U4	xECMDTME229					:1;				/* ECMDTMCFG229 */
					U4	xECMDTME230					:1;				/* ECMDTMCFG230 */
					U4	xECMDTME231					:1;				/* ECMDTMCFG231 */
					U4	xECMDTME232					:1;				/* ECMDTMCFG232 */
					U4	xECMDTME233					:1;				/* ECMDTMCFG233 */
					U4	xECMDTME234					:1;				/* ECMDTMCFG234 */
					U4	xECMDTME235					:1;				/* ECMDTMCFG235 */
					U4	xECMDTME236					:1;				/* ECMDTMCFG236 */
					U4	xECMDTME237					:1;				/* ECMDTMCFG237 */
					U4	xECMDTME238					:1;				/* ECMDTMCFG238 */
					U4	xECMDTME239					:1;				/* ECMDTMCFG239 */
					U4	xECMDTME240					:1;				/* ECMDTMCFG240 */
					U4	xECMDTME241					:1;				/* ECMDTMCFG241 */
					U4	xECMDTME242					:1;				/* ECMDTMCFG242 */
					U4	xECMDTME243					:1;				/* ECMDTMCFG243 */
					U4	xECMDTME244					:1;				/* ECMDTMCFG244 */
					U4	xECMDTME245					:1;				/* ECMDTMCFG245 */
					U4	xECMDTME246					:1;				/* ECMDTMCFG246 */
					U4	xECMDTME247					:1;				/* ECMDTMCFG247 */
					U4	xECMDTME248					:1;				/* ECMDTMCFG248 */
					U4	xECMDTME249					:1;				/* ECMDTMCFG249 */
					U4	xECMDTME250					:1;				/* ECMDTMCFG250 */
					U4	xECMDTME251					:1;				/* ECMDTMCFG251 */
					U4	xECMDTME252					:1;				/* ECMDTMCFG252 */
					U4	xECMDTME253					:1;				/* ECMDTMCFG253 */
					U4	xECMDTME254					:1;				/* ECMDTMCFG254 */
					U4	xECMDTME255					:1;				/* ECMDTMCFG255 */
				} stBit;
			} unECMDTMCFG7;										/* 0xFFD3851C */

			union												/* ECMDTMCFG8 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME256					:1;				/* ECMDTMCFG256 */
					U4	xECMDTME257					:1;				/* ECMDTMCFG257 */
					U4	xECMDTME258					:1;				/* ECMDTMCFG258 */
					U4	xECMDTME259					:1;				/* ECMDTMCFG259 */
					U4	xECMDTME260					:1;				/* ECMDTMCFG260 */
					U4	xECMDTME261					:1;				/* ECMDTMCFG261 */
					U4	xECMDTME262					:1;				/* ECMDTMCFG262 */
					U4	xECMDTME263					:1;				/* ECMDTMCFG263 */
					U4	xECMDTME264					:1;				/* ECMDTMCFG264 */
					U4	xECMDTME265					:1;				/* ECMDTMCFG265 */
					U4	xECMDTME266					:1;				/* ECMDTMCFG266 */
					U4	xECMDTME267					:1;				/* ECMDTMCFG267 */
					U4	xECMDTME268					:1;				/* ECMDTMCFG268 */
					U4	xECMDTME269					:1;				/* ECMDTMCFG269 */
					U4	xECMDTME270					:1;				/* ECMDTMCFG270 */
					U4	xECMDTME271					:1;				/* ECMDTMCFG271 */
					U4	xECMDTME272					:1;				/* ECMDTMCFG272 */
					U4	xECMDTME273					:1;				/* ECMDTMCFG273 */
					U4	xECMDTME274					:1;				/* ECMDTMCFG274 */
					U4	xECMDTME275					:1;				/* ECMDTMCFG275 */
					U4	xECMDTME276					:1;				/* ECMDTMCFG276 */
					U4	xECMDTME277					:1;				/* ECMDTMCFG277 */
					U4	xECMDTME278					:1;				/* ECMDTMCFG278 */
					U4	xECMDTME279					:1;				/* ECMDTMCFG279 */
					U4	xECMDTME280					:1;				/* ECMDTMCFG280 */
					U4	xECMDTME281					:1;				/* ECMDTMCFG281 */
					U4	xECMDTME282					:1;				/* ECMDTMCFG282 */
					U4	xECMDTME283					:1;				/* ECMDTMCFG283 */
					U4	xECMDTME284					:1;				/* ECMDTMCFG284 */
					U4	xECMDTME285					:1;				/* ECMDTMCFG285 */
					U4	xECMDTME286					:1;				/* ECMDTMCFG286 */
					U4	xECMDTME287					:1;				/* ECMDTMCFG287 */
				} stBit;
			} unECMDTMCFG8;										/* 0xFFD38520 */

			union												/* ECMDTMCFG9 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME288					:1;				/* ECMDTMCFG288 */
					U4	xECMDTME289					:1;				/* ECMDTMCFG289 */
					U4	xECMDTME290					:1;				/* ECMDTMCFG290 */
					U4	xECMDTME291					:1;				/* ECMDTMCFG291 */
					U4	xECMDTME292					:1;				/* ECMDTMCFG292 */
					U4	xECMDTME293					:1;				/* ECMDTMCFG293 */
					U4	xECMDTME294					:1;				/* ECMDTMCFG294 */
					U4	xECMDTME295					:1;				/* ECMDTMCFG295 */
					U4	xECMDTME296					:1;				/* ECMDTMCFG296 */
					U4	xECMDTME297					:1;				/* ECMDTMCFG297 */
					U4	xECMDTME298					:1;				/* ECMDTMCFG298 */
					U4	xECMDTME299					:1;				/* ECMDTMCFG299 */
					U4	xECMDTME300					:1;				/* ECMDTMCFG300 */
					U4	xECMDTME301					:1;				/* ECMDTMCFG301 */
					U4	xECMDTME302					:1;				/* ECMDTMCFG302 */
					U4	xECMDTME303					:1;				/* ECMDTMCFG303 */
					U4	xECMDTME304					:1;				/* ECMDTMCFG304 */
					U4	xECMDTME305					:1;				/* ECMDTMCFG305 */
					U4	xECMDTME306					:1;				/* ECMDTMCFG306 */
					U4	xECMDTME307					:1;				/* ECMDTMCFG307 */
					U4	xECMDTME308					:1;				/* ECMDTMCFG308 */
					U4	xECMDTME309					:1;				/* ECMDTMCFG309 */
					U4	xECMDTME310					:1;				/* ECMDTMCFG310 */
					U4	xECMDTME311					:1;				/* ECMDTMCFG311 */
					U4	xECMDTME312					:1;				/* ECMDTMCFG312 */
					U4	xECMDTME313					:1;				/* ECMDTMCFG313 */
					U4	xECMDTME314					:1;				/* ECMDTMCFG314 */
					U4	xECMDTME315					:1;				/* ECMDTMCFG315 */
					U4	xECMDTME316					:1;				/* ECMDTMCFG316 */
					U4	xECMDTME317					:1;				/* ECMDTMCFG317 */
					U4	xECMDTME318					:1;				/* ECMDTMCFG318 */
					U4	xECMDTME319					:1;				/* ECMDTMCFG319 */
				} stBit;
			} unECMDTMCFG9;										/* 0xFFD38524 */

			union												/* ECMDTMCFG10 */
			{
				U4	u4Data;										/* 32-bit Access */
				struct											/* Bit Access	*/
				{
					U4	xECMDTME320					:1;				/* ECMDTMCFG320 */
					U4	xECMDTME321					:1;				/* ECMDTMCFG321 */
					U4	xECMDTME322					:1;				/* ECMDTMCFG322 */
					U4	xECMDTME323					:1;				/* ECMDTMCFG323 */
					U4	xECMDTME324					:1;				/* ECMDTMCFG324 */
					U4	xECMDTME325					:1;				/* ECMDTMCFG325 */
					U4	xECMDTME326					:1;				/* ECMDTMCFG326 */
					U4	xECMDTME327					:1;				/* ECMDTMCFG327 */
					U4	xECMDTME328					:1;				/* ECMDTMCFG328 */
					U4	xECMDTME329					:1;				/* ECMDTMCFG329 */
					U4	xECMDTME330					:1;				/* ECMDTMCFG330 */
					U4	xECMDTME331					:1;				/* ECMDTMCFG331 */
					U4	xECMDTME332					:1;				/* ECMDTMCFG332 */
					U4	xECMDTME333					:1;				/* ECMDTMCFG333 */
					U4	xECMDTME334					:1;				/* ECMDTMCFG334 */
					U4	xECMDTME335					:1;				/* ECMDTMCFG335 */
					U4	xECMDTME336					:1;				/* ECMDTMCFG336 */
					U4	xECMDTME337					:1;				/* ECMDTMCFG337 */
					U4	xECMDTME338					:1;				/* ECMDTMCFG338 */
					U4	xECMDTME339					:1;				/* ECMDTMCFG339 */
					U4	xECMDTME340					:1;				/* ECMDTMCFG340 */
					U4	xECMDTME341					:1;				/* ECMDTMCFG341 */
					U4	xECMDTME342					:1;				/* ECMDTMCFG342 */
					U4	xECMDTME343					:1;				/* ECMDTMCFG343 */
					U4	xECMDTME344					:1;				/* ECMDTMCFG344 */
					U4	xECMDTME345					:1;				/* ECMDTMCFG345 */
					U4	xECMDTME346					:1;				/* ECMDTMCFG346 */
					U4	xECMDTME347					:1;				/* ECMDTMCFG347 */
					U4	xECMDTME348					:1;				/* ECMDTMCFG348 */
					U4	xECMDTME349					:1;				/* ECMDTMCFG349 */
					U4	xECMDTME350					:1;				/* ECMDTMCFG350 */
					U4	xECMDTME351					:1;				/* ECMDTMCFG351 */
				} stBit;
			} unECMDTMCFG10;										/* 0xFFD38528 */
		} stECMDTMCFGn;
	} unECMDTMCFGn;

	U1	u1Dummy18[496];	/* 0xFFD3852C - 0xFFD3871C */

	union														/* ECMEOCCFG */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	b24EOUTCLRT				:24;					/* ECMEOUTCLRT */
			U4	xCMPW					:1;						/* CMPW */
			U4	b6Dummy1				:6;
			U4	xEOCIEN					:1;						/* EOCIEN */
		} stBit;
	} unECMEOCCFG;												/* 0xFFD3871C */

	union														/* ECMETCCFG0 */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	b24ETRGCLRT				:24;					/* ECMETRGCLRT */
			U4	xCMPW					:1;						/* CMPW */
			U4	b6Dummy1				:6;
			U4	xETCIEN					:1;						/* ETCIEN */
		} stBit;
	} unECMETCCFG0;												/* 0xFFD38720 */

	union														/* ECMETCCFG1 */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	b24ETRGCLRT				:24;					/* ECMETRGCLRT */
			U4	xCMPW					:1;						/* CMPW */
			U4	b6Dummy1				:6;
			U4	xETCIEN					:1;						/* ETCIEN */
		} stBit;
	} unECMETCCFG1;												/* 0xFFD38724 */

	union														/* ECMETCCFG2 */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	b24ETRGCLRT				:24;					/* ECMETRGCLRT */
			U4	xCMPW					:1;						/* CMPW */
			U4	b6Dummy1				:6;
			U4	xETCIEN					:1;						/* ETCIEN */
		} stBit;
	} unECMETCCFG2;												/* 0xFFD38728 */

	union														/* ECMETCCFG3 */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	b24ETRGCLRT				:24;					/* ECMETRGCLRT */
			U4	xCMPW					:1;						/* CMPW */
			U4	b6Dummy1				:6;
			U4	xETCIEN					:1;						/* ETCIEN */
		} stBit;
	} unECMETCCFG3;												/* 0xFFD3872C */

	U1	u1Dummy19[16];	/* 0xFFD38730 - 0xFFD38740 */

	union														/* ECMPEM */
	{
		U4	u4Data;												/* 32-bit Access */
		struct													/* Bit Access	*/
		{
			U4	xMSKC					:1;						/* MSKC */
			U4	xMSKM					:1;						/* MSKM */
			U4	b30Dummy1				:30;
		} stBit;
	} unECMPEM;													/* 0xFFD38740 */

}	Reg_Ecm_EcmType;


/*----------------------------------------------------------------------------------------------*/
/*	register BIT definition																		*/
/*----------------------------------------------------------------------------------------------*/
/* ECMmESET,m=M/C */
#define		ECM_ECMESET_EST			(BIT0)
	#define		ECM_ECMESET_EST_SET			(1)

/* ECMmESET0,m=M/C */
#define		ECM_ECMESET0_EST			(BIT0)
	#define		ECM_ECMESET_EST_SET			(1)

/* ECMmESET1,m=M/C */
#define		ECM_ECMESET1_EST			(BIT0)
	#define		ECM_ECMESET_EST_SET			(1)

/* ECMmESET2,m=M/C */
#define		ECM_ECMESET2_EST			(BIT0)
	#define		ECM_ECMESET_EST_SET			(1)

/* ECMmESET3,m=M/C */
#define		ECM_ECMESET3_EST			(BIT0)
	#define		ECM_ECMESET_EST_SET			(1)

/* ECMmECLR,m=M/C */
#define		ECM_ECMECLR_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmECLR0,m=M/C */
#define		ECM_ECMECLR0_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmECLR1,m=M/C */
#define		ECM_ECMECLR1_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmECLR2,m=M/C */
#define		ECM_ECMECLR2_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmECLR3,m=M/C */
#define		ECM_ECMECLR3_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmECLR4,m=M/C */
#define		ECM_ECMECLR4_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmECLR5,m=M/C */
#define		ECM_ECMECLR5_ECT			(BIT0)
	#define		ECM_ECMECLR_ECT_CLR			(1)

/* ECMmESSTR0,m=M/C */
#define		ECM_ECMESSTR0_SSE031		(BIT31)
	#define		ECM_ECMESSTR0_SSE031_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE031_ERROR		(1)
#define		ECM_ECMESSTR0_SSE030		(BIT30)
	#define		ECM_ECMESSTR0_SSE030_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE030_ERROR		(1)
#define		ECM_ECMESSTR0_SSE029		(BIT29)
	#define		ECM_ECMESSTR0_SSE029_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE029_ERROR		(1)
#define		ECM_ECMESSTR0_SSE028		(BIT28)
	#define		ECM_ECMESSTR0_SSE028_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE028_ERROR		(1)
#define		ECM_ECMESSTR0_SSE027		(BIT27)
	#define		ECM_ECMESSTR0_SSE027_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE027_ERROR		(1)
#define		ECM_ECMESSTR0_SSE026		(BIT26)
	#define		ECM_ECMESSTR0_SSE026_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE026_ERROR		(1)
#define		ECM_ECMESSTR0_SSE025		(BIT25)
	#define		ECM_ECMESSTR0_SSE025_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE025_ERROR		(1)
#define		ECM_ECMESSTR0_SSE024		(BIT24)
	#define		ECM_ECMESSTR0_SSE024_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE024_ERROR		(1)
#define		ECM_ECMESSTR0_SSE023		(BIT23)
	#define		ECM_ECMESSTR0_SSE023_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE023_ERROR		(1)
#define		ECM_ECMESSTR0_SSE022		(BIT22)
	#define		ECM_ECMESSTR0_SSE022_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE022_ERROR		(1)
#define		ECM_ECMESSTR0_SSE021		(BIT21)
	#define		ECM_ECMESSTR0_SSE021_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE021_ERROR		(1)
#define		ECM_ECMESSTR0_SSE020		(BIT20)
	#define		ECM_ECMESSTR0_SSE020_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE020_ERROR		(1)
#define		ECM_ECMESSTR0_SSE019		(BIT19)
	#define		ECM_ECMESSTR0_SSE019_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE019_ERROR		(1)
#define		ECM_ECMESSTR0_SSE018		(BIT18)
	#define		ECM_ECMESSTR0_SSE018_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE018_ERROR		(1)
#define		ECM_ECMESSTR0_SSE017		(BIT17)
	#define		ECM_ECMESSTR0_SSE017_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE017_ERROR		(1)
#define		ECM_ECMESSTR0_SSE016		(BIT16)
	#define		ECM_ECMESSTR0_SSE016_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE016_ERROR		(1)
#define		ECM_ECMESSTR0_SSE015		(BIT15)
	#define		ECM_ECMESSTR0_SSE015_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE015_ERROR		(1)
#define		ECM_ECMESSTR0_SSE014		(BIT14)
	#define		ECM_ECMESSTR0_SSE014_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE014_ERROR		(1)
#define		ECM_ECMESSTR0_SSE013		(BIT13)
	#define		ECM_ECMESSTR0_SSE013_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE013_ERROR		(1)
#define		ECM_ECMESSTR0_SSE012		(BIT12)
	#define		ECM_ECMESSTR0_SSE012_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE012_ERROR		(1)
#define		ECM_ECMESSTR0_SSE011		(BIT11)
	#define		ECM_ECMESSTR0_SSE011_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE011_ERROR		(1)
#define		ECM_ECMESSTR0_SSE010		(BIT10)
	#define		ECM_ECMESSTR0_SSE010_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE010_ERROR		(1)
#define		ECM_ECMESSTR0_SSE009		(BIT9)
	#define		ECM_ECMESSTR0_SSE009_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE009_ERROR		(1)
#define		ECM_ECMESSTR0_SSE008		(BIT8)
	#define		ECM_ECMESSTR0_SSE008_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE008_ERROR		(1)
#define		ECM_ECMESSTR0_SSE007		(BIT7)
	#define		ECM_ECMESSTR0_SSE007_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE007_ERROR		(1)
#define		ECM_ECMESSTR0_SSE06		(BIT6)
	#define		ECM_ECMESSTR0_SSE006_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE006_ERROR		(1)
#define		ECM_ECMESSTR0_SSE005		(BIT5)
	#define		ECM_ECMESSTR0_SSE005_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE005_ERROR		(1)
#define		ECM_ECMESSTR0_SSE004		(BIT4)
	#define		ECM_ECMESSTR0_SSE004_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE004_ERROR		(1)
#define		ECM_ECMESSTR0_SSE003		(BIT3)
	#define		ECM_ECMESSTR0_SSE003_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE003_ERROR		(1)
#define		ECM_ECMESSTR0_SSE02		(BIT2)
	#define		ECM_ECMESSTR0_SSE002_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE002_ERROR		(1)
#define		ECM_ECMESSTR0_SSE01		(BIT1)
	#define		ECM_ECMESSTR0_SSE001_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE001_ERROR		(1)
#define		ECM_ECMESSTR0_SSE00		(BIT0)
	#define		ECM_ECMESSTR0_SSE000_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE000_ERROR		(1)
/* ECMmESSTR1,m=M/C */
#define		ECM_ECMESSTR0_SSE063		(BIT31)
	#define		ECM_ECMESSTR0_SSE063_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE063_ERROR		(1)
#define		ECM_ECMESSTR0_SSE062		(BIT30)
	#define		ECM_ECMESSTR0_SSE062_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE062_ERROR		(1)
#define		ECM_ECMESSTR0_SSE061		(BIT29)
	#define		ECM_ECMESSTR0_SSE061_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE061_ERROR		(1)
#define		ECM_ECMESSTR0_SSE060		(BIT28)
	#define		ECM_ECMESSTR0_SSE060_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE060_ERROR		(1)
#define		ECM_ECMESSTR0_SSE059		(BIT27)
	#define		ECM_ECMESSTR0_SSE059_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE059_ERROR		(1)
#define		ECM_ECMESSTR0_SSE058		(BIT26)
	#define		ECM_ECMESSTR0_SSE058_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE058_ERROR		(1)
#define		ECM_ECMESSTR0_SSE057		(BIT25)
	#define		ECM_ECMESSTR0_SSE057_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE057_ERROR		(1)
#define		ECM_ECMESSTR0_SSE056		(BIT24)
	#define		ECM_ECMESSTR0_SSE056_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE056_ERROR		(1)
#define		ECM_ECMESSTR0_SSE055		(BIT23)
	#define		ECM_ECMESSTR0_SSE055_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE055_ERROR		(1)
#define		ECM_ECMESSTR0_SSE054		(BIT22)
	#define		ECM_ECMESSTR0_SSE054_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE054_ERROR		(1)
#define		ECM_ECMESSTR0_SSE053		(BIT21)
	#define		ECM_ECMESSTR0_SSE053_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE053_ERROR		(1)
#define		ECM_ECMESSTR0_SSE052		(BIT20)
	#define		ECM_ECMESSTR0_SSE052_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE052_ERROR		(1)
#define		ECM_ECMESSTR0_SSE051		(BIT19)
	#define		ECM_ECMESSTR0_SSE051_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE051_ERROR		(1)
#define		ECM_ECMESSTR0_SSE050		(BIT18)
	#define		ECM_ECMESSTR0_SSE050_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE050_ERROR		(1)
#define		ECM_ECMESSTR0_SSE049		(BIT17)
	#define		ECM_ECMESSTR0_SSE049_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE049_ERROR		(1)
#define		ECM_ECMESSTR0_SSE048		(BIT16)
	#define		ECM_ECMESSTR0_SSE048_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE048_ERROR		(1)
#define		ECM_ECMESSTR0_SSE047		(BIT15)
	#define		ECM_ECMESSTR0_SSE047_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE047_ERROR		(1)
#define		ECM_ECMESSTR0_SSE046		(BIT14)
	#define		ECM_ECMESSTR0_SSE046_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE046_ERROR		(1)
#define		ECM_ECMESSTR0_SSE045		(BIT13)
	#define		ECM_ECMESSTR0_SSE045_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE045_ERROR		(1)
#define		ECM_ECMESSTR0_SSE044		(BIT12)
	#define		ECM_ECMESSTR0_SSE044_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE044_ERROR		(1)
#define		ECM_ECMESSTR0_SSE043		(BIT11)
	#define		ECM_ECMESSTR0_SSE043_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE043_ERROR		(1)
#define		ECM_ECMESSTR0_SSE042		(BIT10)
	#define		ECM_ECMESSTR0_SSE042_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE042_ERROR		(1)
#define		ECM_ECMESSTR0_SSE041		(BIT9)
	#define		ECM_ECMESSTR0_SSE041_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE041_ERROR		(1)
#define		ECM_ECMESSTR0_SSE040		(BIT8)
	#define		ECM_ECMESSTR0_SSE040_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE040_ERROR		(1)
#define		ECM_ECMESSTR0_SSE039		(BIT7)
	#define		ECM_ECMESSTR0_SSE039_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE039_ERROR		(1)
#define		ECM_ECMESSTR0_SSE038		(BIT6)
	#define		ECM_ECMESSTR0_SSE038_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE038_ERROR		(1)
#define		ECM_ECMESSTR0_SSE037		(BIT5)
	#define		ECM_ECMESSTR0_SSE037_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE037_ERROR		(1)
#define		ECM_ECMESSTR0_SSE036		(BIT4)
	#define		ECM_ECMESSTR0_SSE036_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE036_ERROR		(1)
#define		ECM_ECMESSTR0_SSE035		(BIT3)
	#define		ECM_ECMESSTR0_SSE035_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE035_ERROR		(1)
#define		ECM_ECMESSTR0_SSE034		(BIT2)
	#define		ECM_ECMESSTR0_SSE034_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE034_ERROR		(1)
#define		ECM_ECMESSTR0_SSE033		(BIT1)
	#define		ECM_ECMESSTR0_SSE033_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE033_ERROR		(1)
#define		ECM_ECMESSTR0_SSE032		(BIT0)
	#define		ECM_ECMESSTR0_SSE032_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE032_ERROR		(1)

/* ECMmESSTR2,m=M/C */
#define		ECM_ECMESSTR0_SSE095		(BIT31)
	#define		ECM_ECMESSTR0_SSE095_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE095_ERROR		(1)
#define		ECM_ECMESSTR0_SSE094		(BIT30)
	#define		ECM_ECMESSTR0_SSE094_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE094_ERROR		(1)
#define		ECM_ECMESSTR0_SSE093		(BIT29)
	#define		ECM_ECMESSTR0_SSE093_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE093_ERROR		(1)
#define		ECM_ECMESSTR0_SSE092		(BIT28)
	#define		ECM_ECMESSTR0_SSE092_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE092_ERROR		(1)
#define		ECM_ECMESSTR0_SSE091		(BIT27)
	#define		ECM_ECMESSTR0_SSE091_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE091_ERROR		(1)
#define		ECM_ECMESSTR0_SSE090		(BIT26)
	#define		ECM_ECMESSTR0_SSE090_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE090_ERROR		(1)
#define		ECM_ECMESSTR0_SSE089		(BIT25)
	#define		ECM_ECMESSTR0_SSE089_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE089_ERROR		(1)
#define		ECM_ECMESSTR0_SSE088		(BIT24)
	#define		ECM_ECMESSTR0_SSE088_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE088_ERROR		(1)
#define		ECM_ECMESSTR0_SSE087		(BIT23)
	#define		ECM_ECMESSTR0_SSE087_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE087_ERROR		(1)
#define		ECM_ECMESSTR0_SSE086		(BIT22)
	#define		ECM_ECMESSTR0_SSE086_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE086_ERROR		(1)
#define		ECM_ECMESSTR0_SSE085		(BIT21)
	#define		ECM_ECMESSTR0_SSE085_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE085_ERROR		(1)
#define		ECM_ECMESSTR0_SSE084		(BIT20)
	#define		ECM_ECMESSTR0_SSE084_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE084_ERROR		(1)
#define		ECM_ECMESSTR0_SSE083		(BIT19)
	#define		ECM_ECMESSTR0_SSE083_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE083_ERROR		(1)
#define		ECM_ECMESSTR0_SSE082		(BIT18)
	#define		ECM_ECMESSTR0_SSE082_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE082_ERROR		(1)
#define		ECM_ECMESSTR0_SSE081		(BIT17)
	#define		ECM_ECMESSTR0_SSE081_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE081_ERROR		(1)
#define		ECM_ECMESSTR0_SSE080		(BIT16)
	#define		ECM_ECMESSTR0_SSE080_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE080_ERROR		(1)
#define		ECM_ECMESSTR0_SSE079		(BIT15)
	#define		ECM_ECMESSTR0_SSE079_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE079_ERROR		(1)
#define		ECM_ECMESSTR0_SSE078		(BIT14)
	#define		ECM_ECMESSTR0_SSE078_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE078_ERROR		(1)
#define		ECM_ECMESSTR0_SSE077		(BIT13)
	#define		ECM_ECMESSTR0_SSE077_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE077_ERROR		(1)
#define		ECM_ECMESSTR0_SSE076		(BIT12)
	#define		ECM_ECMESSTR0_SSE076_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE076_ERROR		(1)
#define		ECM_ECMESSTR0_SSE075		(BIT11)
	#define		ECM_ECMESSTR0_SSE075_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE075_ERROR		(1)
#define		ECM_ECMESSTR0_SSE074		(BIT10)
	#define		ECM_ECMESSTR0_SSE074_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE074_ERROR		(1)
#define		ECM_ECMESSTR0_SSE073		(BIT9)
	#define		ECM_ECMESSTR0_SSE073_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE073_ERROR		(1)
#define		ECM_ECMESSTR0_SSE072		(BIT8)
	#define		ECM_ECMESSTR0_SSE072_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE072_ERROR		(1)
#define		ECM_ECMESSTR0_SSE071		(BIT7)
	#define		ECM_ECMESSTR0_SSE071_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE071_ERROR		(1)
#define		ECM_ECMESSTR0_SSE070		(BIT6)
	#define		ECM_ECMESSTR0_SSE070_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE070_ERROR		(1)
#define		ECM_ECMESSTR0_SSE069		(BIT5)
	#define		ECM_ECMESSTR0_SSE069_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE069_ERROR		(1)
#define		ECM_ECMESSTR0_SSE068		(BIT4)
	#define		ECM_ECMESSTR0_SSE068_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE068_ERROR		(1)
#define		ECM_ECMESSTR0_SSE067		(BIT3)
	#define		ECM_ECMESSTR0_SSE067_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE067_ERROR		(1)
#define		ECM_ECMESSTR0_SSE066		(BIT2)
	#define		ECM_ECMESSTR0_SSE066_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE066_ERROR		(1)
#define		ECM_ECMESSTR0_SSE065		(BIT1)
	#define		ECM_ECMESSTR0_SSE065_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE065_ERROR		(1)
#define		ECM_ECMESSTR0_SSE064		(BIT0)
	#define		ECM_ECMESSTR0_SSE064_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE064_ERROR		(1)

/* ECMmESSTR3,m=M/C */
#define		ECM_ECMESSTR0_SSE127		(BIT31)
	#define		ECM_ECMESSTR0_SSE127_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE127_ERROR		(1)
#define		ECM_ECMESSTR0_SSE126		(BIT30)
	#define		ECM_ECMESSTR0_SSE126_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE126_ERROR		(1)
#define		ECM_ECMESSTR0_SSE125		(BIT29)
	#define		ECM_ECMESSTR0_SSE125_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE125_ERROR		(1)
#define		ECM_ECMESSTR0_SSE124		(BIT28)
	#define		ECM_ECMESSTR0_SSE124_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE124_ERROR		(1)
#define		ECM_ECMESSTR0_SSE123		(BIT27)
	#define		ECM_ECMESSTR0_SSE123_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE123_ERROR		(1)
#define		ECM_ECMESSTR0_SSE122		(BIT26)
	#define		ECM_ECMESSTR0_SSE122_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE122_ERROR		(1)
#define		ECM_ECMESSTR0_SSE121		(BIT25)
	#define		ECM_ECMESSTR0_SSE121_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE121_ERROR		(1)
#define		ECM_ECMESSTR0_SSE120		(BIT24)
	#define		ECM_ECMESSTR0_SSE120_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE120_ERROR		(1)
#define		ECM_ECMESSTR0_SSE119		(BIT23)
	#define		ECM_ECMESSTR0_SSE119_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE119_ERROR		(1)
#define		ECM_ECMESSTR0_SSE118		(BIT22)
	#define		ECM_ECMESSTR0_SSE118_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE118_ERROR		(1)
#define		ECM_ECMESSTR0_SSE117		(BIT21)
	#define		ECM_ECMESSTR0_SSE117_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE117_ERROR		(1)
#define		ECM_ECMESSTR0_SSE116		(BIT20)
	#define		ECM_ECMESSTR0_SSE116_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE116_ERROR		(1)
#define		ECM_ECMESSTR0_SSE115		(BIT19)
	#define		ECM_ECMESSTR0_SSE115_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE115_ERROR		(1)
#define		ECM_ECMESSTR0_SSE114		(BIT18)
	#define		ECM_ECMESSTR0_SSE114_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE114_ERROR		(1)
#define		ECM_ECMESSTR0_SSE113		(BIT17)
	#define		ECM_ECMESSTR0_SSE113_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE113_ERROR		(1)
#define		ECM_ECMESSTR0_SSE112		(BIT16)
	#define		ECM_ECMESSTR0_SSE112_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE112_ERROR		(1)
#define		ECM_ECMESSTR0_SSE111		(BIT15)
	#define		ECM_ECMESSTR0_SSE111_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE111_ERROR		(1)
#define		ECM_ECMESSTR0_SSE110		(BIT14)
	#define		ECM_ECMESSTR0_SSE110_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE110_ERROR		(1)
#define		ECM_ECMESSTR0_SSE109		(BIT13)
	#define		ECM_ECMESSTR0_SSE109_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE109_ERROR		(1)
#define		ECM_ECMESSTR0_SSE108		(BIT12)
	#define		ECM_ECMESSTR0_SSE108_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE108_ERROR		(1)
#define		ECM_ECMESSTR0_SSE107		(BIT11)
	#define		ECM_ECMESSTR0_SSE107_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE107_ERROR		(1)
#define		ECM_ECMESSTR0_SSE106		(BIT10)
	#define		ECM_ECMESSTR0_SSE106_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE106_ERROR		(1)
#define		ECM_ECMESSTR0_SSE105		(BIT9)
	#define		ECM_ECMESSTR0_SSE105_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE105_ERROR		(1)
#define		ECM_ECMESSTR0_SSE104		(BIT8)
	#define		ECM_ECMESSTR0_SSE104_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE104_ERROR		(1)
#define		ECM_ECMESSTR0_SSE103		(BIT7)
	#define		ECM_ECMESSTR0_SSE103_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE103_ERROR		(1)
#define		ECM_ECMESSTR0_SSE102		(BIT6)
	#define		ECM_ECMESSTR0_SSE102_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE102_ERROR		(1)
#define		ECM_ECMESSTR0_SSE101		(BIT5)
	#define		ECM_ECMESSTR0_SSE101_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE101_ERROR		(1)
#define		ECM_ECMESSTR0_SSE100		(BIT4)
	#define		ECM_ECMESSTR0_SSE100_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE100_ERROR		(1)
#define		ECM_ECMESSTR0_SSE099		(BIT3)
	#define		ECM_ECMESSTR0_SSE099_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE099_ERROR		(1)
#define		ECM_ECMESSTR0_SSE098		(BIT2)
	#define		ECM_ECMESSTR0_SSE098_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE098_ERROR		(1)
#define		ECM_ECMESSTR0_SSE097		(BIT1)
	#define		ECM_ECMESSTR0_SSE097_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE097_ERROR		(1)
#define		ECM_ECMESSTR0_SSE096		(BIT0)
	#define		ECM_ECMESSTR0_SSE096_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE096_ERROR		(1)

/* ECMmESSTR4,m=M/C */
#define		ECM_ECMESSTR0_SSE159		(BIT31)
	#define		ECM_ECMESSTR0_SSE159_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE159_ERROR		(1)
#define		ECM_ECMESSTR0_SSE158		(BIT30)
	#define		ECM_ECMESSTR0_SSE158_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE158_ERROR		(1)
#define		ECM_ECMESSTR0_SSE157		(BIT29)
	#define		ECM_ECMESSTR0_SSE157_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE157_ERROR		(1)
#define		ECM_ECMESSTR0_SSE156		(BIT28)
	#define		ECM_ECMESSTR0_SSE156_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE156_ERROR		(1)
#define		ECM_ECMESSTR0_SSE155		(BIT27)
	#define		ECM_ECMESSTR0_SSE155_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE155_ERROR		(1)
#define		ECM_ECMESSTR0_SSE154		(BIT26)
	#define		ECM_ECMESSTR0_SSE154_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE154_ERROR		(1)
#define		ECM_ECMESSTR0_SSE153		(BIT25)
	#define		ECM_ECMESSTR0_SSE153_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE153_ERROR		(1)
#define		ECM_ECMESSTR0_SSE152		(BIT24)
	#define		ECM_ECMESSTR0_SSE152_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE152_ERROR		(1)
#define		ECM_ECMESSTR0_SSE151		(BIT23)
	#define		ECM_ECMESSTR0_SSE151_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE151_ERROR		(1)
#define		ECM_ECMESSTR0_SSE150		(BIT22)
	#define		ECM_ECMESSTR0_SSE150_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE150_ERROR		(1)
#define		ECM_ECMESSTR0_SSE149		(BIT21)
	#define		ECM_ECMESSTR0_SSE149_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE149_ERROR		(1)
#define		ECM_ECMESSTR0_SSE148		(BIT20)
	#define		ECM_ECMESSTR0_SSE148_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE148_ERROR		(1)
#define		ECM_ECMESSTR0_SSE147		(BIT19)
	#define		ECM_ECMESSTR0_SSE147_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE147_ERROR		(1)
#define		ECM_ECMESSTR0_SSE146		(BIT18)
	#define		ECM_ECMESSTR0_SSE146_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE146_ERROR		(1)
#define		ECM_ECMESSTR0_SSE145		(BIT17)
	#define		ECM_ECMESSTR0_SSE145_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE145_ERROR		(1)
#define		ECM_ECMESSTR0_SSE144		(BIT16)
	#define		ECM_ECMESSTR0_SSE144_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE144_ERROR		(1)
#define		ECM_ECMESSTR0_SSE143		(BIT15)
	#define		ECM_ECMESSTR0_SSE143_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE143_ERROR		(1)
#define		ECM_ECMESSTR0_SSE142		(BIT14)
	#define		ECM_ECMESSTR0_SSE142_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE142_ERROR		(1)
#define		ECM_ECMESSTR0_SSE141		(BIT13)
	#define		ECM_ECMESSTR0_SSE141_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE141_ERROR		(1)
#define		ECM_ECMESSTR0_SSE140		(BIT12)
	#define		ECM_ECMESSTR0_SSE140_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE140_ERROR		(1)
#define		ECM_ECMESSTR0_SSE139		(BIT11)
	#define		ECM_ECMESSTR0_SSE139_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE139_ERROR		(1)
#define		ECM_ECMESSTR0_SSE138		(BIT10)
	#define		ECM_ECMESSTR0_SSE138_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE138_ERROR		(1)
#define		ECM_ECMESSTR0_SSE137		(BIT9)
	#define		ECM_ECMESSTR0_SSE137_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE137_ERROR		(1)
#define		ECM_ECMESSTR0_SSE136		(BIT8)
	#define		ECM_ECMESSTR0_SSE136_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE136_ERROR		(1)
#define		ECM_ECMESSTR0_SSE135		(BIT7)
	#define		ECM_ECMESSTR0_SSE135_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE135_ERROR		(1)
#define		ECM_ECMESSTR0_SSE134		(BIT6)
	#define		ECM_ECMESSTR0_SSE134_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE134_ERROR		(1)
#define		ECM_ECMESSTR0_SSE133		(BIT5)
	#define		ECM_ECMESSTR0_SSE133_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE133_ERROR		(1)
#define		ECM_ECMESSTR0_SSE132		(BIT4)
	#define		ECM_ECMESSTR0_SSE132_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE132_ERROR		(1)
#define		ECM_ECMESSTR0_SSE131		(BIT3)
	#define		ECM_ECMESSTR0_SSE131_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE131_ERROR		(1)
#define		ECM_ECMESSTR0_SSE130		(BIT2)
	#define		ECM_ECMESSTR0_SSE130_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE130_ERROR		(1)
#define		ECM_ECMESSTR0_SSE129		(BIT1)
	#define		ECM_ECMESSTR0_SSE129_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE129_ERROR		(1)
#define		ECM_ECMESSTR0_SSE128		(BIT0)
	#define		ECM_ECMESSTR0_SSE128_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE128_ERROR		(1)

/* ECMmESSTR5,m=M/C */
#define		ECM_ECMESSTR0_SSE191		(BIT31)
	#define		ECM_ECMESSTR0_SSE191_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE191_ERROR		(1)
#define		ECM_ECMESSTR0_SSE190		(BIT30)
	#define		ECM_ECMESSTR0_SSE190_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE190_ERROR		(1)
#define		ECM_ECMESSTR0_SSE189		(BIT29)
	#define		ECM_ECMESSTR0_SSE189_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE189_ERROR		(1)
#define		ECM_ECMESSTR0_SSE188		(BIT28)
	#define		ECM_ECMESSTR0_SSE188_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE188_ERROR		(1)
#define		ECM_ECMESSTR0_SSE187		(BIT27)
	#define		ECM_ECMESSTR0_SSE187_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE187_ERROR		(1)
#define		ECM_ECMESSTR0_SSE186		(BIT26)
	#define		ECM_ECMESSTR0_SSE186_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE186_ERROR		(1)
#define		ECM_ECMESSTR0_SSE185		(BIT25)
	#define		ECM_ECMESSTR0_SSE185_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE185_ERROR		(1)
#define		ECM_ECMESSTR0_SSE184		(BIT24)
	#define		ECM_ECMESSTR0_SSE184_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE184_ERROR		(1)
#define		ECM_ECMESSTR0_SSE183		(BIT23)
	#define		ECM_ECMESSTR0_SSE183_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE183_ERROR		(1)
#define		ECM_ECMESSTR0_SSE182		(BIT22)
	#define		ECM_ECMESSTR0_SSE182_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE182_ERROR		(1)
#define		ECM_ECMESSTR0_SSE181		(BIT21)
	#define		ECM_ECMESSTR0_SSE181_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE181_ERROR		(1)
#define		ECM_ECMESSTR0_SSE180		(BIT20)
	#define		ECM_ECMESSTR0_SSE180_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE180_ERROR		(1)
#define		ECM_ECMESSTR0_SSE179		(BIT19)
	#define		ECM_ECMESSTR0_SSE179_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE179_ERROR		(1)
#define		ECM_ECMESSTR0_SSE178		(BIT18)
	#define		ECM_ECMESSTR0_SSE178_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE178_ERROR		(1)
#define		ECM_ECMESSTR0_SSE177		(BIT17)
	#define		ECM_ECMESSTR0_SSE177_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE177_ERROR		(1)
#define		ECM_ECMESSTR0_SSE176		(BIT16)
	#define		ECM_ECMESSTR0_SSE176_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE176_ERROR		(1)
#define		ECM_ECMESSTR0_SSE175		(BIT15)
	#define		ECM_ECMESSTR0_SSE175_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE175_ERROR		(1)
#define		ECM_ECMESSTR0_SSE174		(BIT14)
	#define		ECM_ECMESSTR0_SSE174_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE174_ERROR		(1)
#define		ECM_ECMESSTR0_SSE173		(BIT13)
	#define		ECM_ECMESSTR0_SSE173_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE173_ERROR		(1)
#define		ECM_ECMESSTR0_SSE172		(BIT12)
	#define		ECM_ECMESSTR0_SSE172_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE172_ERROR		(1)
#define		ECM_ECMESSTR0_SSE171		(BIT11)
	#define		ECM_ECMESSTR0_SSE171_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE171_ERROR		(1)
#define		ECM_ECMESSTR0_SSE170		(BIT10)
	#define		ECM_ECMESSTR0_SSE170_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE170_ERROR		(1)
#define		ECM_ECMESSTR0_SSE169		(BIT9)
	#define		ECM_ECMESSTR0_SSE169_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE169_ERROR		(1)
#define		ECM_ECMESSTR0_SSE168		(BIT8)
	#define		ECM_ECMESSTR0_SSE168_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE168_ERROR		(1)
#define		ECM_ECMESSTR0_SSE167		(BIT7)
	#define		ECM_ECMESSTR0_SSE167_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE167_ERROR		(1)
#define		ECM_ECMESSTR0_SSE166		(BIT6)
	#define		ECM_ECMESSTR0_SSE166_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE166_ERROR		(1)
#define		ECM_ECMESSTR0_SSE165		(BIT5)
	#define		ECM_ECMESSTR0_SSE165_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE165_ERROR		(1)
#define		ECM_ECMESSTR0_SSE164		(BIT4)
	#define		ECM_ECMESSTR0_SSE164_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE164_ERROR		(1)
#define		ECM_ECMESSTR0_SSE163		(BIT3)
	#define		ECM_ECMESSTR0_SSE163_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE163_ERROR		(1)
#define		ECM_ECMESSTR0_SSE162		(BIT2)
	#define		ECM_ECMESSTR0_SSE162_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE162_ERROR		(1)
#define		ECM_ECMESSTR0_SSE161		(BIT1)
	#define		ECM_ECMESSTR0_SSE161_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE161_ERROR		(1)
#define		ECM_ECMESSTR0_SSE160		(BIT0)
	#define		ECM_ECMESSTR0_SSE160_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE160_ERROR		(1)

/* ECMmESSTR6,m=M/C */
#define		ECM_ECMESSTR0_SSE223		(BIT31)
	#define		ECM_ECMESSTR0_SSE223_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE223_ERROR		(1)
#define		ECM_ECMESSTR0_SSE222		(BIT30)
	#define		ECM_ECMESSTR0_SSE222_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE222_ERROR		(1)
#define		ECM_ECMESSTR0_SSE221		(BIT29)
	#define		ECM_ECMESSTR0_SSE221_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE221_ERROR		(1)
#define		ECM_ECMESSTR0_SSE220		(BIT28)
	#define		ECM_ECMESSTR0_SSE220_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE220_ERROR		(1)
#define		ECM_ECMESSTR0_SSE219		(BIT27)
	#define		ECM_ECMESSTR0_SSE219_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE219_ERROR		(1)
#define		ECM_ECMESSTR0_SSE218		(BIT26)
	#define		ECM_ECMESSTR0_SSE218_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE218_ERROR		(1)
#define		ECM_ECMESSTR0_SSE217		(BIT25)
	#define		ECM_ECMESSTR0_SSE217_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE217_ERROR		(1)
#define		ECM_ECMESSTR0_SSE216		(BIT24)
	#define		ECM_ECMESSTR0_SSE216_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE216_ERROR		(1)
#define		ECM_ECMESSTR0_SSE215		(BIT23)
	#define		ECM_ECMESSTR0_SSE215_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE215_ERROR		(1)
#define		ECM_ECMESSTR0_SSE214		(BIT22)
	#define		ECM_ECMESSTR0_SSE214_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE214_ERROR		(1)
#define		ECM_ECMESSTR0_SSE213		(BIT21)
	#define		ECM_ECMESSTR0_SSE213_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE213_ERROR		(1)
#define		ECM_ECMESSTR0_SSE212		(BIT20)
	#define		ECM_ECMESSTR0_SSE212_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE212_ERROR		(1)
#define		ECM_ECMESSTR0_SSE211		(BIT19)
	#define		ECM_ECMESSTR0_SSE211_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE211_ERROR		(1)
#define		ECM_ECMESSTR0_SSE210		(BIT18)
	#define		ECM_ECMESSTR0_SSE210_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE210_ERROR		(1)
#define		ECM_ECMESSTR0_SSE209		(BIT17)
	#define		ECM_ECMESSTR0_SSE209_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE209_ERROR		(1)
#define		ECM_ECMESSTR0_SSE208		(BIT16)
	#define		ECM_ECMESSTR0_SSE208_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE208_ERROR		(1)
#define		ECM_ECMESSTR0_SSE207		(BIT15)
	#define		ECM_ECMESSTR0_SSE207_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE207_ERROR		(1)
#define		ECM_ECMESSTR0_SSE206		(BIT14)
	#define		ECM_ECMESSTR0_SSE206_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE206_ERROR		(1)
#define		ECM_ECMESSTR0_SSE205		(BIT13)
	#define		ECM_ECMESSTR0_SSE205_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE205_ERROR		(1)
#define		ECM_ECMESSTR0_SSE204		(BIT12)
	#define		ECM_ECMESSTR0_SSE204_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE204_ERROR		(1)
#define		ECM_ECMESSTR0_SSE203		(BIT11)
	#define		ECM_ECMESSTR0_SSE203_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE203_ERROR		(1)
#define		ECM_ECMESSTR0_SSE202		(BIT10)
	#define		ECM_ECMESSTR0_SSE202_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE202_ERROR		(1)
#define		ECM_ECMESSTR0_SSE201		(BIT9)
	#define		ECM_ECMESSTR0_SSE201_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE201_ERROR		(1)
#define		ECM_ECMESSTR0_SSE200		(BIT8)
	#define		ECM_ECMESSTR0_SSE200_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE200_ERROR		(1)
#define		ECM_ECMESSTR0_SSE199		(BIT7)
	#define		ECM_ECMESSTR0_SSE199_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE199_ERROR		(1)
#define		ECM_ECMESSTR0_SSE198		(BIT6)
	#define		ECM_ECMESSTR0_SSE198_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE198_ERROR		(1)
#define		ECM_ECMESSTR0_SSE197		(BIT5)
	#define		ECM_ECMESSTR0_SSE197_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE197_ERROR		(1)
#define		ECM_ECMESSTR0_SSE196		(BIT4)
	#define		ECM_ECMESSTR0_SSE196_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE196_ERROR		(1)
#define		ECM_ECMESSTR0_SSE195		(BIT3)
	#define		ECM_ECMESSTR0_SSE195_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE195_ERROR		(1)
#define		ECM_ECMESSTR0_SSE194		(BIT2)
	#define		ECM_ECMESSTR0_SSE194_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE194_ERROR		(1)
#define		ECM_ECMESSTR0_SSE193		(BIT1)
	#define		ECM_ECMESSTR0_SSE193_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE193_ERROR		(1)
#define		ECM_ECMESSTR0_SSE192		(BIT0)
	#define		ECM_ECMESSTR0_SSE192_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE192_ERROR		(1)

/* ECMmESSTR7,m=M/C */
#define		ECM_ECMESSTR0_SSE255		(BIT31)
	#define		ECM_ECMESSTR0_SSE255_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE255_ERROR		(1)
#define		ECM_ECMESSTR0_SSE254		(BIT30)
	#define		ECM_ECMESSTR0_SSE254_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE254_ERROR		(1)
#define		ECM_ECMESSTR0_SSE253		(BIT29)
	#define		ECM_ECMESSTR0_SSE253_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE253_ERROR		(1)
#define		ECM_ECMESSTR0_SSE252		(BIT28)
	#define		ECM_ECMESSTR0_SSE252_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE252_ERROR		(1)
#define		ECM_ECMESSTR0_SSE251		(BIT27)
	#define		ECM_ECMESSTR0_SSE251_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE251_ERROR		(1)
#define		ECM_ECMESSTR0_SSE250		(BIT26)
	#define		ECM_ECMESSTR0_SSE250_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE250_ERROR		(1)
#define		ECM_ECMESSTR0_SSE249		(BIT25)
	#define		ECM_ECMESSTR0_SSE249_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE249_ERROR		(1)
#define		ECM_ECMESSTR0_SSE248		(BIT24)
	#define		ECM_ECMESSTR0_SSE248_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE248_ERROR		(1)
#define		ECM_ECMESSTR0_SSE247		(BIT23)
	#define		ECM_ECMESSTR0_SSE247_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE247_ERROR		(1)
#define		ECM_ECMESSTR0_SSE246		(BIT22)
	#define		ECM_ECMESSTR0_SSE246_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE246_ERROR		(1)
#define		ECM_ECMESSTR0_SSE245		(BIT21)
	#define		ECM_ECMESSTR0_SSE245_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE245_ERROR		(1)
#define		ECM_ECMESSTR0_SSE244		(BIT20)
	#define		ECM_ECMESSTR0_SSE244_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE244_ERROR		(1)
#define		ECM_ECMESSTR0_SSE243		(BIT19)
	#define		ECM_ECMESSTR0_SSE243_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE243_ERROR		(1)
#define		ECM_ECMESSTR0_SSE242		(BIT18)
	#define		ECM_ECMESSTR0_SSE242_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE242_ERROR		(1)
#define		ECM_ECMESSTR0_SSE241		(BIT17)
	#define		ECM_ECMESSTR0_SSE241_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE241_ERROR		(1)
#define		ECM_ECMESSTR0_SSE240		(BIT16)
	#define		ECM_ECMESSTR0_SSE240_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE240_ERROR		(1)
#define		ECM_ECMESSTR0_SSE239		(BIT15)
	#define		ECM_ECMESSTR0_SSE239_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE239_ERROR		(1)
#define		ECM_ECMESSTR0_SSE238		(BIT14)
	#define		ECM_ECMESSTR0_SSE238_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE238_ERROR		(1)
#define		ECM_ECMESSTR0_SSE237		(BIT13)
	#define		ECM_ECMESSTR0_SSE237_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE237_ERROR		(1)
#define		ECM_ECMESSTR0_SSE236		(BIT12)
	#define		ECM_ECMESSTR0_SSE236_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE236_ERROR		(1)
#define		ECM_ECMESSTR0_SSE235		(BIT11)
	#define		ECM_ECMESSTR0_SSE235_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE235_ERROR		(1)
#define		ECM_ECMESSTR0_SSE234		(BIT10)
	#define		ECM_ECMESSTR0_SSE234_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE234_ERROR		(1)
#define		ECM_ECMESSTR0_SSE233		(BIT9)
	#define		ECM_ECMESSTR0_SSE233_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE233_ERROR		(1)
#define		ECM_ECMESSTR0_SSE232		(BIT8)
	#define		ECM_ECMESSTR0_SSE232_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE232_ERROR		(1)
#define		ECM_ECMESSTR0_SSE231		(BIT7)
	#define		ECM_ECMESSTR0_SSE231_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE231_ERROR		(1)
#define		ECM_ECMESSTR0_SSE230		(BIT6)
	#define		ECM_ECMESSTR0_SSE230_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE230_ERROR		(1)
#define		ECM_ECMESSTR0_SSE229		(BIT5)
	#define		ECM_ECMESSTR0_SSE229_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE229_ERROR		(1)
#define		ECM_ECMESSTR0_SSE228		(BIT4)
	#define		ECM_ECMESSTR0_SSE228_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE228_ERROR		(1)
#define		ECM_ECMESSTR0_SSE227		(BIT3)
	#define		ECM_ECMESSTR0_SSE227_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE227_ERROR		(1)
#define		ECM_ECMESSTR0_SSE226		(BIT2)
	#define		ECM_ECMESSTR0_SSE226_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE226_ERROR		(1)
#define		ECM_ECMESSTR0_SSE225		(BIT1)
	#define		ECM_ECMESSTR0_SSE225_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE225_ERROR		(1)
#define		ECM_ECMESSTR0_SSE224		(BIT0)
	#define		ECM_ECMESSTR0_SSE224_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE224_ERROR		(1)

/* ECMmESSTR8,m=M/C */
#define		ECM_ECMESSTR8_SSE279		(BIT31)
	#define		ECM_ECMESSTR8_SSE279_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE279_ERROR		(1)
#define		ECM_ECMESSTR8_SSE278		(BIT30)
	#define		ECM_ECMESSTR8_SSE278_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE278_ERROR		(1)
#define		ECM_ECMESSTR8_SSE277		(BIT29)
	#define		ECM_ECMESSTR8_SSE277_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE277_ERROR		(1)
#define		ECM_ECMESSTR8_SSE276		(BIT28)
	#define		ECM_ECMESSTR8_SSE276_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE276_ERROR		(1)
#define		ECM_ECMESSTR8_SSE275		(BIT27)
	#define		ECM_ECMESSTR8_SSE275_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE275_ERROR		(1)
#define		ECM_ECMESSTR8_SSE274		(BIT26)
	#define		ECM_ECMESSTR8_SSE274_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE274_ERROR		(1)
#define		ECM_ECMESSTR8_SSE273		(BIT25)
	#define		ECM_ECMESSTR8_SSE273_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE273_ERROR		(1)
#define		ECM_ECMESSTR8_SSE272		(BIT24)
	#define		ECM_ECMESSTR8_SSE272_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE272_ERROR		(1)
#define		ECM_ECMESSTR8_SSE271		(BIT23)
	#define		ECM_ECMESSTR8_SSE271_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE271_ERROR		(1)
#define		ECM_ECMESSTR8_SSE270		(BIT22)
	#define		ECM_ECMESSTR8_SSE270_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE270_ERROR		(1)
#define		ECM_ECMESSTR8_SSE269		(BIT21)
	#define		ECM_ECMESSTR8_SSE269_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE269_ERROR		(1)
#define		ECM_ECMESSTR8_SSE268		(BIT20)
	#define		ECM_ECMESSTR8_SSE268_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE268_ERROR		(1)
#define		ECM_ECMESSTR8_SSE267		(BIT19)
	#define		ECM_ECMESSTR8_SSE267_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE267_ERROR		(1)
#define		ECM_ECMESSTR8_SSE266		(BIT18)
	#define		ECM_ECMESSTR8_SSE266_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE266_ERROR		(1)
#define		ECM_ECMESSTR8_SSE265		(BIT17)
	#define		ECM_ECMESSTR8_SSE265_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE265_ERROR		(1)
#define		ECM_ECMESSTR8_SSE264		(BIT16)
	#define		ECM_ECMESSTR8_SSE264_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE264_ERROR		(1)
#define		ECM_ECMESSTR8_SSE263		(BIT15)
	#define		ECM_ECMESSTR8_SSE263_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE263_ERROR		(1)
#define		ECM_ECMESSTR8_SSE262		(BIT14)
	#define		ECM_ECMESSTR8_SSE262_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE262_ERROR		(1)
#define		ECM_ECMESSTR8_SSE261		(BIT13)
	#define		ECM_ECMESSTR8_SSE261_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE261_ERROR		(1)
#define		ECM_ECMESSTR8_SSE260		(BIT12)
	#define		ECM_ECMESSTR8_SSE260_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE260_ERROR		(1)
#define		ECM_ECMESSTR8_SSE259		(BIT11)
	#define		ECM_ECMESSTR8_SSE259_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE259_ERROR		(1)
#define		ECM_ECMESSTR8_SSE258		(BIT10)
	#define		ECM_ECMESSTR8_SSE258_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE258_ERROR		(1)
#define		ECM_ECMESSTR8_SSE257		(BIT9)
	#define		ECM_ECMESSTR8_SSE257_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE257_ERROR		(1)
#define		ECM_ECMESSTR8_SSE256		(BIT8)
	#define		ECM_ECMESSTR8_SSE256_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE256_ERROR		(1)
#define		ECM_ECMESSTR8_SSE255		(BIT7)
	#define		ECM_ECMESSTR8_SSE255_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE255_ERROR		(1)
#define		ECM_ECMESSTR8_SSE254		(BIT6)
	#define		ECM_ECMESSTR8_SSE254_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE254_ERROR		(1)
#define		ECM_ECMESSTR8_SSE253		(BIT5)
	#define		ECM_ECMESSTR8_SSE253_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE253_ERROR		(1)
#define		ECM_ECMESSTR8_SSE252		(BIT4)
	#define		ECM_ECMESSTR8_SSE252_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE252_ERROR		(1)
#define		ECM_ECMESSTR8_SSE251		(BIT3)
	#define		ECM_ECMESSTR8_SSE251_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE251_ERROR		(1)
#define		ECM_ECMESSTR8_SSE250		(BIT2)
	#define		ECM_ECMESSTR8_SSE250_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE250_ERROR		(1)
#define		ECM_ECMESSTR8_SSE249		(BIT1)
	#define		ECM_ECMESSTR8_SSE249_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE249_ERROR		(1)
#define		ECM_ECMESSTR8_SSE248		(BIT0)
	#define		ECM_ECMESSTR8_SSE248_NOERROR	(0)
	#define		ECM_ECMESSTR8_SSE248_ERROR		(1)

/* ECMmESSTR9,m=M/C */
#define		ECM_ECMESSTR0_SSE319		(BIT31)
	#define		ECM_ECMESSTR0_SSE319_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE319_ERROR		(1)
#define		ECM_ECMESSTR0_SSE318		(BIT30)
	#define		ECM_ECMESSTR0_SSE318_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE318_ERROR		(1)
#define		ECM_ECMESSTR0_SSE317		(BIT29)
	#define		ECM_ECMESSTR0_SSE317_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE317_ERROR		(1)
#define		ECM_ECMESSTR0_SSE316		(BIT28)
	#define		ECM_ECMESSTR0_SSE316_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE316_ERROR		(1)
#define		ECM_ECMESSTR0_SSE315		(BIT27)
	#define		ECM_ECMESSTR0_SSE315_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE315_ERROR		(1)
#define		ECM_ECMESSTR0_SSE314		(BIT26)
	#define		ECM_ECMESSTR0_SSE314_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE314_ERROR		(1)
#define		ECM_ECMESSTR0_SSE313		(BIT25)
	#define		ECM_ECMESSTR0_SSE313_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE313_ERROR		(1)
#define		ECM_ECMESSTR0_SSE312		(BIT24)
	#define		ECM_ECMESSTR0_SSE312_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE312_ERROR		(1)
#define		ECM_ECMESSTR0_SSE311		(BIT23)
	#define		ECM_ECMESSTR0_SSE311_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE311_ERROR		(1)
#define		ECM_ECMESSTR0_SSE310		(BIT22)
	#define		ECM_ECMESSTR0_SSE310_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE310_ERROR		(1)
#define		ECM_ECMESSTR0_SSE309		(BIT21)
	#define		ECM_ECMESSTR0_SSE309_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE309_ERROR		(1)
#define		ECM_ECMESSTR0_SSE308		(BIT20)
	#define		ECM_ECMESSTR0_SSE308_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE308_ERROR		(1)
#define		ECM_ECMESSTR0_SSE307		(BIT19)
	#define		ECM_ECMESSTR0_SSE307_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE307_ERROR		(1)
#define		ECM_ECMESSTR0_SSE306		(BIT18)
	#define		ECM_ECMESSTR0_SSE306_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE306_ERROR		(1)
#define		ECM_ECMESSTR0_SSE305		(BIT17)
	#define		ECM_ECMESSTR0_SSE305_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE305_ERROR		(1)
#define		ECM_ECMESSTR0_SSE304		(BIT16)
	#define		ECM_ECMESSTR0_SSE304_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE304_ERROR		(1)
#define		ECM_ECMESSTR0_SSE303		(BIT15)
	#define		ECM_ECMESSTR0_SSE303_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE303_ERROR		(1)
#define		ECM_ECMESSTR0_SSE302		(BIT14)
	#define		ECM_ECMESSTR0_SSE302_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE302_ERROR		(1)
#define		ECM_ECMESSTR0_SSE301		(BIT13)
	#define		ECM_ECMESSTR0_SSE301_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE301_ERROR		(1)
#define		ECM_ECMESSTR0_SSE300		(BIT12)
	#define		ECM_ECMESSTR0_SSE300_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE300_ERROR		(1)
#define		ECM_ECMESSTR0_SSE299		(BIT11)
	#define		ECM_ECMESSTR0_SSE299_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE299_ERROR		(1)
#define		ECM_ECMESSTR0_SSE298		(BIT10)
	#define		ECM_ECMESSTR0_SSE298_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE298_ERROR		(1)
#define		ECM_ECMESSTR0_SSE297		(BIT9)
	#define		ECM_ECMESSTR0_SSE297_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE297_ERROR		(1)
#define		ECM_ECMESSTR0_SSE296		(BIT8)
	#define		ECM_ECMESSTR0_SSE296_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE296_ERROR		(1)
#define		ECM_ECMESSTR0_SSE295		(BIT7)
	#define		ECM_ECMESSTR0_SSE295_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE295_ERROR		(1)
#define		ECM_ECMESSTR0_SSE294		(BIT6)
	#define		ECM_ECMESSTR0_SSE294_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE294_ERROR		(1)
#define		ECM_ECMESSTR0_SSE293		(BIT5)
	#define		ECM_ECMESSTR0_SSE293_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE293_ERROR		(1)
#define		ECM_ECMESSTR0_SSE292		(BIT4)
	#define		ECM_ECMESSTR0_SSE292_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE292_ERROR		(1)
#define		ECM_ECMESSTR0_SSE291		(BIT3)
	#define		ECM_ECMESSTR0_SSE291_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE291_ERROR		(1)
#define		ECM_ECMESSTR0_SSE290		(BIT2)
	#define		ECM_ECMESSTR0_SSE290_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE290_ERROR		(1)
#define		ECM_ECMESSTR0_SSE289		(BIT1)
	#define		ECM_ECMESSTR0_SSE289_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE289_ERROR		(1)
#define		ECM_ECMESSTR0_SSE288		(BIT0)
	#define		ECM_ECMESSTR0_SSE288_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE288_ERROR		(1)

/* ECMmESSTR10,m=M/C */
#define		ECM_ECMESSTR0_SSE351		(BIT31)
	#define		ECM_ECMESSTR0_SSE351_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE351_ERROR		(1)
#define		ECM_ECMESSTR0_SSE350		(BIT30)
	#define		ECM_ECMESSTR0_SSE350_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE350_ERROR		(1)
#define		ECM_ECMESSTR0_SSE349		(BIT29)
	#define		ECM_ECMESSTR0_SSE349_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE349_ERROR		(1)
#define		ECM_ECMESSTR0_SSE348		(BIT28)
	#define		ECM_ECMESSTR0_SSE348_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE348_ERROR		(1)
#define		ECM_ECMESSTR0_SSE347		(BIT27)
	#define		ECM_ECMESSTR0_SSE347_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE347_ERROR		(1)
#define		ECM_ECMESSTR0_SSE346		(BIT26)
	#define		ECM_ECMESSTR0_SSE346_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE346_ERROR		(1)
#define		ECM_ECMESSTR0_SSE345		(BIT25)
	#define		ECM_ECMESSTR0_SSE345_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE345_ERROR		(1)
#define		ECM_ECMESSTR0_SSE344		(BIT24)
	#define		ECM_ECMESSTR0_SSE344_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE344_ERROR		(1)
#define		ECM_ECMESSTR0_SSE343		(BIT23)
	#define		ECM_ECMESSTR0_SSE343_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE343_ERROR		(1)
#define		ECM_ECMESSTR0_SSE342		(BIT22)
	#define		ECM_ECMESSTR0_SSE342_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE342_ERROR		(1)
#define		ECM_ECMESSTR0_SSE341		(BIT21)
	#define		ECM_ECMESSTR0_SSE341_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE341_ERROR		(1)
#define		ECM_ECMESSTR0_SSE340		(BIT20)
	#define		ECM_ECMESSTR0_SSE340_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE340_ERROR		(1)
#define		ECM_ECMESSTR0_SSE339		(BIT19)
	#define		ECM_ECMESSTR0_SSE339_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE339_ERROR		(1)
#define		ECM_ECMESSTR0_SSE338		(BIT18)
	#define		ECM_ECMESSTR0_SSE338_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE338_ERROR		(1)
#define		ECM_ECMESSTR0_SSE337		(BIT17)
	#define		ECM_ECMESSTR0_SSE337_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE337_ERROR		(1)
#define		ECM_ECMESSTR0_SSE336		(BIT16)
	#define		ECM_ECMESSTR0_SSE336_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE336_ERROR		(1)
#define		ECM_ECMESSTR0_SSE335		(BIT15)
	#define		ECM_ECMESSTR0_SSE335_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE335_ERROR		(1)
#define		ECM_ECMESSTR0_SSE334		(BIT14)
	#define		ECM_ECMESSTR0_SSE334_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE334_ERROR		(1)
#define		ECM_ECMESSTR0_SSE333		(BIT13)
	#define		ECM_ECMESSTR0_SSE333_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE333_ERROR		(1)
#define		ECM_ECMESSTR0_SSE332		(BIT12)
	#define		ECM_ECMESSTR0_SSE332_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE332_ERROR		(1)
#define		ECM_ECMESSTR0_SSE331		(BIT11)
	#define		ECM_ECMESSTR0_SSE331_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE331_ERROR		(1)
#define		ECM_ECMESSTR0_SSE330		(BIT10)
	#define		ECM_ECMESSTR0_SSE330_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE330_ERROR		(1)
#define		ECM_ECMESSTR0_SSE329		(BIT9)
	#define		ECM_ECMESSTR0_SSE329_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE329_ERROR		(1)
#define		ECM_ECMESSTR0_SSE328		(BIT8)
	#define		ECM_ECMESSTR0_SSE328_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE328_ERROR		(1)
#define		ECM_ECMESSTR0_SSE327		(BIT7)
	#define		ECM_ECMESSTR0_SSE327_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE327_ERROR		(1)
#define		ECM_ECMESSTR0_SSE326		(BIT6)
	#define		ECM_ECMESSTR0_SSE326_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE326_ERROR		(1)
#define		ECM_ECMESSTR0_SSE325		(BIT5)
	#define		ECM_ECMESSTR0_SSE325_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE325_ERROR		(1)
#define		ECM_ECMESSTR0_SSE324		(BIT4)
	#define		ECM_ECMESSTR0_SSE324_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE324_ERROR		(1)
#define		ECM_ECMESSTR0_SSE323		(BIT3)
	#define		ECM_ECMESSTR0_SSE323_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE323_ERROR		(1)
#define		ECM_ECMESSTR0_SSE322		(BIT2)
	#define		ECM_ECMESSTR0_SSE322_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE322_ERROR		(1)
#define		ECM_ECMESSTR0_SSE321		(BIT1)
	#define		ECM_ECMESSTR0_SSE321_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE321_ERROR		(1)
#define		ECM_ECMESSTR0_SSE320		(BIT0)
	#define		ECM_ECMESSTR0_SSE320_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE320_ERROR		(1)

/* ECMmESSTR11,m=M/C */
#define		ECM_ECMESSTR0_SSE383		(BIT31)
	#define		ECM_ECMESSTR0_SSE383_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE383_ERROR		(1)
#define		ECM_ECMESSTR0_SSE382		(BIT30)
	#define		ECM_ECMESSTR0_SSE382_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE382_ERROR		(1)
#define		ECM_ECMESSTR0_SSE381		(BIT29)
	#define		ECM_ECMESSTR0_SSE381_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE381_ERROR		(1)
#define		ECM_ECMESSTR0_SSE380		(BIT28)
	#define		ECM_ECMESSTR0_SSE380_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE380_ERROR		(1)
#define		ECM_ECMESSTR0_SSE379		(BIT27)
	#define		ECM_ECMESSTR0_SSE379_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE379_ERROR		(1)
#define		ECM_ECMESSTR0_SSE378		(BIT26)
	#define		ECM_ECMESSTR0_SSE378_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE378_ERROR		(1)
#define		ECM_ECMESSTR0_SSE377		(BIT25)
	#define		ECM_ECMESSTR0_SSE377_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE377_ERROR		(1)
#define		ECM_ECMESSTR0_SSE376		(BIT24)
	#define		ECM_ECMESSTR0_SSE376_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE376_ERROR		(1)
#define		ECM_ECMESSTR0_SSE375		(BIT23)
	#define		ECM_ECMESSTR0_SSE375_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE375_ERROR		(1)
#define		ECM_ECMESSTR0_SSE374		(BIT22)
	#define		ECM_ECMESSTR0_SSE374_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE374_ERROR		(1)
#define		ECM_ECMESSTR0_SSE373		(BIT21)
	#define		ECM_ECMESSTR0_SSE373_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE373_ERROR		(1)
#define		ECM_ECMESSTR0_SSE372		(BIT20)
	#define		ECM_ECMESSTR0_SSE372_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE372_ERROR		(1)
#define		ECM_ECMESSTR0_SSE371		(BIT19)
	#define		ECM_ECMESSTR0_SSE371_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE371_ERROR		(1)
#define		ECM_ECMESSTR0_SSE370		(BIT18)
	#define		ECM_ECMESSTR0_SSE370_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE370_ERROR		(1)
#define		ECM_ECMESSTR0_SSE369		(BIT17)
	#define		ECM_ECMESSTR0_SSE369_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE369_ERROR		(1)
#define		ECM_ECMESSTR0_SSE368		(BIT16)
	#define		ECM_ECMESSTR0_SSE368_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE368_ERROR		(1)
#define		ECM_ECMESSTR0_SSE367		(BIT15)
	#define		ECM_ECMESSTR0_SSE367_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE367_ERROR		(1)
#define		ECM_ECMESSTR0_SSE366		(BIT14)
	#define		ECM_ECMESSTR0_SSE366_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE366_ERROR		(1)
#define		ECM_ECMESSTR0_SSE365		(BIT13)
	#define		ECM_ECMESSTR0_SSE365_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE365_ERROR		(1)
#define		ECM_ECMESSTR0_SSE364		(BIT12)
	#define		ECM_ECMESSTR0_SSE364_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE364_ERROR		(1)
#define		ECM_ECMESSTR0_SSE363		(BIT11)
	#define		ECM_ECMESSTR0_SSE363_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE363_ERROR		(1)
#define		ECM_ECMESSTR0_SSE362		(BIT10)
	#define		ECM_ECMESSTR0_SSE362_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE362_ERROR		(1)
#define		ECM_ECMESSTR0_SSE361		(BIT9)
	#define		ECM_ECMESSTR0_SSE361_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE361_ERROR		(1)
#define		ECM_ECMESSTR0_SSE360		(BIT8)
	#define		ECM_ECMESSTR0_SSE360_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE360_ERROR		(1)
#define		ECM_ECMESSTR0_SSE359		(BIT7)
	#define		ECM_ECMESSTR0_SSE359_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE359_ERROR		(1)
#define		ECM_ECMESSTR0_SSE358		(BIT6)
	#define		ECM_ECMESSTR0_SSE358_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE358_ERROR		(1)
#define		ECM_ECMESSTR0_SSE357		(BIT5)
	#define		ECM_ECMESSTR0_SSE357_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE357_ERROR		(1)
#define		ECM_ECMESSTR0_SSE356		(BIT4)
	#define		ECM_ECMESSTR0_SSE356_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE356_ERROR		(1)
#define		ECM_ECMESSTR0_SSE355		(BIT3)
	#define		ECM_ECMESSTR0_SSE355_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE355_ERROR		(1)
#define		ECM_ECMESSTR0_SSE354		(BIT2)
	#define		ECM_ECMESSTR0_SSE354_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE354_ERROR		(1)
#define		ECM_ECMESSTR0_SSE353		(BIT1)
	#define		ECM_ECMESSTR0_SSE353_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE353_ERROR		(1)
#define		ECM_ECMESSTR0_SSE352		(BIT0)
	#define		ECM_ECMESSTR0_SSE352_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE352_ERROR		(1)

/* ECMmESSTR12,m=M/C */
#define		ECM_ECMESSTR0_SSE415		(BIT31)
	#define		ECM_ECMESSTR0_SSE415_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE415_ERROR		(1)
#define		ECM_ECMESSTR0_SSE414		(BIT30)
	#define		ECM_ECMESSTR0_SSE414_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE414_ERROR		(1)
#define		ECM_ECMESSTR0_SSE413		(BIT29)
	#define		ECM_ECMESSTR0_SSE413_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE413_ERROR		(1)
#define		ECM_ECMESSTR0_SSE412		(BIT28)
	#define		ECM_ECMESSTR0_SSE412_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE412_ERROR		(1)
#define		ECM_ECMESSTR0_SSE411		(BIT27)
	#define		ECM_ECMESSTR0_SSE411_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE411_ERROR		(1)
#define		ECM_ECMESSTR0_SSE410		(BIT26)
	#define		ECM_ECMESSTR0_SSE410_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE410_ERROR		(1)
#define		ECM_ECMESSTR0_SSE409		(BIT25)
	#define		ECM_ECMESSTR0_SSE409_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE409_ERROR		(1)
#define		ECM_ECMESSTR0_SSE408		(BIT24)
	#define		ECM_ECMESSTR0_SSE408_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE408_ERROR		(1)
#define		ECM_ECMESSTR0_SSE407		(BIT23)
	#define		ECM_ECMESSTR0_SSE407_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE407_ERROR		(1)
#define		ECM_ECMESSTR0_SSE406		(BIT22)
	#define		ECM_ECMESSTR0_SSE406_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE406_ERROR		(1)
#define		ECM_ECMESSTR0_SSE405		(BIT21)
	#define		ECM_ECMESSTR0_SSE405_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE405_ERROR		(1)
#define		ECM_ECMESSTR0_SSE404		(BIT20)
	#define		ECM_ECMESSTR0_SSE404_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE404_ERROR		(1)
#define		ECM_ECMESSTR0_SSE403		(BIT19)
	#define		ECM_ECMESSTR0_SSE403_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE403_ERROR		(1)
#define		ECM_ECMESSTR0_SSE402		(BIT18)
	#define		ECM_ECMESSTR0_SSE402_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE402_ERROR		(1)
#define		ECM_ECMESSTR0_SSE401		(BIT17)
	#define		ECM_ECMESSTR0_SSE401_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE401_ERROR		(1)
#define		ECM_ECMESSTR0_SSE400		(BIT16)
	#define		ECM_ECMESSTR0_SSE400_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE400_ERROR		(1)
#define		ECM_ECMESSTR0_SSE399		(BIT15)
	#define		ECM_ECMESSTR0_SSE399_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE399_ERROR		(1)
#define		ECM_ECMESSTR0_SSE398		(BIT14)
	#define		ECM_ECMESSTR0_SSE398_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE398_ERROR		(1)
#define		ECM_ECMESSTR0_SSE397		(BIT13)
	#define		ECM_ECMESSTR0_SSE397_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE397_ERROR		(1)
#define		ECM_ECMESSTR0_SSE396		(BIT12)
	#define		ECM_ECMESSTR0_SSE396_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE396_ERROR		(1)
#define		ECM_ECMESSTR0_SSE395		(BIT11)
	#define		ECM_ECMESSTR0_SSE395_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE395_ERROR		(1)
#define		ECM_ECMESSTR0_SSE394		(BIT10)
	#define		ECM_ECMESSTR0_SSE394_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE394_ERROR		(1)
#define		ECM_ECMESSTR0_SSE393		(BIT9)
	#define		ECM_ECMESSTR0_SSE393_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE393_ERROR		(1)
#define		ECM_ECMESSTR0_SSE392		(BIT8)
	#define		ECM_ECMESSTR0_SSE392_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE392_ERROR		(1)
#define		ECM_ECMESSTR0_SSE391		(BIT7)
	#define		ECM_ECMESSTR0_SSE391_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE391_ERROR		(1)
#define		ECM_ECMESSTR0_SSE390		(BIT6)
	#define		ECM_ECMESSTR0_SSE390_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE390_ERROR		(1)
#define		ECM_ECMESSTR0_SSE389		(BIT5)
	#define		ECM_ECMESSTR0_SSE389_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE389_ERROR		(1)
#define		ECM_ECMESSTR0_SSE388		(BIT4)
	#define		ECM_ECMESSTR0_SSE388_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE388_ERROR		(1)
#define		ECM_ECMESSTR0_SSE387		(BIT3)
	#define		ECM_ECMESSTR0_SSE387_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE387_ERROR		(1)
#define		ECM_ECMESSTR0_SSE386		(BIT2)
	#define		ECM_ECMESSTR0_SSE386_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE386_ERROR		(1)
#define		ECM_ECMESSTR0_SSE385		(BIT1)
	#define		ECM_ECMESSTR0_SSE385_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE385_ERROR		(1)
#define		ECM_ECMESSTR0_SSE384		(BIT0)
	#define		ECM_ECMESSTR0_SSE384_NOERROR	(0)
	#define		ECM_ECMESSTR0_SSE384_ERROR		(1)

/* ECMEPCFG */
#define		ECM_EPCFG_ECMSL0		(BIT0)
	#define		ECM_EPCFG_ECMSL0_NDYNAMIC	(0)
	#define		ECM_EPCFG_ECMSL0_DYNAMIC	(1)

/* ECMISCFG0 */
#define		ECM_ECMISCFG0_IS031		(BIT31)
	#define		ECM_ECMISCFG0_IS031_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS031_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS030		(BIT30)
	#define		ECM_ECMISCFG0_IS030_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS030_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS029		(BIT29)
	#define		ECM_ECMISCFG0_IS029_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS029_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS028		(BIT28)
	#define		ECM_ECMISCFG0_IS028_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS028_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS027		(BIT27)
	#define		ECM_ECMISCFG0_IS027_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS027_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS026		(BIT26)
	#define		ECM_ECMISCFG0_IS026_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS026_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS025		(BIT25)
	#define		ECM_ECMISCFG0_IS025_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS025_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS024		(BIT24)
	#define		ECM_ECMISCFG0_IS024_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS024_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS023		(BIT23)
	#define		ECM_ECMISCFG0_IS023_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS023_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS022		(BIT22)
	#define		ECM_ECMISCFG0_IS022_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS022_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS021		(BIT21)
	#define		ECM_ECMISCFG0_IS021_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS021_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS020		(BIT20)
	#define		ECM_ECMISCFG0_IS020_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS020_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS019		(BIT19)
	#define		ECM_ECMISCFG0_IS019_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS019_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS018		(BIT18)
	#define		ECM_ECMISCFG0_IS018_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS018_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS017		(BIT17)
	#define		ECM_ECMISCFG0_IS017_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS017_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS016		(BIT16)
	#define		ECM_ECMISCFG0_IS016_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS016_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS015		(BIT15)
	#define		ECM_ECMISCFG0_IS015_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS015_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS014		(BIT14)
	#define		ECM_ECMISCFG0_IS014_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS014_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS013		(BIT13)
	#define		ECM_ECMISCFG0_IS013_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS013_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS012		(BIT12)
	#define		ECM_ECMISCFG0_IS012_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS012_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS011		(BIT11)
	#define		ECM_ECMISCFG0_IS011_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS011_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS010		(BIT10)
	#define		ECM_ECMISCFG0_IS010_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS010_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS009		(BIT9)
	#define		ECM_ECMISCFG0_IS009_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS009_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS008		(BIT8)
	#define		ECM_ECMISCFG0_IS008_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS008_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS007		(BIT7)
	#define		ECM_ECMISCFG0_IS007_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS007_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS006		(BIT6)
	#define		ECM_ECMISCFG0_IS006_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS006_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS005		(BIT5)
	#define		ECM_ECMISCFG0_IS005_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS005_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS004		(BIT4)
	#define		ECM_ECMISCFG0_IS004_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS004_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS003		(BIT3)
	#define		ECM_ECMISCFG0_IS003_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS003_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS002		(BIT2)
	#define		ECM_ECMISCFG0_IS002_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS002_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS001		(BIT1)
	#define		ECM_ECMISCFG0_IS001_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS001_FELEVEL		(1)
#define		ECM_ECMISCFG0_IS000		(BIT0)
	#define		ECM_ECMISCFG0_IS000_EILEVEL	(0)
	#define		ECM_ECMISCFG0_IS000_FELEVEL		(1)

/* ECMISCFG1 */
#define		ECM_ECMISCFG1_IS063		(BIT31)
	#define		ECM_ECMISCFG1_IS063_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS063_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS062		(BIT30)
	#define		ECM_ECMISCFG1_IS062_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS062_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS061		(BIT29)
	#define		ECM_ECMISCFG1_IS061_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS061_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS060		(BIT28)
	#define		ECM_ECMISCFG1_IS060_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS060_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS059		(BIT27)
	#define		ECM_ECMISCFG1_IS059_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS059_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS058		(BIT26)
	#define		ECM_ECMISCFG1_IS058_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS058_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS057		(BIT25)
	#define		ECM_ECMISCFG1_IS057_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS057_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS056		(BIT24)
	#define		ECM_ECMISCFG1_IS056_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS056_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS055		(BIT23)
	#define		ECM_ECMISCFG1_IS055_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS055_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS054		(BIT22)
	#define		ECM_ECMISCFG1_IS054_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS054_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS053		(BIT21)
	#define		ECM_ECMISCFG1_IS053_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS053_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS052		(BIT20)
	#define		ECM_ECMISCFG1_IS052_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS052_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS051		(BIT19)
	#define		ECM_ECMISCFG1_IS051_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS051_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS050		(BIT18)
	#define		ECM_ECMISCFG1_IS050_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS050_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS049		(BIT17)
	#define		ECM_ECMISCFG1_IS049_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS049_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS048		(BIT16)
	#define		ECM_ECMISCFG1_IS048_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS048_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS047		(BIT15)
	#define		ECM_ECMISCFG1_IS047_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS047_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS046		(BIT14)
	#define		ECM_ECMISCFG1_IS046_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS046_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS045		(BIT13)
	#define		ECM_ECMISCFG1_IS045_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS045_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS044		(BIT12)
	#define		ECM_ECMISCFG1_IS044_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS044_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS043		(BIT11)
	#define		ECM_ECMISCFG1_IS043_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS043_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS042		(BIT10)
	#define		ECM_ECMISCFG1_IS042_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS042_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS041		(BIT9)
	#define		ECM_ECMISCFG1_IS041_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS041_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS040		(BIT8)
	#define		ECM_ECMISCFG1_IS040_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS040_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS039		(BIT7)
	#define		ECM_ECMISCFG1_IS039_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS039_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS038		(BIT6)
	#define		ECM_ECMISCFG1_IS038_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS038_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS037		(BIT5)
	#define		ECM_ECMISCFG1_IS037_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS037_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS036		(BIT4)
	#define		ECM_ECMISCFG1_IS036_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS036_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS035		(BIT3)
	#define		ECM_ECMISCFG1_IS035_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS035_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS034		(BIT2)
	#define		ECM_ECMISCFG1_IS034_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS034_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS033		(BIT1)
	#define		ECM_ECMISCFG1_IS033_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS033_FELEVEL		(1)
#define		ECM_ECMISCFG1_IS032		(BIT0)
	#define		ECM_ECMISCFG1_IS032_EILEVEL	(0)
	#define		ECM_ECMISCFG1_IS032_FELEVEL		(1)

/* ECMISCFG2 */
#define		ECM_ECMISCFG2_IS095		(BIT31)
	#define		ECM_ECMISCFG2_IS095_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS095_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS094		(BIT30)
	#define		ECM_ECMISCFG2_IS094_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS094_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS093		(BIT29)
	#define		ECM_ECMISCFG2_IS093_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS093_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS092		(BIT28)
	#define		ECM_ECMISCFG2_IS092_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS092_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS091		(BIT27)
	#define		ECM_ECMISCFG2_IS091_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS091_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS090		(BIT26)
	#define		ECM_ECMISCFG2_IS090_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS090_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS089		(BIT25)
	#define		ECM_ECMISCFG2_IS089_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS089_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS088		(BIT24)
	#define		ECM_ECMISCFG2_IS088_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS088_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS087		(BIT23)
	#define		ECM_ECMISCFG2_IS087_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS087_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS086		(BIT22)
	#define		ECM_ECMISCFG2_IS086_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS086_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS085		(BIT21)
	#define		ECM_ECMISCFG2_IS085_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS085_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS084		(BIT20)
	#define		ECM_ECMISCFG2_IS084_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS084_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS083		(BIT19)
	#define		ECM_ECMISCFG2_IS083_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS083_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS082		(BIT18)
	#define		ECM_ECMISCFG2_IS082_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS082_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS081		(BIT17)
	#define		ECM_ECMISCFG2_IS081_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS081_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS080		(BIT16)
	#define		ECM_ECMISCFG2_IS080_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS080_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS079		(BIT15)
	#define		ECM_ECMISCFG2_IS079_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS079_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS078		(BIT14)
	#define		ECM_ECMISCFG2_IS078_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS078_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS077		(BIT13)
	#define		ECM_ECMISCFG2_IS077_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS077_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS076		(BIT12)
	#define		ECM_ECMISCFG2_IS076_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS076_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS075		(BIT11)
	#define		ECM_ECMISCFG2_IS075_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS075_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS074		(BIT10)
	#define		ECM_ECMISCFG2_IS074_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS074_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS073		(BIT9)
	#define		ECM_ECMISCFG2_IS073_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS073_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS072		(BIT8)
	#define		ECM_ECMISCFG2_IS072_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS072_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS071		(BIT7)
	#define		ECM_ECMISCFG2_IS071_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS071_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS070		(BIT6)
	#define		ECM_ECMISCFG2_IS070_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS070_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS069		(BIT5)
	#define		ECM_ECMISCFG2_IS069_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS069_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS068		(BIT4)
	#define		ECM_ECMISCFG2_IS068_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS068_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS067		(BIT3)
	#define		ECM_ECMISCFG2_IS067_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS067_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS066		(BIT2)
	#define		ECM_ECMISCFG2_IS066_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS066_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS065		(BIT1)
	#define		ECM_ECMISCFG2_IS065_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS065_FELEVEL		(1)
#define		ECM_ECMISCFG2_IS064		(BIT0)
	#define		ECM_ECMISCFG2_IS064_EILEVEL	(0)
	#define		ECM_ECMISCFG2_IS064_FELEVEL		(1)

/* ECMISCFG3 */
#define		ECM_ECMISCFG3_IS127		(BIT31)
	#define		ECM_ECMISCFG3_IS127_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS127_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS126		(BIT30)
	#define		ECM_ECMISCFG3_IS126_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS126_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS125		(BIT29)
	#define		ECM_ECMISCFG3_IS125_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS125_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS124		(BIT28)
	#define		ECM_ECMISCFG3_IS124_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS124_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS123		(BIT27)
	#define		ECM_ECMISCFG3_IS123_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS123_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS122		(BIT26)
	#define		ECM_ECMISCFG3_IS122_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS122_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS121		(BIT25)
	#define		ECM_ECMISCFG3_IS121_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS121_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS120		(BIT24)
	#define		ECM_ECMISCFG3_IS120_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS120_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS119		(BIT23)
	#define		ECM_ECMISCFG3_IS119_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS119_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS118		(BIT22)
	#define		ECM_ECMISCFG3_IS118_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS118_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS117		(BIT21)
	#define		ECM_ECMISCFG3_IS117_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS117_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS116		(BIT20)
	#define		ECM_ECMISCFG3_IS116_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS116_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS115		(BIT19)
	#define		ECM_ECMISCFG3_IS115_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS115_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS114		(BIT18)
	#define		ECM_ECMISCFG3_IS114_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS114_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS113		(BIT17)
	#define		ECM_ECMISCFG3_IS113_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS113_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS112		(BIT16)
	#define		ECM_ECMISCFG3_IS112_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS112_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS111		(BIT15)
	#define		ECM_ECMISCFG3_IS111_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS111_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS110		(BIT14)
	#define		ECM_ECMISCFG3_IS110_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS110_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS109		(BIT13)
	#define		ECM_ECMISCFG3_IS109_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS109_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS108		(BIT12)
	#define		ECM_ECMISCFG3_IS108_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS108_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS107		(BIT11)
	#define		ECM_ECMISCFG3_IS107_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS107_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS106		(BIT10)
	#define		ECM_ECMISCFG3_IS106_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS106_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS105		(BIT9)
	#define		ECM_ECMISCFG3_IS105_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS105_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS104		(BIT8)
	#define		ECM_ECMISCFG3_IS104_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS104_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS103		(BIT7)
	#define		ECM_ECMISCFG3_IS103_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS103_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS102		(BIT6)
	#define		ECM_ECMISCFG3_IS102_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS102_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS101		(BIT5)
	#define		ECM_ECMISCFG3_IS101_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS101_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS100		(BIT4)
	#define		ECM_ECMISCFG3_IS100_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS100_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS099		(BIT3)
	#define		ECM_ECMISCFG3_IS099_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS099_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS098		(BIT2)
	#define		ECM_ECMISCFG3_IS098_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS098_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS097		(BIT1)
	#define		ECM_ECMISCFG3_IS097_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS097_FELEVEL		(1)
#define		ECM_ECMISCFG3_IS096		(BIT0)
	#define		ECM_ECMISCFG3_IS096_EILEVEL	(0)
	#define		ECM_ECMISCFG3_IS096_FELEVEL		(1)

/* ECMISCFG4 */
#define		ECM_ECMISCFG4_IS159		(BIT31)
	#define		ECM_ECMISCFG4_IS159_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS159_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS158		(BIT30)
	#define		ECM_ECMISCFG4_IS158_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS158_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS157		(BIT29)
	#define		ECM_ECMISCFG4_IS157_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS157_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS156		(BIT28)
	#define		ECM_ECMISCFG4_IS156_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS156_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS155		(BIT27)
	#define		ECM_ECMISCFG4_IS155_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS155_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS154		(BIT26)
	#define		ECM_ECMISCFG4_IS154_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS154_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS153		(BIT25)
	#define		ECM_ECMISCFG4_IS153_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS153_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS152		(BIT24)
	#define		ECM_ECMISCFG4_IS152_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS152_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS151		(BIT23)
	#define		ECM_ECMISCFG4_IS151_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS151_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS150		(BIT22)
	#define		ECM_ECMISCFG4_IS150_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS150_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS149		(BIT21)
	#define		ECM_ECMISCFG4_IS149_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS149_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS148		(BIT20)
	#define		ECM_ECMISCFG4_IS148_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS148_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS147		(BIT19)
	#define		ECM_ECMISCFG4_IS147_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS147_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS146		(BIT18)
	#define		ECM_ECMISCFG4_IS146_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS146_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS145		(BIT17)
	#define		ECM_ECMISCFG4_IS145_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS145_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS144		(BIT16)
	#define		ECM_ECMISCFG4_IS144_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS144_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS143		(BIT15)
	#define		ECM_ECMISCFG4_IS143_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS143_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS142		(BIT14)
	#define		ECM_ECMISCFG4_IS142_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS142_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS141		(BIT13)
	#define		ECM_ECMISCFG4_IS141_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS141_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS140		(BIT12)
	#define		ECM_ECMISCFG4_IS140_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS140_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS139		(BIT11)
	#define		ECM_ECMISCFG4_IS139_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS139_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS138		(BIT10)
	#define		ECM_ECMISCFG4_IS138_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS138_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS137		(BIT9)
	#define		ECM_ECMISCFG4_IS137_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS137_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS136		(BIT8)
	#define		ECM_ECMISCFG4_IS136_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS136_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS135		(BIT7)
	#define		ECM_ECMISCFG4_IS135_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS135_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS134		(BIT6)
	#define		ECM_ECMISCFG4_IS134_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS134_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS133		(BIT5)
	#define		ECM_ECMISCFG4_IS133_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS133_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS132		(BIT4)
	#define		ECM_ECMISCFG4_IS132_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS132_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS131		(BIT3)
	#define		ECM_ECMISCFG4_IS131_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS131_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS130		(BIT2)
	#define		ECM_ECMISCFG4_IS130_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS130_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS129		(BIT1)
	#define		ECM_ECMISCFG4_IS129_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS129_FELEVEL		(1)
#define		ECM_ECMISCFG4_IS128		(BIT0)
	#define		ECM_ECMISCFG4_IS128_EILEVEL	(0)
	#define		ECM_ECMISCFG4_IS128_FELEVEL		(1)

/* ECMISCFG5 */
#define		ECM_ECMISCFG5_IS191		(BIT31)
	#define		ECM_ECMISCFG5_IS191_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS191_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS190		(BIT30)
	#define		ECM_ECMISCFG5_IS190_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS190_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS189		(BIT29)
	#define		ECM_ECMISCFG5_IS189_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS189_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS188		(BIT28)
	#define		ECM_ECMISCFG5_IS188_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS188_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS187		(BIT27)
	#define		ECM_ECMISCFG5_IS187_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS187_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS186		(BIT26)
	#define		ECM_ECMISCFG5_IS186_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS186_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS185		(BIT25)
	#define		ECM_ECMISCFG5_IS185_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS185_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS184		(BIT24)
	#define		ECM_ECMISCFG5_IS184_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS184_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS183		(BIT23)
	#define		ECM_ECMISCFG5_IS183_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS183_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS182		(BIT22)
	#define		ECM_ECMISCFG5_IS182_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS182_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS181		(BIT21)
	#define		ECM_ECMISCFG5_IS181_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS181_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS180		(BIT20)
	#define		ECM_ECMISCFG5_IS180_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS180_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS179		(BIT19)
	#define		ECM_ECMISCFG5_IS179_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS179_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS178		(BIT18)
	#define		ECM_ECMISCFG5_IS178_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS178_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS177		(BIT17)
	#define		ECM_ECMISCFG5_IS177_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS177_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS176		(BIT16)
	#define		ECM_ECMISCFG5_IS176_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS176_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS175		(BIT15)
	#define		ECM_ECMISCFG5_IS175_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS175_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS174		(BIT14)
	#define		ECM_ECMISCFG5_IS174_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS174_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS173		(BIT13)
	#define		ECM_ECMISCFG5_IS173_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS173_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS172		(BIT12)
	#define		ECM_ECMISCFG5_IS172_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS172_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS171		(BIT11)
	#define		ECM_ECMISCFG5_IS171_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS171_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS170		(BIT10)
	#define		ECM_ECMISCFG5_IS170_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS170_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS169		(BIT9)
	#define		ECM_ECMISCFG5_IS169_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS169_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS168		(BIT8)
	#define		ECM_ECMISCFG5_IS168_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS168_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS167		(BIT7)
	#define		ECM_ECMISCFG5_IS167_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS167_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS166		(BIT6)
	#define		ECM_ECMISCFG5_IS166_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS166_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS165		(BIT5)
	#define		ECM_ECMISCFG5_IS165_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS165_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS164		(BIT4)
	#define		ECM_ECMISCFG5_IS164_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS164_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS163		(BIT3)
	#define		ECM_ECMISCFG5_IS163_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS163_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS162		(BIT2)
	#define		ECM_ECMISCFG5_IS162_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS162_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS161		(BIT1)
	#define		ECM_ECMISCFG5_IS161_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS161_FELEVEL		(1)
#define		ECM_ECMISCFG5_IS160		(BIT0)
	#define		ECM_ECMISCFG5_IS160_EILEVEL	(0)
	#define		ECM_ECMISCFG5_IS160_FELEVEL		(1)

/* ECMISCFG6 */
#define		ECM_ECMISCFG6_IS223		(BIT31)
	#define		ECM_ECMISCFG6_IS223_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS223_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS222		(BIT30)
	#define		ECM_ECMISCFG6_IS222_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS222_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS221		(BIT29)
	#define		ECM_ECMISCFG6_IS221_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS221_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS220		(BIT28)
	#define		ECM_ECMISCFG6_IS220_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS220_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS219		(BIT27)
	#define		ECM_ECMISCFG6_IS219_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS219_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS218		(BIT26)
	#define		ECM_ECMISCFG6_IS218_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS218_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS217		(BIT25)
	#define		ECM_ECMISCFG6_IS217_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS217_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS216		(BIT24)
	#define		ECM_ECMISCFG6_IS216_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS216_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS215		(BIT23)
	#define		ECM_ECMISCFG6_IS215_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS215_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS214		(BIT22)
	#define		ECM_ECMISCFG6_IS214_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS214_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS213		(BIT21)
	#define		ECM_ECMISCFG6_IS213_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS213_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS212		(BIT20)
	#define		ECM_ECMISCFG6_IS212_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS212_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS211		(BIT19)
	#define		ECM_ECMISCFG6_IS211_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS211_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS210		(BIT18)
	#define		ECM_ECMISCFG6_IS210_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS210_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS209		(BIT17)
	#define		ECM_ECMISCFG6_IS209_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS209_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS208		(BIT16)
	#define		ECM_ECMISCFG6_IS208_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS208_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS207		(BIT15)
	#define		ECM_ECMISCFG6_IS207_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS207_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS206		(BIT14)
	#define		ECM_ECMISCFG6_IS206_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS206_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS205		(BIT13)
	#define		ECM_ECMISCFG6_IS205_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS205_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS204		(BIT12)
	#define		ECM_ECMISCFG6_IS204_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS204_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS203		(BIT11)
	#define		ECM_ECMISCFG6_IS203_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS203_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS202		(BIT10)
	#define		ECM_ECMISCFG6_IS202_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS202_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS201		(BIT9)
	#define		ECM_ECMISCFG6_IS201_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS201_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS200		(BIT8)
	#define		ECM_ECMISCFG6_IS200_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS200_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS199		(BIT7)
	#define		ECM_ECMISCFG6_IS199_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS199_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS198		(BIT6)
	#define		ECM_ECMISCFG6_IS198_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS198_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS197		(BIT5)
	#define		ECM_ECMISCFG6_IS197_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS197_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS196		(BIT4)
	#define		ECM_ECMISCFG6_IS196_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS196_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS195		(BIT3)
	#define		ECM_ECMISCFG6_IS195_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS195_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS194		(BIT2)
	#define		ECM_ECMISCFG6_IS194_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS194_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS193		(BIT1)
	#define		ECM_ECMISCFG6_IS193_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS193_FELEVEL		(1)
#define		ECM_ECMISCFG6_IS192		(BIT0)
	#define		ECM_ECMISCFG6_IS192_EILEVEL	(0)
	#define		ECM_ECMISCFG6_IS192_FELEVEL		(1)

/* ECMISCFG7 */
#define		ECM_ECMISCFG7_IS255		(BIT31)
	#define		ECM_ECMISCFG7_IS255_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS255_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS254		(BIT30)
	#define		ECM_ECMISCFG7_IS254_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS254_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS253		(BIT29)
	#define		ECM_ECMISCFG7_IS253_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS253_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS252		(BIT28)
	#define		ECM_ECMISCFG7_IS252_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS252_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS251		(BIT27)
	#define		ECM_ECMISCFG7_IS251_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS251_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS250		(BIT26)
	#define		ECM_ECMISCFG7_IS250_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS250_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS249		(BIT25)
	#define		ECM_ECMISCFG7_IS249_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS249_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS248		(BIT24)
	#define		ECM_ECMISCFG7_IS248_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS248_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS247		(BIT23)
	#define		ECM_ECMISCFG7_IS247_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS247_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS246		(BIT22)
	#define		ECM_ECMISCFG7_IS246_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS246_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS245		(BIT21)
	#define		ECM_ECMISCFG7_IS245_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS245_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS244		(BIT20)
	#define		ECM_ECMISCFG7_IS244_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS244_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS243		(BIT19)
	#define		ECM_ECMISCFG7_IS243_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS243_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS242		(BIT18)
	#define		ECM_ECMISCFG7_IS242_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS242_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS241		(BIT17)
	#define		ECM_ECMISCFG7_IS241_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS241_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS240		(BIT16)
	#define		ECM_ECMISCFG7_IS240_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS240_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS239		(BIT15)
	#define		ECM_ECMISCFG7_IS239_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS239_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS238		(BIT14)
	#define		ECM_ECMISCFG7_IS238_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS238_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS237		(BIT13)
	#define		ECM_ECMISCFG7_IS237_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS237_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS236		(BIT12)
	#define		ECM_ECMISCFG7_IS236_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS236_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS235		(BIT11)
	#define		ECM_ECMISCFG7_IS235_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS235_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS234		(BIT10)
	#define		ECM_ECMISCFG7_IS234_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS234_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS233		(BIT9)
	#define		ECM_ECMISCFG7_IS233_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS233_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS232		(BIT8)
	#define		ECM_ECMISCFG7_IS232_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS232_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS231		(BIT7)
	#define		ECM_ECMISCFG7_IS231_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS231_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS230		(BIT6)
	#define		ECM_ECMISCFG7_IS230_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS230_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS229		(BIT5)
	#define		ECM_ECMISCFG7_IS229_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS229_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS228		(BIT4)
	#define		ECM_ECMISCFG7_IS228_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS228_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS227		(BIT3)
	#define		ECM_ECMISCFG7_IS227_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS227_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS226		(BIT2)
	#define		ECM_ECMISCFG7_IS226_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS226_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS225		(BIT1)
	#define		ECM_ECMISCFG7_IS225_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS225_FELEVEL		(1)
#define		ECM_ECMISCFG7_IS224		(BIT0)
	#define		ECM_ECMISCFG7_IS224_EILEVEL	(0)
	#define		ECM_ECMISCFG7_IS224_FELEVEL		(1)

/* ECMISCFG8 */
#define		ECM_ECMISCFG8_IS287		(BIT31)
	#define		ECM_ECMISCFG8_IS287_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS287_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS286		(BIT30)
	#define		ECM_ECMISCFG8_IS286_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS286_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS285		(BIT29)
	#define		ECM_ECMISCFG8_IS285_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS285_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS284		(BIT28)
	#define		ECM_ECMISCFG8_IS284_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS284_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS283		(BIT27)
	#define		ECM_ECMISCFG8_IS283_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS283_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS282		(BIT26)
	#define		ECM_ECMISCFG8_IS282_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS282_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS281		(BIT25)
	#define		ECM_ECMISCFG8_IS281_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS281_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS280		(BIT24)
	#define		ECM_ECMISCFG8_IS280_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS280_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS279		(BIT23)
	#define		ECM_ECMISCFG8_IS279_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS279_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS278		(BIT22)
	#define		ECM_ECMISCFG8_IS278_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS278_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS277		(BIT21)
	#define		ECM_ECMISCFG8_IS277_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS277_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS276		(BIT20)
	#define		ECM_ECMISCFG8_IS276_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS276_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS275		(BIT19)
	#define		ECM_ECMISCFG8_IS275_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS275_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS274		(BIT18)
	#define		ECM_ECMISCFG8_IS274_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS274_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS273		(BIT17)
	#define		ECM_ECMISCFG8_IS273_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS273_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS272		(BIT16)
	#define		ECM_ECMISCFG8_IS272_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS272_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS271		(BIT15)
	#define		ECM_ECMISCFG8_IS271_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS271_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS270		(BIT14)
	#define		ECM_ECMISCFG8_IS270_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS270_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS269		(BIT13)
	#define		ECM_ECMISCFG8_IS269_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS269_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS268		(BIT12)
	#define		ECM_ECMISCFG8_IS268_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS268_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS267		(BIT11)
	#define		ECM_ECMISCFG8_IS267_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS267_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS266		(BIT10)
	#define		ECM_ECMISCFG8_IS266_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS266_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS265		(BIT9)
	#define		ECM_ECMISCFG8_IS265_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS265_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS264		(BIT8)
	#define		ECM_ECMISCFG8_IS264_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS264_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS263		(BIT7)
	#define		ECM_ECMISCFG8_IS263_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS263_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS262		(BIT6)
	#define		ECM_ECMISCFG8_IS262_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS262_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS261		(BIT5)
	#define		ECM_ECMISCFG8_IS261_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS261_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS260		(BIT4)
	#define		ECM_ECMISCFG8_IS260_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS260_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS259		(BIT3)
	#define		ECM_ECMISCFG8_IS259_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS259_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS258		(BIT2)
	#define		ECM_ECMISCFG8_IS258_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS258_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS257		(BIT1)
	#define		ECM_ECMISCFG8_IS257_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS257_FELEVEL		(1)
#define		ECM_ECMISCFG8_IS256		(BIT0)
	#define		ECM_ECMISCFG8_IS256_EILEVEL	(0)
	#define		ECM_ECMISCFG8_IS256_FELEVEL		(1)

/* ECMISCFG9 */
#define		ECM_ECMISCFG9_IS319		(BIT31)
	#define		ECM_ECMISCFG9_IS319_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS319_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS318		(BIT30)
	#define		ECM_ECMISCFG9_IS318_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS318_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS317		(BIT29)
	#define		ECM_ECMISCFG9_IS317_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS317_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS316		(BIT28)
	#define		ECM_ECMISCFG9_IS316_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS316_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS315		(BIT27)
	#define		ECM_ECMISCFG9_IS315_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS315_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS314		(BIT26)
	#define		ECM_ECMISCFG9_IS314_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS314_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS313		(BIT25)
	#define		ECM_ECMISCFG9_IS313_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS313_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS312		(BIT24)
	#define		ECM_ECMISCFG9_IS312_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS312_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS311		(BIT23)
	#define		ECM_ECMISCFG9_IS311_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS311_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS310		(BIT22)
	#define		ECM_ECMISCFG9_IS310_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS310_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS309		(BIT21)
	#define		ECM_ECMISCFG9_IS309_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS309_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS308		(BIT20)
	#define		ECM_ECMISCFG9_IS308_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS308_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS307		(BIT19)
	#define		ECM_ECMISCFG9_IS307_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS307_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS306		(BIT18)
	#define		ECM_ECMISCFG9_IS306_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS306_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS305		(BIT17)
	#define		ECM_ECMISCFG9_IS305_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS305_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS304		(BIT16)
	#define		ECM_ECMISCFG9_IS304_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS304_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS303		(BIT15)
	#define		ECM_ECMISCFG9_IS303_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS303_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS302		(BIT14)
	#define		ECM_ECMISCFG9_IS302_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS302_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS301		(BIT13)
	#define		ECM_ECMISCFG9_IS301_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS301_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS300		(BIT12)
	#define		ECM_ECMISCFG9_IS300_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS300_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS299		(BIT11)
	#define		ECM_ECMISCFG9_IS299_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS299_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS298		(BIT10)
	#define		ECM_ECMISCFG9_IS298_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS298_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS297		(BIT9)
	#define		ECM_ECMISCFG9_IS297_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS297_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS296		(BIT8)
	#define		ECM_ECMISCFG9_IS296_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS296_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS295		(BIT7)
	#define		ECM_ECMISCFG9_IS295_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS295_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS294		(BIT6)
	#define		ECM_ECMISCFG9_IS294_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS294_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS293		(BIT5)
	#define		ECM_ECMISCFG9_IS293_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS293_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS292		(BIT4)
	#define		ECM_ECMISCFG9_IS292_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS292_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS291		(BIT3)
	#define		ECM_ECMISCFG9_IS291_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS291_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS290		(BIT2)
	#define		ECM_ECMISCFG9_IS290_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS290_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS289		(BIT1)
	#define		ECM_ECMISCFG9_IS289_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS289_FELEVEL		(1)
#define		ECM_ECMISCFG9_IS288		(BIT0)
	#define		ECM_ECMISCFG9_IS288_EILEVEL	(0)
	#define		ECM_ECMISCFG9_IS288_FELEVEL		(1)

/* ECMISCFG10 */
#define		ECM_ECMISCFG10_IS351		(BIT31)
	#define		ECM_ECMISCFG10_IS351_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS351_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS350		(BIT30)
	#define		ECM_ECMISCFG10_IS350_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS350_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS349		(BIT29)
	#define		ECM_ECMISCFG10_IS349_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS349_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS348		(BIT28)
	#define		ECM_ECMISCFG10_IS348_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS348_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS347		(BIT27)
	#define		ECM_ECMISCFG10_IS347_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS347_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS346		(BIT26)
	#define		ECM_ECMISCFG10_IS346_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS346_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS345		(BIT25)
	#define		ECM_ECMISCFG10_IS345_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS345_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS344		(BIT24)
	#define		ECM_ECMISCFG10_IS344_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS344_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS343		(BIT23)
	#define		ECM_ECMISCFG10_IS343_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS343_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS342		(BIT22)
	#define		ECM_ECMISCFG10_IS342_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS342_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS341		(BIT21)
	#define		ECM_ECMISCFG10_IS341_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS341_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS340		(BIT20)
	#define		ECM_ECMISCFG10_IS340_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS340_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS339		(BIT19)
	#define		ECM_ECMISCFG10_IS339_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS339_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS338		(BIT18)
	#define		ECM_ECMISCFG10_IS338_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS338_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS337		(BIT17)
	#define		ECM_ECMISCFG10_IS337_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS337_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS336		(BIT16)
	#define		ECM_ECMISCFG10_IS336_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS336_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS335		(BIT15)
	#define		ECM_ECMISCFG10_IS335_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS335_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS334		(BIT14)
	#define		ECM_ECMISCFG10_IS334_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS334_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS333		(BIT13)
	#define		ECM_ECMISCFG10_IS333_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS333_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS332		(BIT12)
	#define		ECM_ECMISCFG10_IS332_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS332_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS331		(BIT11)
	#define		ECM_ECMISCFG10_IS331_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS331_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS330		(BIT10)
	#define		ECM_ECMISCFG10_IS330_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS330_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS329		(BIT9)
	#define		ECM_ECMISCFG10_IS329_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS329_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS328		(BIT8)
	#define		ECM_ECMISCFG10_IS328_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS328_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS327		(BIT7)
	#define		ECM_ECMISCFG10_IS327_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS327_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS326		(BIT6)
	#define		ECM_ECMISCFG10_IS326_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS326_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS325		(BIT5)
	#define		ECM_ECMISCFG10_IS325_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS325_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS324		(BIT4)
	#define		ECM_ECMISCFG10_IS324_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS324_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS323		(BIT3)
	#define		ECM_ECMISCFG10_IS323_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS323_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS322		(BIT2)
	#define		ECM_ECMISCFG10_IS322_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS322_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS321		(BIT1)
	#define		ECM_ECMISCFG10_IS321_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS321_FELEVEL		(1)
#define		ECM_ECMISCFG10_IS320		(BIT0)
	#define		ECM_ECMISCFG10_IS320_EILEVEL	(0)
	#define		ECM_ECMISCFG10_IS320_FELEVEL		(1)

/* ECMINCFG0_0 */
#define		ECM_ECMINCFG0_0_IE0_031		(BIT31)
	#define		ECM_ECMINCFG0_0_IE0_031_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_031_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_030		(BIT30)
	#define		ECM_ECMINCFG0_0_IE0_030_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_030_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_029		(BIT29)
	#define		ECM_ECMINCFG0_0_IE0_029_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_029_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_028		(BIT28)
	#define		ECM_ECMINCFG0_0_IE0_028_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_028_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_027		(BIT27)
	#define		ECM_ECMINCFG0_0_IE0_027_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_027_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_026		(BIT26)
	#define		ECM_ECMINCFG0_0_IE0_026_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_026_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_025		(BIT25)
	#define		ECM_ECMINCFG0_0_IE0_025_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_025_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_024		(BIT24)
	#define		ECM_ECMINCFG0_0_IE0_024_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_024_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_023		(BIT23)
	#define		ECM_ECMINCFG0_0_IE0_023_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_023_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_022		(BIT22)
	#define		ECM_ECMINCFG0_0_IE0_022_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_022_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_021		(BIT21)
	#define		ECM_ECMINCFG0_0_IE0_021_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_021_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_020		(BIT20)
	#define		ECM_ECMINCFG0_0_IE0_020_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_020_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_019		(BIT19)
	#define		ECM_ECMINCFG0_0_IE0_019_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_019_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_018		(BIT18)
	#define		ECM_ECMINCFG0_0_IE0_018_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_018_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_017		(BIT17)
	#define		ECM_ECMINCFG0_0_IE0_017_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_017_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_016		(BIT16)
	#define		ECM_ECMINCFG0_0_IE0_016_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_016_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_015		(BIT15)
	#define		ECM_ECMINCFG0_0_IE0_015_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_015_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_014		(BIT14)
	#define		ECM_ECMINCFG0_0_IE0_014_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_014_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_013		(BIT13)
	#define		ECM_ECMINCFG0_0_IE0_013_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_013_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_012		(BIT12)
	#define		ECM_ECMINCFG0_0_IE0_012_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_012_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_011		(BIT11)
	#define		ECM_ECMINCFG0_0_IE0_011_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_011_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_010		(BIT10)
	#define		ECM_ECMINCFG0_0_IE0_010_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_010_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_009		(BIT9)
	#define		ECM_ECMINCFG0_0_IE0_009_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_009_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_008		(BIT8)
	#define		ECM_ECMINCFG0_0_IE0_008_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_008_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_007		(BIT7)
	#define		ECM_ECMINCFG0_0_IE0_007_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_007_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_006		(BIT6)
	#define		ECM_ECMINCFG0_0_IE0_006_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_006_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_005		(BIT5)
	#define		ECM_ECMINCFG0_0_IE0_005_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_005_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_004		(BIT4)
	#define		ECM_ECMINCFG0_0_IE0_004_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_004_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_003		(BIT3)
	#define		ECM_ECMINCFG0_0_IE0_003_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_003_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_002		(BIT2)
	#define		ECM_ECMINCFG0_0_IE0_002_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_002_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_001		(BIT1)
	#define		ECM_ECMINCFG0_0_IE0_001_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_001_ENABLE		(1)
#define		ECM_ECMINCFG0_0_IE0_000		(BIT0)
	#define		ECM_ECMINCFG0_0_IE0_000_DISABLE	(0)
	#define		ECM_ECMINCFG0_0_IE0_000_ENABLE		(1)

/* ECMINCFG0_1 */
#define		ECM_ECMINCFG0_1_IE0_063		(BIT31)
	#define		ECM_ECMINCFG0_1_IE0_063_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_063_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_062		(BIT30)
	#define		ECM_ECMINCFG0_1_IE0_062_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_062_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_061		(BIT29)
	#define		ECM_ECMINCFG0_1_IE0_061_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_061_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_060		(BIT28)
	#define		ECM_ECMINCFG0_1_IE0_060_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_060_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_059		(BIT27)
	#define		ECM_ECMINCFG0_1_IE0_059_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_059_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_058		(BIT26)
	#define		ECM_ECMINCFG0_1_IE0_058_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_058_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_057		(BIT25)
	#define		ECM_ECMINCFG0_1_IE0_057_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_057_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_056		(BIT24)
	#define		ECM_ECMINCFG0_1_IE0_056_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_056_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_055		(BIT23)
	#define		ECM_ECMINCFG0_1_IE0_055_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_055_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_054		(BIT22)
	#define		ECM_ECMINCFG0_1_IE0_054_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_054_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_053		(BIT21)
	#define		ECM_ECMINCFG0_1_IE0_053_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_053_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_052		(BIT20)
	#define		ECM_ECMINCFG0_1_IE0_052_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_052_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_051		(BIT19)
	#define		ECM_ECMINCFG0_1_IE0_051_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_051_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_050		(BIT18)
	#define		ECM_ECMINCFG0_1_IE0_050_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_050_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_049		(BIT17)
	#define		ECM_ECMINCFG0_1_IE0_049_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_049_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_048		(BIT16)
	#define		ECM_ECMINCFG0_1_IE0_048_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_048_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_047		(BIT15)
	#define		ECM_ECMINCFG0_1_IE0_047_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_047_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_046		(BIT14)
	#define		ECM_ECMINCFG0_1_IE0_046_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_046_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_045		(BIT13)
	#define		ECM_ECMINCFG0_1_IE0_045_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_045_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_044		(BIT12)
	#define		ECM_ECMINCFG0_1_IE0_044_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_044_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_043		(BIT11)
	#define		ECM_ECMINCFG0_1_IE0_043_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_043_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_042		(BIT10)
	#define		ECM_ECMINCFG0_1_IE0_042_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_042_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_041		(BIT9)
	#define		ECM_ECMINCFG0_1_IE0_041_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_041_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_040		(BIT8)
	#define		ECM_ECMINCFG0_1_IE0_040_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_040_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_039		(BIT7)
	#define		ECM_ECMINCFG0_1_IE0_039_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_039_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_038		(BIT6)
	#define		ECM_ECMINCFG0_1_IE0_038_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_038_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_037		(BIT5)
	#define		ECM_ECMINCFG0_1_IE0_037_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_037_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_036		(BIT4)
	#define		ECM_ECMINCFG0_1_IE0_036_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_036_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_035		(BIT3)
	#define		ECM_ECMINCFG0_1_IE0_035_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_035_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_034		(BIT2)
	#define		ECM_ECMINCFG0_1_IE0_034_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_034_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_033		(BIT1)
	#define		ECM_ECMINCFG0_1_IE0_033_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_033_ENABLE		(1)
#define		ECM_ECMINCFG0_1_IE0_032		(BIT0)
	#define		ECM_ECMINCFG0_1_IE0_032_DISABLE	(0)
	#define		ECM_ECMINCFG0_1_IE0_032_ENABLE		(1)

/* ECMINCFG0_2 */
#define		ECM_ECMINCFG0_2_IE0_095		(BIT31)
	#define		ECM_ECMINCFG0_2_IE0_095_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_095_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_094		(BIT30)
	#define		ECM_ECMINCFG0_2_IE0_094_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_094_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_093		(BIT29)
	#define		ECM_ECMINCFG0_2_IE0_093_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_093_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_092		(BIT28)
	#define		ECM_ECMINCFG0_2_IE0_092_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_092_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_091		(BIT27)
	#define		ECM_ECMINCFG0_2_IE0_091_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_091_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_090		(BIT26)
	#define		ECM_ECMINCFG0_2_IE0_090_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_090_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_089		(BIT25)
	#define		ECM_ECMINCFG0_2_IE0_089_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_089_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_088		(BIT24)
	#define		ECM_ECMINCFG0_2_IE0_088_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_088_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_087		(BIT23)
	#define		ECM_ECMINCFG0_2_IE0_087_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_087_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_086		(BIT22)
	#define		ECM_ECMINCFG0_2_IE0_086_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_086_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_085		(BIT21)
	#define		ECM_ECMINCFG0_2_IE0_085_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_085_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_084		(BIT20)
	#define		ECM_ECMINCFG0_2_IE0_084_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_084_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_083		(BIT19)
	#define		ECM_ECMINCFG0_2_IE0_083_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_083_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_082		(BIT18)
	#define		ECM_ECMINCFG0_2_IE0_082_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_082_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_081		(BIT17)
	#define		ECM_ECMINCFG0_2_IE0_081_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_081_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_080		(BIT16)
	#define		ECM_ECMINCFG0_2_IE0_080_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_080_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_079		(BIT15)
	#define		ECM_ECMINCFG0_2_IE0_079_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_079_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_078		(BIT14)
	#define		ECM_ECMINCFG0_2_IE0_078_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_078_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_077		(BIT13)
	#define		ECM_ECMINCFG0_2_IE0_077_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_077_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_076		(BIT12)
	#define		ECM_ECMINCFG0_2_IE0_076_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_076_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_075		(BIT11)
	#define		ECM_ECMINCFG0_2_IE0_075_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_075_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_074		(BIT10)
	#define		ECM_ECMINCFG0_2_IE0_074_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_074_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_073		(BIT9)
	#define		ECM_ECMINCFG0_2_IE0_073_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_073_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_072		(BIT8)
	#define		ECM_ECMINCFG0_2_IE0_072_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_072_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_071		(BIT7)
	#define		ECM_ECMINCFG0_2_IE0_071_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_071_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_070		(BIT6)
	#define		ECM_ECMINCFG0_2_IE0_070_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_070_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_069		(BIT5)
	#define		ECM_ECMINCFG0_2_IE0_069_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_069_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_068		(BIT4)
	#define		ECM_ECMINCFG0_2_IE0_068_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_068_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_067		(BIT3)
	#define		ECM_ECMINCFG0_2_IE0_067_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_067_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_066		(BIT2)
	#define		ECM_ECMINCFG0_2_IE0_066_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_066_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_065		(BIT1)
	#define		ECM_ECMINCFG0_2_IE0_065_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_065_ENABLE		(1)
#define		ECM_ECMINCFG0_2_IE0_064		(BIT0)
	#define		ECM_ECMINCFG0_2_IE0_064_DISABLE	(0)
	#define		ECM_ECMINCFG0_2_IE0_064_ENABLE		(1)

/* ECMINCFG0_3 */
#define		ECM_ECMINCFG0_3_IE0_127		(BIT31)
	#define		ECM_ECMINCFG0_3_IE0_127_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_127_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_126		(BIT30)
	#define		ECM_ECMINCFG0_3_IE0_126_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_126_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_125		(BIT29)
	#define		ECM_ECMINCFG0_3_IE0_125_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_125_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_124		(BIT28)
	#define		ECM_ECMINCFG0_3_IE0_124_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_124_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_123		(BIT27)
	#define		ECM_ECMINCFG0_3_IE0_123_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_123_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_122		(BIT26)
	#define		ECM_ECMINCFG0_3_IE0_122_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_122_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_121		(BIT25)
	#define		ECM_ECMINCFG0_3_IE0_121_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_121_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_120		(BIT24)
	#define		ECM_ECMINCFG0_3_IE0_120_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_120_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_119		(BIT23)
	#define		ECM_ECMINCFG0_3_IE0_119_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_119_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_118		(BIT22)
	#define		ECM_ECMINCFG0_3_IE0_118_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_118_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_117		(BIT21)
	#define		ECM_ECMINCFG0_3_IE0_117_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_117_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_116		(BIT20)
	#define		ECM_ECMINCFG0_3_IE0_116_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_116_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_115		(BIT19)
	#define		ECM_ECMINCFG0_3_IE0_115_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_115_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_114		(BIT18)
	#define		ECM_ECMINCFG0_3_IE0_114_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_114_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_113		(BIT17)
	#define		ECM_ECMINCFG0_3_IE0_113_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_113_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_112		(BIT16)
	#define		ECM_ECMINCFG0_3_IE0_112_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_112_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_111		(BIT15)
	#define		ECM_ECMINCFG0_3_IE0_111_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_111_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_110		(BIT14)
	#define		ECM_ECMINCFG0_3_IE0_110_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_110_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_109		(BIT13)
	#define		ECM_ECMINCFG0_3_IE0_109_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_109_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_108		(BIT12)
	#define		ECM_ECMINCFG0_3_IE0_108_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_108_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_107		(BIT11)
	#define		ECM_ECMINCFG0_3_IE0_107_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_107_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_106		(BIT10)
	#define		ECM_ECMINCFG0_3_IE0_106_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_106_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_105		(BIT9)
	#define		ECM_ECMINCFG0_3_IE0_105_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_105_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_104		(BIT8)
	#define		ECM_ECMINCFG0_3_IE0_104_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_104_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_103		(BIT7)
	#define		ECM_ECMINCFG0_3_IE0_103_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_103_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_102		(BIT6)
	#define		ECM_ECMINCFG0_3_IE0_102_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_102_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_101		(BIT5)
	#define		ECM_ECMINCFG0_3_IE0_101_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_101_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_100		(BIT4)
	#define		ECM_ECMINCFG0_3_IE0_100_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_100_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_099		(BIT3)
	#define		ECM_ECMINCFG0_3_IE0_099_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_099_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_098		(BIT2)
	#define		ECM_ECMINCFG0_3_IE0_098_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_098_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_097		(BIT1)
	#define		ECM_ECMINCFG0_3_IE0_097_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_097_ENABLE		(1)
#define		ECM_ECMINCFG0_3_IE0_096		(BIT0)
	#define		ECM_ECMINCFG0_3_IE0_096_DISABLE	(0)
	#define		ECM_ECMINCFG0_3_IE0_096_ENABLE		(1)

/* ECMINCFG0_4 */
#define		ECM_ECMINCFG0_4_IE0_159		(BIT31)
	#define		ECM_ECMINCFG0_4_IE0_159_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_159_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_158		(BIT30)
	#define		ECM_ECMINCFG0_4_IE0_158_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_158_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_157		(BIT29)
	#define		ECM_ECMINCFG0_4_IE0_157_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_157_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_156		(BIT28)
	#define		ECM_ECMINCFG0_4_IE0_156_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_156_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_155		(BIT27)
	#define		ECM_ECMINCFG0_4_IE0_155_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_155_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_154		(BIT26)
	#define		ECM_ECMINCFG0_4_IE0_154_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_154_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_153		(BIT25)
	#define		ECM_ECMINCFG0_4_IE0_153_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_153_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_152		(BIT24)
	#define		ECM_ECMINCFG0_4_IE0_152_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_152_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_151		(BIT23)
	#define		ECM_ECMINCFG0_4_IE0_151_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_151_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_150		(BIT22)
	#define		ECM_ECMINCFG0_4_IE0_150_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_150_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_149		(BIT21)
	#define		ECM_ECMINCFG0_4_IE0_149_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_149_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_148		(BIT20)
	#define		ECM_ECMINCFG0_4_IE0_148_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_148_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_147		(BIT19)
	#define		ECM_ECMINCFG0_4_IE0_147_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_147_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_146		(BIT18)
	#define		ECM_ECMINCFG0_4_IE0_146_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_146_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_145		(BIT17)
	#define		ECM_ECMINCFG0_4_IE0_145_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_145_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_144		(BIT16)
	#define		ECM_ECMINCFG0_4_IE0_144_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_144_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_143		(BIT15)
	#define		ECM_ECMINCFG0_4_IE0_143_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_143_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_142		(BIT14)
	#define		ECM_ECMINCFG0_4_IE0_142_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_142_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_141		(BIT13)
	#define		ECM_ECMINCFG0_4_IE0_141_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_141_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_140		(BIT12)
	#define		ECM_ECMINCFG0_4_IE0_140_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_140_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_139		(BIT11)
	#define		ECM_ECMINCFG0_4_IE0_139_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_139_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_138		(BIT10)
	#define		ECM_ECMINCFG0_4_IE0_138_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_138_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_137		(BIT9)
	#define		ECM_ECMINCFG0_4_IE0_137_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_137_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_136		(BIT8)
	#define		ECM_ECMINCFG0_4_IE0_136_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_136_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_135		(BIT7)
	#define		ECM_ECMINCFG0_4_IE0_135_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_135_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_134		(BIT6)
	#define		ECM_ECMINCFG0_4_IE0_134_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_134_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_133		(BIT5)
	#define		ECM_ECMINCFG0_4_IE0_133_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_133_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_132		(BIT4)
	#define		ECM_ECMINCFG0_4_IE0_132_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_132_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_131		(BIT3)
	#define		ECM_ECMINCFG0_4_IE0_131_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_131_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_130		(BIT2)
	#define		ECM_ECMINCFG0_4_IE0_130_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_130_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_129		(BIT1)
	#define		ECM_ECMINCFG0_4_IE0_129_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_129_ENABLE		(1)
#define		ECM_ECMINCFG0_4_IE0_128		(BIT0)
	#define		ECM_ECMINCFG0_4_IE0_128_DISABLE	(0)
	#define		ECM_ECMINCFG0_4_IE0_128_ENABLE		(1)

/* ECMINCFG0_5 */
#define		ECM_ECMINCFG0_5_IE0_191		(BIT31)
	#define		ECM_ECMINCFG0_5_IE0_191_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_191_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_190		(BIT30)
	#define		ECM_ECMINCFG0_5_IE0_190_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_190_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_189		(BIT29)
	#define		ECM_ECMINCFG0_5_IE0_189_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_189_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_188		(BIT28)
	#define		ECM_ECMINCFG0_5_IE0_188_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_188_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_187		(BIT27)
	#define		ECM_ECMINCFG0_5_IE0_187_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_187_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_186		(BIT26)
	#define		ECM_ECMINCFG0_5_IE0_186_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_186_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_185		(BIT25)
	#define		ECM_ECMINCFG0_5_IE0_185_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_185_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_184		(BIT24)
	#define		ECM_ECMINCFG0_5_IE0_184_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_184_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_183		(BIT23)
	#define		ECM_ECMINCFG0_5_IE0_183_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_183_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_182		(BIT22)
	#define		ECM_ECMINCFG0_5_IE0_182_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_182_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_181		(BIT21)
	#define		ECM_ECMINCFG0_5_IE0_181_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_181_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_180		(BIT20)
	#define		ECM_ECMINCFG0_5_IE0_180_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_180_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_179		(BIT19)
	#define		ECM_ECMINCFG0_5_IE0_179_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_179_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_178		(BIT18)
	#define		ECM_ECMINCFG0_5_IE0_178_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_178_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_177		(BIT17)
	#define		ECM_ECMINCFG0_5_IE0_177_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_177_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_176		(BIT16)
	#define		ECM_ECMINCFG0_5_IE0_176_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_176_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_175		(BIT15)
	#define		ECM_ECMINCFG0_5_IE0_175_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_175_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_174		(BIT14)
	#define		ECM_ECMINCFG0_5_IE0_174_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_174_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_173		(BIT13)
	#define		ECM_ECMINCFG0_5_IE0_173_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_173_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_172		(BIT12)
	#define		ECM_ECMINCFG0_5_IE0_172_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_172_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_171		(BIT11)
	#define		ECM_ECMINCFG0_5_IE0_171_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_171_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_170		(BIT10)
	#define		ECM_ECMINCFG0_5_IE0_170_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_170_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_169		(BIT9)
	#define		ECM_ECMINCFG0_5_IE0_169_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_169_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_168		(BIT8)
	#define		ECM_ECMINCFG0_5_IE0_168_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_168_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_167		(BIT7)
	#define		ECM_ECMINCFG0_5_IE0_167_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_167_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_166		(BIT6)
	#define		ECM_ECMINCFG0_5_IE0_166_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_166_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_165		(BIT5)
	#define		ECM_ECMINCFG0_5_IE0_165_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_165_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_164		(BIT4)
	#define		ECM_ECMINCFG0_5_IE0_164_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_164_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_163		(BIT3)
	#define		ECM_ECMINCFG0_5_IE0_163_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_163_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_162		(BIT2)
	#define		ECM_ECMINCFG0_5_IE0_162_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_162_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_161		(BIT1)
	#define		ECM_ECMINCFG0_5_IE0_161_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_161_ENABLE		(1)
#define		ECM_ECMINCFG0_5_IE0_160		(BIT0)
	#define		ECM_ECMINCFG0_5_IE0_160_DISABLE	(0)
	#define		ECM_ECMINCFG0_5_IE0_160_ENABLE		(1)

/* ECMINCFG0_6 */
#define		ECM_ECMINCFG0_6_IE0_223		(BIT31)
	#define		ECM_ECMINCFG0_6_IE0_223_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_223_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_222		(BIT30)
	#define		ECM_ECMINCFG0_6_IE0_222_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_222_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_221		(BIT29)
	#define		ECM_ECMINCFG0_6_IE0_221_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_221_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_220		(BIT28)
	#define		ECM_ECMINCFG0_6_IE0_220_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_220_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_219		(BIT27)
	#define		ECM_ECMINCFG0_6_IE0_219_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_219_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_218		(BIT26)
	#define		ECM_ECMINCFG0_6_IE0_218_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_218_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_217		(BIT25)
	#define		ECM_ECMINCFG0_6_IE0_217_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_217_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_216		(BIT24)
	#define		ECM_ECMINCFG0_6_IE0_216_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_216_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_215		(BIT23)
	#define		ECM_ECMINCFG0_6_IE0_215_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_215_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_214		(BIT22)
	#define		ECM_ECMINCFG0_6_IE0_214_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_214_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_213		(BIT21)
	#define		ECM_ECMINCFG0_6_IE0_213_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_213_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_212		(BIT20)
	#define		ECM_ECMINCFG0_6_IE0_212_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_212_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_211		(BIT19)
	#define		ECM_ECMINCFG0_6_IE0_211_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_211_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_210		(BIT18)
	#define		ECM_ECMINCFG0_6_IE0_210_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_210_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_209		(BIT17)
	#define		ECM_ECMINCFG0_6_IE0_209_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_209_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_208		(BIT16)
	#define		ECM_ECMINCFG0_6_IE0_208_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_208_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_207		(BIT15)
	#define		ECM_ECMINCFG0_6_IE0_207_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_207_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_206		(BIT14)
	#define		ECM_ECMINCFG0_6_IE0_206_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_206_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_205		(BIT13)
	#define		ECM_ECMINCFG0_6_IE0_205_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_205_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_204		(BIT12)
	#define		ECM_ECMINCFG0_6_IE0_204_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_204_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_203		(BIT11)
	#define		ECM_ECMINCFG0_6_IE0_203_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_203_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_202		(BIT10)
	#define		ECM_ECMINCFG0_6_IE0_202_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_202_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_201		(BIT9)
	#define		ECM_ECMINCFG0_6_IE0_201_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_201_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_200		(BIT8)
	#define		ECM_ECMINCFG0_6_IE0_200_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_200_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_199		(BIT7)
	#define		ECM_ECMINCFG0_6_IE0_199_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_199_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_198		(BIT6)
	#define		ECM_ECMINCFG0_6_IE0_198_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_198_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_197		(BIT5)
	#define		ECM_ECMINCFG0_6_IE0_197_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_197_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_196		(BIT4)
	#define		ECM_ECMINCFG0_6_IE0_196_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_196_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_195		(BIT3)
	#define		ECM_ECMINCFG0_6_IE0_195_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_195_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_194		(BIT2)
	#define		ECM_ECMINCFG0_6_IE0_194_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_194_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_193		(BIT1)
	#define		ECM_ECMINCFG0_6_IE0_193_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_193_ENABLE		(1)
#define		ECM_ECMINCFG0_6_IE0_192		(BIT0)
	#define		ECM_ECMINCFG0_6_IE0_192_DISABLE	(0)
	#define		ECM_ECMINCFG0_6_IE0_192_ENABLE		(1)

/* ECMINCFG0_7 */
#define		ECM_ECMINCFG0_7_IE0_255		(BIT31)
	#define		ECM_ECMINCFG0_7_IE0_255_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_255_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_254		(BIT30)
	#define		ECM_ECMINCFG0_7_IE0_254_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_254_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_253		(BIT29)
	#define		ECM_ECMINCFG0_7_IE0_253_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_253_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_252		(BIT28)
	#define		ECM_ECMINCFG0_7_IE0_252_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_252_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_251		(BIT27)
	#define		ECM_ECMINCFG0_7_IE0_251_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_251_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_250		(BIT26)
	#define		ECM_ECMINCFG0_7_IE0_250_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_250_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_249		(BIT25)
	#define		ECM_ECMINCFG0_7_IE0_249_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_249_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_248		(BIT24)
	#define		ECM_ECMINCFG0_7_IE0_248_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_248_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_247		(BIT23)
	#define		ECM_ECMINCFG0_7_IE0_247_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_247_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_246		(BIT22)
	#define		ECM_ECMINCFG0_7_IE0_246_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_246_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_245		(BIT21)
	#define		ECM_ECMINCFG0_7_IE0_245_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_245_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_244		(BIT20)
	#define		ECM_ECMINCFG0_7_IE0_244_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_244_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_243		(BIT19)
	#define		ECM_ECMINCFG0_7_IE0_243_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_243_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_242		(BIT18)
	#define		ECM_ECMINCFG0_7_IE0_242_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_242_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_241		(BIT17)
	#define		ECM_ECMINCFG0_7_IE0_241_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_241_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_240		(BIT16)
	#define		ECM_ECMINCFG0_7_IE0_240_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_240_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_239		(BIT15)
	#define		ECM_ECMINCFG0_7_IE0_239_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_239_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_238		(BIT14)
	#define		ECM_ECMINCFG0_7_IE0_238_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_238_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_237		(BIT13)
	#define		ECM_ECMINCFG0_7_IE0_237_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_237_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_236		(BIT12)
	#define		ECM_ECMINCFG0_7_IE0_236_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_236_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_235		(BIT11)
	#define		ECM_ECMINCFG0_7_IE0_235_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_235_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_234		(BIT10)
	#define		ECM_ECMINCFG0_7_IE0_234_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_234_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_233		(BIT9)
	#define		ECM_ECMINCFG0_7_IE0_233_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_233_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_232		(BIT8)
	#define		ECM_ECMINCFG0_7_IE0_232_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_232_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_231		(BIT7)
	#define		ECM_ECMINCFG0_7_IE0_231_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_231_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_230		(BIT6)
	#define		ECM_ECMINCFG0_7_IE0_230_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_230_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_229		(BIT5)
	#define		ECM_ECMINCFG0_7_IE0_229_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_229_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_228		(BIT4)
	#define		ECM_ECMINCFG0_7_IE0_228_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_228_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_227		(BIT3)
	#define		ECM_ECMINCFG0_7_IE0_227_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_227_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_226		(BIT2)
	#define		ECM_ECMINCFG0_7_IE0_226_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_226_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_225		(BIT1)
	#define		ECM_ECMINCFG0_7_IE0_225_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_225_ENABLE		(1)
#define		ECM_ECMINCFG0_7_IE0_224		(BIT0)
	#define		ECM_ECMINCFG0_7_IE0_224_DISABLE	(0)
	#define		ECM_ECMINCFG0_7_IE0_224_ENABLE		(1)

/* ECMINCFG0_8 */
#define		ECM_ECMINCFG0_8_IE0_287		(BIT31)
	#define		ECM_ECMINCFG0_8_IE0_287_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_287_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_286		(BIT30)
	#define		ECM_ECMINCFG0_8_IE0_286_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_286_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_285		(BIT29)
	#define		ECM_ECMINCFG0_8_IE0_285_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_285_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_284		(BIT28)
	#define		ECM_ECMINCFG0_8_IE0_284_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_284_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_283		(BIT27)
	#define		ECM_ECMINCFG0_8_IE0_283_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_283_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_282		(BIT26)
	#define		ECM_ECMINCFG0_8_IE0_282_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_282_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_281		(BIT25)
	#define		ECM_ECMINCFG0_8_IE0_281_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_281_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_280		(BIT24)
	#define		ECM_ECMINCFG0_8_IE0_280_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_280_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_279		(BIT23)
	#define		ECM_ECMINCFG0_8_IE0_279_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_279_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_278		(BIT22)
	#define		ECM_ECMINCFG0_8_IE0_278_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_278_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_277		(BIT21)
	#define		ECM_ECMINCFG0_8_IE0_277_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_277_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_276		(BIT20)
	#define		ECM_ECMINCFG0_8_IE0_276_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_276_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_275		(BIT19)
	#define		ECM_ECMINCFG0_8_IE0_275_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_275_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_274		(BIT18)
	#define		ECM_ECMINCFG0_8_IE0_274_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_274_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_273		(BIT17)
	#define		ECM_ECMINCFG0_8_IE0_273_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_273_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_272		(BIT16)
	#define		ECM_ECMINCFG0_8_IE0_272_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_272_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_271		(BIT15)
	#define		ECM_ECMINCFG0_8_IE0_271_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_271_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_270		(BIT14)
	#define		ECM_ECMINCFG0_8_IE0_270_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_270_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_269		(BIT13)
	#define		ECM_ECMINCFG0_8_IE0_269_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_269_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_268		(BIT12)
	#define		ECM_ECMINCFG0_8_IE0_268_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_268_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_267		(BIT11)
	#define		ECM_ECMINCFG0_8_IE0_267_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_267_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_266		(BIT10)
	#define		ECM_ECMINCFG0_8_IE0_266_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_266_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_265		(BIT9)
	#define		ECM_ECMINCFG0_8_IE0_265_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_265_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_264		(BIT8)
	#define		ECM_ECMINCFG0_8_IE0_264_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_264_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_263		(BIT7)
	#define		ECM_ECMINCFG0_8_IE0_263_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_263_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_262		(BIT6)
	#define		ECM_ECMINCFG0_8_IE0_262_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_262_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_261		(BIT5)
	#define		ECM_ECMINCFG0_8_IE0_261_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_261_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_260		(BIT4)
	#define		ECM_ECMINCFG0_8_IE0_260_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_260_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_259		(BIT3)
	#define		ECM_ECMINCFG0_8_IE0_259_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_259_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_258		(BIT2)
	#define		ECM_ECMINCFG0_8_IE0_258_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_258_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_257		(BIT1)
	#define		ECM_ECMINCFG0_8_IE0_257_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_257_ENABLE		(1)
#define		ECM_ECMINCFG0_8_IE0_256		(BIT0)
	#define		ECM_ECMINCFG0_8_IE0_256_DISABLE	(0)
	#define		ECM_ECMINCFG0_8_IE0_256_ENABLE		(1)

/* ECMINCFG0_9 */
#define		ECM_ECMINCFG0_9_IE0_319		(BIT31)
	#define		ECM_ECMINCFG0_9_IE0_319_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_319_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_318		(BIT30)
	#define		ECM_ECMINCFG0_9_IE0_318_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_318_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_317		(BIT29)
	#define		ECM_ECMINCFG0_9_IE0_317_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_317_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_316		(BIT28)
	#define		ECM_ECMINCFG0_9_IE0_316_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_316_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_315		(BIT27)
	#define		ECM_ECMINCFG0_9_IE0_315_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_315_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_314		(BIT26)
	#define		ECM_ECMINCFG0_9_IE0_314_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_314_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_313		(BIT25)
	#define		ECM_ECMINCFG0_9_IE0_313_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_313_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_312		(BIT24)
	#define		ECM_ECMINCFG0_9_IE0_312_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_312_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_311		(BIT23)
	#define		ECM_ECMINCFG0_9_IE0_311_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_311_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_310		(BIT22)
	#define		ECM_ECMINCFG0_9_IE0_310_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_310_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_309		(BIT21)
	#define		ECM_ECMINCFG0_9_IE0_309_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_309_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_308		(BIT20)
	#define		ECM_ECMINCFG0_9_IE0_308_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_308_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_307		(BIT19)
	#define		ECM_ECMINCFG0_9_IE0_307_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_307_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_306		(BIT18)
	#define		ECM_ECMINCFG0_9_IE0_306_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_306_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_305		(BIT17)
	#define		ECM_ECMINCFG0_9_IE0_305_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_305_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_304		(BIT16)
	#define		ECM_ECMINCFG0_9_IE0_304_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_304_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_303		(BIT15)
	#define		ECM_ECMINCFG0_9_IE0_303_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_303_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_302		(BIT14)
	#define		ECM_ECMINCFG0_9_IE0_302_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_302_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_301		(BIT13)
	#define		ECM_ECMINCFG0_9_IE0_301_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_301_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_300		(BIT12)
	#define		ECM_ECMINCFG0_9_IE0_300_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_300_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_299		(BIT11)
	#define		ECM_ECMINCFG0_9_IE0_299_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_299_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_298		(BIT10)
	#define		ECM_ECMINCFG0_9_IE0_298_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_298_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_297		(BIT9)
	#define		ECM_ECMINCFG0_9_IE0_297_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_297_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_296		(BIT8)
	#define		ECM_ECMINCFG0_9_IE0_296_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_296_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_295		(BIT7)
	#define		ECM_ECMINCFG0_9_IE0_295_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_295_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_294		(BIT6)
	#define		ECM_ECMINCFG0_9_IE0_294_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_294_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_293		(BIT5)
	#define		ECM_ECMINCFG0_9_IE0_293_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_293_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_292		(BIT4)
	#define		ECM_ECMINCFG0_9_IE0_292_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_292_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_291		(BIT3)
	#define		ECM_ECMINCFG0_9_IE0_291_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_291_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_290		(BIT2)
	#define		ECM_ECMINCFG0_9_IE0_290_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_290_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_289		(BIT1)
	#define		ECM_ECMINCFG0_9_IE0_289_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_289_ENABLE		(1)
#define		ECM_ECMINCFG0_9_IE0_288		(BIT0)
	#define		ECM_ECMINCFG0_9_IE0_288_DISABLE	(0)
	#define		ECM_ECMINCFG0_9_IE0_288_ENABLE		(1)

/* ECMINCFG0_10 */
#define		ECM_ECMINCFG0_10_IE0_351		(BIT31)
	#define		ECM_ECMINCFG0_10_IE0_351_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_351_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_350		(BIT30)
	#define		ECM_ECMINCFG0_10_IE0_350_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_350_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_349		(BIT29)
	#define		ECM_ECMINCFG0_10_IE0_349_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_349_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_348		(BIT28)
	#define		ECM_ECMINCFG0_10_IE0_348_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_348_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_347		(BIT27)
	#define		ECM_ECMINCFG0_10_IE0_347_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_347_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_346		(BIT26)
	#define		ECM_ECMINCFG0_10_IE0_346_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_346_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_345		(BIT25)
	#define		ECM_ECMINCFG0_10_IE0_345_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_345_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_344		(BIT24)
	#define		ECM_ECMINCFG0_10_IE0_344_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_344_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_343		(BIT23)
	#define		ECM_ECMINCFG0_10_IE0_343_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_343_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_342		(BIT22)
	#define		ECM_ECMINCFG0_10_IE0_342_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_342_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_341		(BIT21)
	#define		ECM_ECMINCFG0_10_IE0_341_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_341_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_340		(BIT20)
	#define		ECM_ECMINCFG0_10_IE0_340_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_340_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_339		(BIT19)
	#define		ECM_ECMINCFG0_10_IE0_339_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_339_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_338		(BIT18)
	#define		ECM_ECMINCFG0_10_IE0_338_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_338_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_337		(BIT17)
	#define		ECM_ECMINCFG0_10_IE0_337_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_337_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_336		(BIT16)
	#define		ECM_ECMINCFG0_10_IE0_336_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_336_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_335		(BIT15)
	#define		ECM_ECMINCFG0_10_IE0_335_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_335_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_334		(BIT14)
	#define		ECM_ECMINCFG0_10_IE0_334_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_334_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_333		(BIT13)
	#define		ECM_ECMINCFG0_10_IE0_333_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_333_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_332		(BIT12)
	#define		ECM_ECMINCFG0_10_IE0_332_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_332_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_331		(BIT11)
	#define		ECM_ECMINCFG0_10_IE0_331_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_331_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_330		(BIT10)
	#define		ECM_ECMINCFG0_10_IE0_330_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_330_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_329		(BIT9)
	#define		ECM_ECMINCFG0_10_IE0_329_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_329_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_328		(BIT8)
	#define		ECM_ECMINCFG0_10_IE0_328_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_328_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_327		(BIT7)
	#define		ECM_ECMINCFG0_10_IE0_327_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_327_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_326		(BIT6)
	#define		ECM_ECMINCFG0_10_IE0_326_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_326_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_325		(BIT5)
	#define		ECM_ECMINCFG0_10_IE0_325_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_325_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_324		(BIT4)
	#define		ECM_ECMINCFG0_10_IE0_324_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_324_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_323		(BIT3)
	#define		ECM_ECMINCFG0_10_IE0_323_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_323_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_322		(BIT2)
	#define		ECM_ECMINCFG0_10_IE0_322_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_322_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_321		(BIT1)
	#define		ECM_ECMINCFG0_10_IE0_321_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_321_ENABLE		(1)
#define		ECM_ECMINCFG0_10_IE0_320		(BIT0)
	#define		ECM_ECMINCFG0_10_IE0_320_DISABLE	(0)
	#define		ECM_ECMINCFG0_10_IE0_320_ENABLE		(1)

/* ECMINCFG1_0 */
#define		ECM_ECMINCFG1_0_IE1_031		(BIT31)
	#define		ECM_ECMINCFG1_0_IE1_031_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_031_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_030		(BIT30)
	#define		ECM_ECMINCFG1_0_IE1_030_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_030_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_029		(BIT29)
	#define		ECM_ECMINCFG1_0_IE1_029_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_029_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_028		(BIT28)
	#define		ECM_ECMINCFG1_0_IE1_028_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_028_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_027		(BIT27)
	#define		ECM_ECMINCFG1_0_IE1_027_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_027_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_026		(BIT26)
	#define		ECM_ECMINCFG1_0_IE1_026_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_026_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_025		(BIT25)
	#define		ECM_ECMINCFG1_0_IE1_025_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_025_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_024		(BIT24)
	#define		ECM_ECMINCFG1_0_IE1_024_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_024_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_023		(BIT23)
	#define		ECM_ECMINCFG1_0_IE1_023_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_023_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_022		(BIT22)
	#define		ECM_ECMINCFG1_0_IE1_022_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_022_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_021		(BIT21)
	#define		ECM_ECMINCFG1_0_IE1_021_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_021_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_020		(BIT20)
	#define		ECM_ECMINCFG1_0_IE1_020_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_020_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_019		(BIT19)
	#define		ECM_ECMINCFG1_0_IE1_019_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_019_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_018		(BIT18)
	#define		ECM_ECMINCFG1_0_IE1_018_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_018_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_017		(BIT17)
	#define		ECM_ECMINCFG1_0_IE1_017_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_017_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_016		(BIT16)
	#define		ECM_ECMINCFG1_0_IE1_016_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_016_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_015		(BIT15)
	#define		ECM_ECMINCFG1_0_IE1_015_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_015_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_014		(BIT14)
	#define		ECM_ECMINCFG1_0_IE1_014_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_014_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_013		(BIT13)
	#define		ECM_ECMINCFG1_0_IE1_013_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_013_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_012		(BIT12)
	#define		ECM_ECMINCFG1_0_IE1_012_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_012_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_011		(BIT11)
	#define		ECM_ECMINCFG1_0_IE1_011_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_011_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_010		(BIT10)
	#define		ECM_ECMINCFG1_0_IE1_010_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_010_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_009		(BIT9)
	#define		ECM_ECMINCFG1_0_IE1_009_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_009_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_008		(BIT8)
	#define		ECM_ECMINCFG1_0_IE1_008_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_008_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_007		(BIT7)
	#define		ECM_ECMINCFG1_0_IE1_007_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_007_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_006		(BIT6)
	#define		ECM_ECMINCFG1_0_IE1_006_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_006_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_005		(BIT5)
	#define		ECM_ECMINCFG1_0_IE1_005_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_005_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_004		(BIT4)
	#define		ECM_ECMINCFG1_0_IE1_004_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_004_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_003		(BIT3)
	#define		ECM_ECMINCFG1_0_IE1_003_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_003_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_002		(BIT2)
	#define		ECM_ECMINCFG1_0_IE1_002_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_002_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_001		(BIT1)
	#define		ECM_ECMINCFG1_0_IE1_001_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_001_ENABLE		(1)
#define		ECM_ECMINCFG1_0_IE1_000		(BIT0)
	#define		ECM_ECMINCFG1_0_IE1_000_DISABLE	(0)
	#define		ECM_ECMINCFG1_0_IE1_000_ENABLE		(1)

/* ECMINCFG1_1 */
#define		ECM_ECMINCFG1_1_IE1_063		(BIT31)
	#define		ECM_ECMINCFG1_1_IE1_063_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_063_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_062		(BIT30)
	#define		ECM_ECMINCFG1_1_IE1_062_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_062_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_061		(BIT29)
	#define		ECM_ECMINCFG1_1_IE1_061_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_061_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_060		(BIT28)
	#define		ECM_ECMINCFG1_1_IE1_060_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_060_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_059		(BIT27)
	#define		ECM_ECMINCFG1_1_IE1_059_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_059_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_058		(BIT26)
	#define		ECM_ECMINCFG1_1_IE1_058_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_058_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_057		(BIT25)
	#define		ECM_ECMINCFG1_1_IE1_057_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_057_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_056		(BIT24)
	#define		ECM_ECMINCFG1_1_IE1_056_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_056_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_055		(BIT23)
	#define		ECM_ECMINCFG1_1_IE1_055_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_055_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_054		(BIT22)
	#define		ECM_ECMINCFG1_1_IE1_054_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_054_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_053		(BIT21)
	#define		ECM_ECMINCFG1_1_IE1_053_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_053_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_052		(BIT20)
	#define		ECM_ECMINCFG1_1_IE1_052_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_052_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_051		(BIT19)
	#define		ECM_ECMINCFG1_1_IE1_051_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_051_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_050		(BIT18)
	#define		ECM_ECMINCFG1_1_IE1_050_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_050_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_049		(BIT17)
	#define		ECM_ECMINCFG1_1_IE1_049_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_049_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_048		(BIT16)
	#define		ECM_ECMINCFG1_1_IE1_048_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_048_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_047		(BIT15)
	#define		ECM_ECMINCFG1_1_IE1_047_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_047_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_046		(BIT14)
	#define		ECM_ECMINCFG1_1_IE1_046_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_046_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_045		(BIT13)
	#define		ECM_ECMINCFG1_1_IE1_045_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_045_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_044		(BIT12)
	#define		ECM_ECMINCFG1_1_IE1_044_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_044_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_043		(BIT11)
	#define		ECM_ECMINCFG1_1_IE1_043_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_043_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_042		(BIT10)
	#define		ECM_ECMINCFG1_1_IE1_042_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_042_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_041		(BIT9)
	#define		ECM_ECMINCFG1_1_IE1_041_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_041_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_040		(BIT8)
	#define		ECM_ECMINCFG1_1_IE1_040_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_040_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_039		(BIT7)
	#define		ECM_ECMINCFG1_1_IE1_039_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_039_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_038		(BIT6)
	#define		ECM_ECMINCFG1_1_IE1_038_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_038_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_037		(BIT5)
	#define		ECM_ECMINCFG1_1_IE1_037_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_037_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_036		(BIT4)
	#define		ECM_ECMINCFG1_1_IE1_036_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_036_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_035		(BIT3)
	#define		ECM_ECMINCFG1_1_IE1_035_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_035_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_034		(BIT2)
	#define		ECM_ECMINCFG1_1_IE1_034_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_034_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_033		(BIT1)
	#define		ECM_ECMINCFG1_1_IE1_033_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_033_ENABLE		(1)
#define		ECM_ECMINCFG1_1_IE1_032		(BIT0)
	#define		ECM_ECMINCFG1_1_IE1_032_DISABLE	(0)
	#define		ECM_ECMINCFG1_1_IE1_032_ENABLE		(1)

/* ECMINCFG1_2 */
#define		ECM_ECMINCFG1_2_IE1_095		(BIT31)
	#define		ECM_ECMINCFG1_2_IE1_095_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_095_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_094		(BIT30)
	#define		ECM_ECMINCFG1_2_IE1_094_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_094_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_093		(BIT29)
	#define		ECM_ECMINCFG1_2_IE1_093_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_093_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_092		(BIT28)
	#define		ECM_ECMINCFG1_2_IE1_092_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_092_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_091		(BIT27)
	#define		ECM_ECMINCFG1_2_IE1_091_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_091_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_090		(BIT26)
	#define		ECM_ECMINCFG1_2_IE1_090_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_090_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_089		(BIT25)
	#define		ECM_ECMINCFG1_2_IE1_089_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_089_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_088		(BIT24)
	#define		ECM_ECMINCFG1_2_IE1_088_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_088_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_087		(BIT23)
	#define		ECM_ECMINCFG1_2_IE1_087_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_087_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_086		(BIT22)
	#define		ECM_ECMINCFG1_2_IE1_086_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_086_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_085		(BIT21)
	#define		ECM_ECMINCFG1_2_IE1_085_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_085_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_084		(BIT20)
	#define		ECM_ECMINCFG1_2_IE1_084_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_084_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_083		(BIT19)
	#define		ECM_ECMINCFG1_2_IE1_083_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_083_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_082		(BIT18)
	#define		ECM_ECMINCFG1_2_IE1_082_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_082_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_081		(BIT17)
	#define		ECM_ECMINCFG1_2_IE1_081_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_081_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_080		(BIT16)
	#define		ECM_ECMINCFG1_2_IE1_080_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_080_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_079		(BIT15)
	#define		ECM_ECMINCFG1_2_IE1_079_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_079_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_078		(BIT14)
	#define		ECM_ECMINCFG1_2_IE1_078_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_078_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_077		(BIT13)
	#define		ECM_ECMINCFG1_2_IE1_077_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_077_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_076		(BIT12)
	#define		ECM_ECMINCFG1_2_IE1_076_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_076_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_075		(BIT11)
	#define		ECM_ECMINCFG1_2_IE1_075_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_075_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_074		(BIT10)
	#define		ECM_ECMINCFG1_2_IE1_074_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_074_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_073		(BIT9)
	#define		ECM_ECMINCFG1_2_IE1_073_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_073_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_072		(BIT8)
	#define		ECM_ECMINCFG1_2_IE1_072_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_072_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_071		(BIT7)
	#define		ECM_ECMINCFG1_2_IE1_071_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_071_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_070		(BIT6)
	#define		ECM_ECMINCFG1_2_IE1_070_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_070_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_069		(BIT5)
	#define		ECM_ECMINCFG1_2_IE1_069_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_069_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_068		(BIT4)
	#define		ECM_ECMINCFG1_2_IE1_068_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_068_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_067		(BIT3)
	#define		ECM_ECMINCFG1_2_IE1_067_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_067_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_066		(BIT2)
	#define		ECM_ECMINCFG1_2_IE1_066_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_066_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_065		(BIT1)
	#define		ECM_ECMINCFG1_2_IE1_065_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_065_ENABLE		(1)
#define		ECM_ECMINCFG1_2_IE1_064		(BIT0)
	#define		ECM_ECMINCFG1_2_IE1_064_DISABLE	(0)
	#define		ECM_ECMINCFG1_2_IE1_064_ENABLE		(1)

/* ECMINCFG1_3 */
#define		ECM_ECMINCFG1_3_IE1_127		(BIT31)
	#define		ECM_ECMINCFG1_3_IE1_127_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_127_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_126		(BIT30)
	#define		ECM_ECMINCFG1_3_IE1_126_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_126_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_125		(BIT29)
	#define		ECM_ECMINCFG1_3_IE1_125_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_125_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_124		(BIT28)
	#define		ECM_ECMINCFG1_3_IE1_124_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_124_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_123		(BIT27)
	#define		ECM_ECMINCFG1_3_IE1_123_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_123_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_122		(BIT26)
	#define		ECM_ECMINCFG1_3_IE1_122_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_122_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_121		(BIT25)
	#define		ECM_ECMINCFG1_3_IE1_121_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_121_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_120		(BIT24)
	#define		ECM_ECMINCFG1_3_IE1_120_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_120_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_119		(BIT23)
	#define		ECM_ECMINCFG1_3_IE1_119_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_119_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_118		(BIT22)
	#define		ECM_ECMINCFG1_3_IE1_118_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_118_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_117		(BIT21)
	#define		ECM_ECMINCFG1_3_IE1_117_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_117_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_116		(BIT20)
	#define		ECM_ECMINCFG1_3_IE1_116_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_116_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_115		(BIT19)
	#define		ECM_ECMINCFG1_3_IE1_115_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_115_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_114		(BIT18)
	#define		ECM_ECMINCFG1_3_IE1_114_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_114_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_113		(BIT17)
	#define		ECM_ECMINCFG1_3_IE1_113_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_113_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_112		(BIT16)
	#define		ECM_ECMINCFG1_3_IE1_112_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_112_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_111		(BIT15)
	#define		ECM_ECMINCFG1_3_IE1_111_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_111_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_110		(BIT14)
	#define		ECM_ECMINCFG1_3_IE1_110_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_110_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_109		(BIT13)
	#define		ECM_ECMINCFG1_3_IE1_109_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_109_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_108		(BIT12)
	#define		ECM_ECMINCFG1_3_IE1_108_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_108_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_107		(BIT11)
	#define		ECM_ECMINCFG1_3_IE1_107_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_107_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_106		(BIT10)
	#define		ECM_ECMINCFG1_3_IE1_106_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_106_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_105		(BIT9)
	#define		ECM_ECMINCFG1_3_IE1_105_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_105_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_104		(BIT8)
	#define		ECM_ECMINCFG1_3_IE1_104_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_104_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_103		(BIT7)
	#define		ECM_ECMINCFG1_3_IE1_103_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_103_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_102		(BIT6)
	#define		ECM_ECMINCFG1_3_IE1_102_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_102_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_101		(BIT5)
	#define		ECM_ECMINCFG1_3_IE1_101_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_101_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_100		(BIT4)
	#define		ECM_ECMINCFG1_3_IE1_100_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_100_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_099		(BIT3)
	#define		ECM_ECMINCFG1_3_IE1_099_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_099_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_098		(BIT2)
	#define		ECM_ECMINCFG1_3_IE1_098_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_098_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_097		(BIT1)
	#define		ECM_ECMINCFG1_3_IE1_097_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_097_ENABLE		(1)
#define		ECM_ECMINCFG1_3_IE1_096		(BIT0)
	#define		ECM_ECMINCFG1_3_IE1_096_DISABLE	(0)
	#define		ECM_ECMINCFG1_3_IE1_096_ENABLE		(1)

/* ECMINCFG1_4 */
#define		ECM_ECMINCFG1_4_IE1_159		(BIT31)
	#define		ECM_ECMINCFG1_4_IE1_159_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_159_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_158		(BIT30)
	#define		ECM_ECMINCFG1_4_IE1_158_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_158_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_157		(BIT29)
	#define		ECM_ECMINCFG1_4_IE1_157_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_157_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_156		(BIT28)
	#define		ECM_ECMINCFG1_4_IE1_156_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_156_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_155		(BIT27)
	#define		ECM_ECMINCFG1_4_IE1_155_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_155_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_154		(BIT26)
	#define		ECM_ECMINCFG1_4_IE1_154_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_154_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_153		(BIT25)
	#define		ECM_ECMINCFG1_4_IE1_153_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_153_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_152		(BIT24)
	#define		ECM_ECMINCFG1_4_IE1_152_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_152_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_151		(BIT23)
	#define		ECM_ECMINCFG1_4_IE1_151_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_151_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_150		(BIT22)
	#define		ECM_ECMINCFG1_4_IE1_150_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_150_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_149		(BIT21)
	#define		ECM_ECMINCFG1_4_IE1_149_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_149_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_148		(BIT20)
	#define		ECM_ECMINCFG1_4_IE1_148_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_148_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_147		(BIT19)
	#define		ECM_ECMINCFG1_4_IE1_147_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_147_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_146		(BIT18)
	#define		ECM_ECMINCFG1_4_IE1_146_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_146_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_145		(BIT17)
	#define		ECM_ECMINCFG1_4_IE1_145_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_145_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_144		(BIT16)
	#define		ECM_ECMINCFG1_4_IE1_144_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_144_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_143		(BIT15)
	#define		ECM_ECMINCFG1_4_IE1_143_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_143_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_142		(BIT14)
	#define		ECM_ECMINCFG1_4_IE1_142_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_142_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_141		(BIT13)
	#define		ECM_ECMINCFG1_4_IE1_141_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_141_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_140		(BIT12)
	#define		ECM_ECMINCFG1_4_IE1_140_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_140_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_139		(BIT11)
	#define		ECM_ECMINCFG1_4_IE1_139_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_139_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_138		(BIT10)
	#define		ECM_ECMINCFG1_4_IE1_138_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_138_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_137		(BIT9)
	#define		ECM_ECMINCFG1_4_IE1_137_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_137_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_136		(BIT8)
	#define		ECM_ECMINCFG1_4_IE1_136_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_136_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_135		(BIT7)
	#define		ECM_ECMINCFG1_4_IE1_135_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_135_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_134		(BIT6)
	#define		ECM_ECMINCFG1_4_IE1_134_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_134_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_133		(BIT5)
	#define		ECM_ECMINCFG1_4_IE1_133_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_133_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_132		(BIT4)
	#define		ECM_ECMINCFG1_4_IE1_132_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_132_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_131		(BIT3)
	#define		ECM_ECMINCFG1_4_IE1_131_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_131_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_130		(BIT2)
	#define		ECM_ECMINCFG1_4_IE1_130_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_130_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_129		(BIT1)
	#define		ECM_ECMINCFG1_4_IE1_129_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_129_ENABLE		(1)
#define		ECM_ECMINCFG1_4_IE1_128		(BIT0)
	#define		ECM_ECMINCFG1_4_IE1_128_DISABLE	(0)
	#define		ECM_ECMINCFG1_4_IE1_128_ENABLE		(1)

/* ECMINCFG1_5 */
#define		ECM_ECMINCFG1_5_IE1_191		(BIT31)
	#define		ECM_ECMINCFG1_5_IE1_191_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_191_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_190		(BIT30)
	#define		ECM_ECMINCFG1_5_IE1_190_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_190_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_189		(BIT29)
	#define		ECM_ECMINCFG1_5_IE1_189_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_189_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_188		(BIT28)
	#define		ECM_ECMINCFG1_5_IE1_188_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_188_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_187		(BIT27)
	#define		ECM_ECMINCFG1_5_IE1_187_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_187_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_186		(BIT26)
	#define		ECM_ECMINCFG1_5_IE1_186_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_186_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_185		(BIT25)
	#define		ECM_ECMINCFG1_5_IE1_185_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_185_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_184		(BIT24)
	#define		ECM_ECMINCFG1_5_IE1_184_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_184_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_183		(BIT23)
	#define		ECM_ECMINCFG1_5_IE1_183_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_183_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_182		(BIT22)
	#define		ECM_ECMINCFG1_5_IE1_182_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_182_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_181		(BIT21)
	#define		ECM_ECMINCFG1_5_IE1_181_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_181_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_180		(BIT20)
	#define		ECM_ECMINCFG1_5_IE1_180_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_180_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_179		(BIT19)
	#define		ECM_ECMINCFG1_5_IE1_179_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_179_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_178		(BIT18)
	#define		ECM_ECMINCFG1_5_IE1_178_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_178_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_177		(BIT17)
	#define		ECM_ECMINCFG1_5_IE1_177_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_177_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_176		(BIT16)
	#define		ECM_ECMINCFG1_5_IE1_176_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_176_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_175		(BIT15)
	#define		ECM_ECMINCFG1_5_IE1_175_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_175_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_174		(BIT14)
	#define		ECM_ECMINCFG1_5_IE1_174_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_174_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_173		(BIT13)
	#define		ECM_ECMINCFG1_5_IE1_173_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_173_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_172		(BIT12)
	#define		ECM_ECMINCFG1_5_IE1_172_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_172_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_171		(BIT11)
	#define		ECM_ECMINCFG1_5_IE1_171_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_171_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_170		(BIT10)
	#define		ECM_ECMINCFG1_5_IE1_170_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_170_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_169		(BIT9)
	#define		ECM_ECMINCFG1_5_IE1_169_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_169_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_168		(BIT8)
	#define		ECM_ECMINCFG1_5_IE1_168_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_168_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_167		(BIT7)
	#define		ECM_ECMINCFG1_5_IE1_167_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_167_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_166		(BIT6)
	#define		ECM_ECMINCFG1_5_IE1_166_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_166_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_165		(BIT5)
	#define		ECM_ECMINCFG1_5_IE1_165_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_165_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_164		(BIT4)
	#define		ECM_ECMINCFG1_5_IE1_164_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_164_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_163		(BIT3)
	#define		ECM_ECMINCFG1_5_IE1_163_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_163_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_162		(BIT2)
	#define		ECM_ECMINCFG1_5_IE1_162_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_162_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_161		(BIT1)
	#define		ECM_ECMINCFG1_5_IE1_161_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_161_ENABLE		(1)
#define		ECM_ECMINCFG1_5_IE1_160		(BIT0)
	#define		ECM_ECMINCFG1_5_IE1_160_DISABLE	(0)
	#define		ECM_ECMINCFG1_5_IE1_160_ENABLE		(1)

/* ECMINCFG1_6 */
#define		ECM_ECMINCFG1_6_IE1_223		(BIT31)
	#define		ECM_ECMINCFG1_6_IE1_223_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_223_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_222		(BIT30)
	#define		ECM_ECMINCFG1_6_IE1_222_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_222_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_221		(BIT29)
	#define		ECM_ECMINCFG1_6_IE1_221_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_221_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_220		(BIT28)
	#define		ECM_ECMINCFG1_6_IE1_220_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_220_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_219		(BIT27)
	#define		ECM_ECMINCFG1_6_IE1_219_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_219_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_218		(BIT26)
	#define		ECM_ECMINCFG1_6_IE1_218_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_218_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_217		(BIT25)
	#define		ECM_ECMINCFG1_6_IE1_217_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_217_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_216		(BIT24)
	#define		ECM_ECMINCFG1_6_IE1_216_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_216_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_215		(BIT23)
	#define		ECM_ECMINCFG1_6_IE1_215_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_215_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_214		(BIT22)
	#define		ECM_ECMINCFG1_6_IE1_214_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_214_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_213		(BIT21)
	#define		ECM_ECMINCFG1_6_IE1_213_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_213_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_212		(BIT20)
	#define		ECM_ECMINCFG1_6_IE1_212_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_212_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_211		(BIT19)
	#define		ECM_ECMINCFG1_6_IE1_211_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_211_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_210		(BIT18)
	#define		ECM_ECMINCFG1_6_IE1_210_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_210_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_209		(BIT17)
	#define		ECM_ECMINCFG1_6_IE1_209_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_209_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_208		(BIT16)
	#define		ECM_ECMINCFG1_6_IE1_208_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_208_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_207		(BIT15)
	#define		ECM_ECMINCFG1_6_IE1_207_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_207_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_206		(BIT14)
	#define		ECM_ECMINCFG1_6_IE1_206_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_206_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_205		(BIT13)
	#define		ECM_ECMINCFG1_6_IE1_205_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_205_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_204		(BIT12)
	#define		ECM_ECMINCFG1_6_IE1_204_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_204_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_203		(BIT11)
	#define		ECM_ECMINCFG1_6_IE1_203_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_203_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_202		(BIT10)
	#define		ECM_ECMINCFG1_6_IE1_202_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_202_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_201		(BIT9)
	#define		ECM_ECMINCFG1_6_IE1_201_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_201_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_200		(BIT8)
	#define		ECM_ECMINCFG1_6_IE1_200_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_200_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_199		(BIT7)
	#define		ECM_ECMINCFG1_6_IE1_199_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_199_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_198		(BIT6)
	#define		ECM_ECMINCFG1_6_IE1_198_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_198_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_197		(BIT5)
	#define		ECM_ECMINCFG1_6_IE1_197_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_197_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_196		(BIT4)
	#define		ECM_ECMINCFG1_6_IE1_196_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_196_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_195		(BIT3)
	#define		ECM_ECMINCFG1_6_IE1_195_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_195_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_194		(BIT2)
	#define		ECM_ECMINCFG1_6_IE1_194_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_194_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_193		(BIT1)
	#define		ECM_ECMINCFG1_6_IE1_193_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_193_ENABLE		(1)
#define		ECM_ECMINCFG1_6_IE1_192		(BIT0)
	#define		ECM_ECMINCFG1_6_IE1_192_DISABLE	(0)
	#define		ECM_ECMINCFG1_6_IE1_192_ENABLE		(1)

/* ECMINCFG1_7 */
#define		ECM_ECMINCFG1_7_IE1_255		(BIT31)
	#define		ECM_ECMINCFG1_7_IE1_255_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_255_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_254		(BIT30)
	#define		ECM_ECMINCFG1_7_IE1_254_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_254_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_253		(BIT29)
	#define		ECM_ECMINCFG1_7_IE1_253_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_253_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_252		(BIT28)
	#define		ECM_ECMINCFG1_7_IE1_252_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_252_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_251		(BIT27)
	#define		ECM_ECMINCFG1_7_IE1_251_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_251_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_250		(BIT26)
	#define		ECM_ECMINCFG1_7_IE1_250_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_250_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_249		(BIT25)
	#define		ECM_ECMINCFG1_7_IE1_249_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_249_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_248		(BIT24)
	#define		ECM_ECMINCFG1_7_IE1_248_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_248_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_247		(BIT23)
	#define		ECM_ECMINCFG1_7_IE1_247_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_247_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_246		(BIT22)
	#define		ECM_ECMINCFG1_7_IE1_246_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_246_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_245		(BIT21)
	#define		ECM_ECMINCFG1_7_IE1_245_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_245_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_244		(BIT20)
	#define		ECM_ECMINCFG1_7_IE1_244_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_244_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_243		(BIT19)
	#define		ECM_ECMINCFG1_7_IE1_243_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_243_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_242		(BIT18)
	#define		ECM_ECMINCFG1_7_IE1_242_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_242_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_241		(BIT17)
	#define		ECM_ECMINCFG1_7_IE1_241_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_241_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_240		(BIT16)
	#define		ECM_ECMINCFG1_7_IE1_240_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_240_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_239		(BIT15)
	#define		ECM_ECMINCFG1_7_IE1_239_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_239_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_238		(BIT14)
	#define		ECM_ECMINCFG1_7_IE1_238_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_238_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_237		(BIT13)
	#define		ECM_ECMINCFG1_7_IE1_237_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_237_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_236		(BIT12)
	#define		ECM_ECMINCFG1_7_IE1_236_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_236_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_235		(BIT11)
	#define		ECM_ECMINCFG1_7_IE1_235_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_235_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_234		(BIT10)
	#define		ECM_ECMINCFG1_7_IE1_234_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_234_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_233		(BIT9)
	#define		ECM_ECMINCFG1_7_IE1_233_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_233_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_232		(BIT8)
	#define		ECM_ECMINCFG1_7_IE1_232_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_232_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_231		(BIT7)
	#define		ECM_ECMINCFG1_7_IE1_231_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_231_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_230		(BIT6)
	#define		ECM_ECMINCFG1_7_IE1_230_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_230_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_229		(BIT5)
	#define		ECM_ECMINCFG1_7_IE1_229_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_229_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_228		(BIT4)
	#define		ECM_ECMINCFG1_7_IE1_228_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_228_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_227		(BIT3)
	#define		ECM_ECMINCFG1_7_IE1_227_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_227_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_226		(BIT2)
	#define		ECM_ECMINCFG1_7_IE1_226_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_226_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_225		(BIT1)
	#define		ECM_ECMINCFG1_7_IE1_225_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_225_ENABLE		(1)
#define		ECM_ECMINCFG1_7_IE1_224		(BIT0)
	#define		ECM_ECMINCFG1_7_IE1_224_DISABLE	(0)
	#define		ECM_ECMINCFG1_7_IE1_224_ENABLE		(1)

/* ECMINCFG1_8 */
#define		ECM_ECMINCFG1_8_IE1_287		(BIT31)
	#define		ECM_ECMINCFG1_8_IE1_287_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_287_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_286		(BIT30)
	#define		ECM_ECMINCFG1_8_IE1_286_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_286_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_285		(BIT29)
	#define		ECM_ECMINCFG1_8_IE1_285_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_285_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_284		(BIT28)
	#define		ECM_ECMINCFG1_8_IE1_284_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_284_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_283		(BIT27)
	#define		ECM_ECMINCFG1_8_IE1_283_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_283_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_282		(BIT26)
	#define		ECM_ECMINCFG1_8_IE1_282_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_282_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_281		(BIT25)
	#define		ECM_ECMINCFG1_8_IE1_281_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_281_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_280		(BIT24)
	#define		ECM_ECMINCFG1_8_IE1_280_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_280_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_279		(BIT23)
	#define		ECM_ECMINCFG1_8_IE1_279_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_279_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_278		(BIT22)
	#define		ECM_ECMINCFG1_8_IE1_278_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_278_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_277		(BIT21)
	#define		ECM_ECMINCFG1_8_IE1_277_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_277_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_276		(BIT20)
	#define		ECM_ECMINCFG1_8_IE1_276_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_276_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_275		(BIT19)
	#define		ECM_ECMINCFG1_8_IE1_275_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_275_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_274		(BIT18)
	#define		ECM_ECMINCFG1_8_IE1_274_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_274_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_273		(BIT17)
	#define		ECM_ECMINCFG1_8_IE1_273_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_273_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_272		(BIT16)
	#define		ECM_ECMINCFG1_8_IE1_272_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_272_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_271		(BIT15)
	#define		ECM_ECMINCFG1_8_IE1_271_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_271_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_270		(BIT14)
	#define		ECM_ECMINCFG1_8_IE1_270_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_270_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_269		(BIT13)
	#define		ECM_ECMINCFG1_8_IE1_269_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_269_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_268		(BIT12)
	#define		ECM_ECMINCFG1_8_IE1_268_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_268_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_267		(BIT11)
	#define		ECM_ECMINCFG1_8_IE1_267_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_267_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_266		(BIT10)
	#define		ECM_ECMINCFG1_8_IE1_266_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_266_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_265		(BIT9)
	#define		ECM_ECMINCFG1_8_IE1_265_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_265_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_264		(BIT8)
	#define		ECM_ECMINCFG1_8_IE1_264_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_264_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_263		(BIT7)
	#define		ECM_ECMINCFG1_8_IE1_263_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_263_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_262		(BIT6)
	#define		ECM_ECMINCFG1_8_IE1_262_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_262_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_261		(BIT5)
	#define		ECM_ECMINCFG1_8_IE1_261_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_261_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_260		(BIT4)
	#define		ECM_ECMINCFG1_8_IE1_260_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_260_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_259		(BIT3)
	#define		ECM_ECMINCFG1_8_IE1_259_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_259_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_258		(BIT2)
	#define		ECM_ECMINCFG1_8_IE1_258_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_258_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_257		(BIT1)
	#define		ECM_ECMINCFG1_8_IE1_257_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_257_ENABLE		(1)
#define		ECM_ECMINCFG1_8_IE1_256		(BIT0)
	#define		ECM_ECMINCFG1_8_IE1_256_DISABLE	(0)
	#define		ECM_ECMINCFG1_8_IE1_256_ENABLE		(1)

/* ECMINCFG1_9 */
#define		ECM_ECMINCFG1_9_IE1_319		(BIT31)
	#define		ECM_ECMINCFG1_9_IE1_319_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_319_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_318		(BIT30)
	#define		ECM_ECMINCFG1_9_IE1_318_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_318_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_317		(BIT29)
	#define		ECM_ECMINCFG1_9_IE1_317_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_317_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_316		(BIT28)
	#define		ECM_ECMINCFG1_9_IE1_316_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_316_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_315		(BIT27)
	#define		ECM_ECMINCFG1_9_IE1_315_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_315_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_314		(BIT26)
	#define		ECM_ECMINCFG1_9_IE1_314_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_314_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_313		(BIT25)
	#define		ECM_ECMINCFG1_9_IE1_313_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_313_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_312		(BIT24)
	#define		ECM_ECMINCFG1_9_IE1_312_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_312_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_311		(BIT23)
	#define		ECM_ECMINCFG1_9_IE1_311_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_311_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_310		(BIT22)
	#define		ECM_ECMINCFG1_9_IE1_310_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_310_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_309		(BIT21)
	#define		ECM_ECMINCFG1_9_IE1_309_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_309_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_308		(BIT20)
	#define		ECM_ECMINCFG1_9_IE1_308_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_308_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_307		(BIT19)
	#define		ECM_ECMINCFG1_9_IE1_307_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_307_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_306		(BIT18)
	#define		ECM_ECMINCFG1_9_IE1_306_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_306_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_305		(BIT17)
	#define		ECM_ECMINCFG1_9_IE1_305_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_305_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_304		(BIT16)
	#define		ECM_ECMINCFG1_9_IE1_304_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_304_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_303		(BIT15)
	#define		ECM_ECMINCFG1_9_IE1_303_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_303_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_302		(BIT14)
	#define		ECM_ECMINCFG1_9_IE1_302_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_302_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_301		(BIT13)
	#define		ECM_ECMINCFG1_9_IE1_301_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_301_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_300		(BIT12)
	#define		ECM_ECMINCFG1_9_IE1_300_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_300_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_299		(BIT11)
	#define		ECM_ECMINCFG1_9_IE1_299_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_299_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_298		(BIT10)
	#define		ECM_ECMINCFG1_9_IE1_298_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_298_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_297		(BIT9)
	#define		ECM_ECMINCFG1_9_IE1_297_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_297_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_296		(BIT8)
	#define		ECM_ECMINCFG1_9_IE1_296_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_296_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_295		(BIT7)
	#define		ECM_ECMINCFG1_9_IE1_295_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_295_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_294		(BIT6)
	#define		ECM_ECMINCFG1_9_IE1_294_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_294_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_293		(BIT5)
	#define		ECM_ECMINCFG1_9_IE1_293_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_293_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_292		(BIT4)
	#define		ECM_ECMINCFG1_9_IE1_292_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_292_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_291		(BIT3)
	#define		ECM_ECMINCFG1_9_IE1_291_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_291_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_290		(BIT2)
	#define		ECM_ECMINCFG1_9_IE1_290_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_290_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_289		(BIT1)
	#define		ECM_ECMINCFG1_9_IE1_289_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_289_ENABLE		(1)
#define		ECM_ECMINCFG1_9_IE1_288		(BIT0)
	#define		ECM_ECMINCFG1_9_IE1_288_DISABLE	(0)
	#define		ECM_ECMINCFG1_9_IE1_288_ENABLE		(1)

/* ECMINCFG1_10 */
#define		ECM_ECMINCFG1_10_IE1_351		(BIT31)
	#define		ECM_ECMINCFG1_10_IE1_351_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_351_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_350		(BIT30)
	#define		ECM_ECMINCFG1_10_IE1_350_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_350_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_349		(BIT29)
	#define		ECM_ECMINCFG1_10_IE1_349_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_349_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_348		(BIT28)
	#define		ECM_ECMINCFG1_10_IE1_348_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_348_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_347		(BIT27)
	#define		ECM_ECMINCFG1_10_IE1_347_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_347_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_346		(BIT26)
	#define		ECM_ECMINCFG1_10_IE1_346_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_346_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_345		(BIT25)
	#define		ECM_ECMINCFG1_10_IE1_345_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_345_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_344		(BIT24)
	#define		ECM_ECMINCFG1_10_IE1_344_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_344_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_343		(BIT23)
	#define		ECM_ECMINCFG1_10_IE1_343_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_343_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_342		(BIT22)
	#define		ECM_ECMINCFG1_10_IE1_342_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_342_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_341		(BIT21)
	#define		ECM_ECMINCFG1_10_IE1_341_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_341_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_340		(BIT20)
	#define		ECM_ECMINCFG1_10_IE1_340_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_340_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_339		(BIT19)
	#define		ECM_ECMINCFG1_10_IE1_339_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_339_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_338		(BIT18)
	#define		ECM_ECMINCFG1_10_IE1_338_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_338_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_337		(BIT17)
	#define		ECM_ECMINCFG1_10_IE1_337_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_337_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_336		(BIT16)
	#define		ECM_ECMINCFG1_10_IE1_336_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_336_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_335		(BIT15)
	#define		ECM_ECMINCFG1_10_IE1_335_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_335_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_334		(BIT14)
	#define		ECM_ECMINCFG1_10_IE1_334_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_334_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_333		(BIT13)
	#define		ECM_ECMINCFG1_10_IE1_333_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_333_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_332		(BIT12)
	#define		ECM_ECMINCFG1_10_IE1_332_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_332_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_331		(BIT11)
	#define		ECM_ECMINCFG1_10_IE1_331_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_331_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_330		(BIT10)
	#define		ECM_ECMINCFG1_10_IE1_330_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_330_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_329		(BIT9)
	#define		ECM_ECMINCFG1_10_IE1_329_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_329_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_328		(BIT8)
	#define		ECM_ECMINCFG1_10_IE1_328_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_328_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_327		(BIT7)
	#define		ECM_ECMINCFG1_10_IE1_327_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_327_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_326		(BIT6)
	#define		ECM_ECMINCFG1_10_IE1_326_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_326_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_325		(BIT5)
	#define		ECM_ECMINCFG1_10_IE1_325_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_325_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_324		(BIT4)
	#define		ECM_ECMINCFG1_10_IE1_324_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_324_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_323		(BIT3)
	#define		ECM_ECMINCFG1_10_IE1_323_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_323_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_322		(BIT2)
	#define		ECM_ECMINCFG1_10_IE1_322_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_322_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_321		(BIT1)
	#define		ECM_ECMINCFG1_10_IE1_321_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_321_ENABLE		(1)
#define		ECM_ECMINCFG1_10_IE1_320		(BIT0)
	#define		ECM_ECMINCFG1_10_IE1_320_DISABLE	(0)
	#define		ECM_ECMINCFG1_10_IE1_320_ENABLE		(1)

/* ECMINCFG2_0 */
#define		ECM_ECMINCFG2_0_IE2_031		(BIT31)
	#define		ECM_ECMINCFG2_0_IE2_031_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_031_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_030		(BIT30)
	#define		ECM_ECMINCFG2_0_IE2_030_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_030_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_029		(BIT29)
	#define		ECM_ECMINCFG2_0_IE2_029_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_029_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_028		(BIT28)
	#define		ECM_ECMINCFG2_0_IE2_028_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_028_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_027		(BIT27)
	#define		ECM_ECMINCFG2_0_IE2_027_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_027_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_026		(BIT26)
	#define		ECM_ECMINCFG2_0_IE2_026_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_026_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_025		(BIT25)
	#define		ECM_ECMINCFG2_0_IE2_025_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_025_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_024		(BIT24)
	#define		ECM_ECMINCFG2_0_IE2_024_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_024_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_023		(BIT23)
	#define		ECM_ECMINCFG2_0_IE2_023_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_023_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_022		(BIT22)
	#define		ECM_ECMINCFG2_0_IE2_022_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_022_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_021		(BIT21)
	#define		ECM_ECMINCFG2_0_IE2_021_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_021_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_020		(BIT20)
	#define		ECM_ECMINCFG2_0_IE2_020_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_020_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_019		(BIT19)
	#define		ECM_ECMINCFG2_0_IE2_019_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_019_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_018		(BIT18)
	#define		ECM_ECMINCFG2_0_IE2_018_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_018_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_017		(BIT17)
	#define		ECM_ECMINCFG2_0_IE2_017_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_017_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_016		(BIT16)
	#define		ECM_ECMINCFG2_0_IE2_016_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_016_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_015		(BIT15)
	#define		ECM_ECMINCFG2_0_IE2_015_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_015_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_014		(BIT14)
	#define		ECM_ECMINCFG2_0_IE2_014_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_014_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_013		(BIT13)
	#define		ECM_ECMINCFG2_0_IE2_013_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_013_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_012		(BIT12)
	#define		ECM_ECMINCFG2_0_IE2_012_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_012_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_011		(BIT11)
	#define		ECM_ECMINCFG2_0_IE2_011_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_011_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_010		(BIT10)
	#define		ECM_ECMINCFG2_0_IE2_010_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_010_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_009		(BIT9)
	#define		ECM_ECMINCFG2_0_IE2_009_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_009_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_008		(BIT8)
	#define		ECM_ECMINCFG2_0_IE2_008_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_008_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_007		(BIT7)
	#define		ECM_ECMINCFG2_0_IE2_007_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_007_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_006		(BIT6)
	#define		ECM_ECMINCFG2_0_IE2_006_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_006_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_005		(BIT5)
	#define		ECM_ECMINCFG2_0_IE2_005_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_005_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_004		(BIT4)
	#define		ECM_ECMINCFG2_0_IE2_004_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_004_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_003		(BIT3)
	#define		ECM_ECMINCFG2_0_IE2_003_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_003_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_002		(BIT2)
	#define		ECM_ECMINCFG2_0_IE2_002_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_002_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_001		(BIT1)
	#define		ECM_ECMINCFG2_0_IE2_001_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_001_ENABLE		(1)
#define		ECM_ECMINCFG2_0_IE2_000		(BIT0)
	#define		ECM_ECMINCFG2_0_IE2_000_DISABLE	(0)
	#define		ECM_ECMINCFG2_0_IE2_000_ENABLE		(1)

/* ECMINCFG2_1 */
#define		ECM_ECMINCFG2_1_IE2_063		(BIT31)
	#define		ECM_ECMINCFG2_1_IE2_063_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_063_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_062		(BIT30)
	#define		ECM_ECMINCFG2_1_IE2_062_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_062_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_061		(BIT29)
	#define		ECM_ECMINCFG2_1_IE2_061_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_061_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_060		(BIT28)
	#define		ECM_ECMINCFG2_1_IE2_060_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_060_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_059		(BIT27)
	#define		ECM_ECMINCFG2_1_IE2_059_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_059_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_058		(BIT26)
	#define		ECM_ECMINCFG2_1_IE2_058_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_058_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_057		(BIT25)
	#define		ECM_ECMINCFG2_1_IE2_057_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_057_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_056		(BIT24)
	#define		ECM_ECMINCFG2_1_IE2_056_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_056_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_055		(BIT23)
	#define		ECM_ECMINCFG2_1_IE2_055_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_055_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_054		(BIT22)
	#define		ECM_ECMINCFG2_1_IE2_054_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_054_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_053		(BIT21)
	#define		ECM_ECMINCFG2_1_IE2_053_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_053_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_052		(BIT20)
	#define		ECM_ECMINCFG2_1_IE2_052_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_052_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_051		(BIT19)
	#define		ECM_ECMINCFG2_1_IE2_051_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_051_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_050		(BIT18)
	#define		ECM_ECMINCFG2_1_IE2_050_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_050_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_049		(BIT17)
	#define		ECM_ECMINCFG2_1_IE2_049_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_049_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_048		(BIT16)
	#define		ECM_ECMINCFG2_1_IE2_048_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_048_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_047		(BIT15)
	#define		ECM_ECMINCFG2_1_IE2_047_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_047_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_046		(BIT14)
	#define		ECM_ECMINCFG2_1_IE2_046_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_046_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_045		(BIT13)
	#define		ECM_ECMINCFG2_1_IE2_045_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_045_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_044		(BIT12)
	#define		ECM_ECMINCFG2_1_IE2_044_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_044_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_043		(BIT11)
	#define		ECM_ECMINCFG2_1_IE2_043_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_043_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_042		(BIT10)
	#define		ECM_ECMINCFG2_1_IE2_042_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_042_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_041		(BIT9)
	#define		ECM_ECMINCFG2_1_IE2_041_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_041_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_040		(BIT8)
	#define		ECM_ECMINCFG2_1_IE2_040_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_040_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_039		(BIT7)
	#define		ECM_ECMINCFG2_1_IE2_039_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_039_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_038		(BIT6)
	#define		ECM_ECMINCFG2_1_IE2_038_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_038_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_037		(BIT5)
	#define		ECM_ECMINCFG2_1_IE2_037_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_037_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_036		(BIT4)
	#define		ECM_ECMINCFG2_1_IE2_036_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_036_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_035		(BIT3)
	#define		ECM_ECMINCFG2_1_IE2_035_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_035_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_034		(BIT2)
	#define		ECM_ECMINCFG2_1_IE2_034_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_034_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_033		(BIT1)
	#define		ECM_ECMINCFG2_1_IE2_033_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_033_ENABLE		(1)
#define		ECM_ECMINCFG2_1_IE2_032		(BIT0)
	#define		ECM_ECMINCFG2_1_IE2_032_DISABLE	(0)
	#define		ECM_ECMINCFG2_1_IE2_032_ENABLE		(1)

/* ECMINCFG2_2 */
#define		ECM_ECMINCFG2_2_IE2_095		(BIT31)
	#define		ECM_ECMINCFG2_2_IE2_095_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_095_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_094		(BIT30)
	#define		ECM_ECMINCFG2_2_IE2_094_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_094_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_093		(BIT29)
	#define		ECM_ECMINCFG2_2_IE2_093_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_093_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_092		(BIT28)
	#define		ECM_ECMINCFG2_2_IE2_092_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_092_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_091		(BIT27)
	#define		ECM_ECMINCFG2_2_IE2_091_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_091_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_090		(BIT26)
	#define		ECM_ECMINCFG2_2_IE2_090_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_090_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_089		(BIT25)
	#define		ECM_ECMINCFG2_2_IE2_089_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_089_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_088		(BIT24)
	#define		ECM_ECMINCFG2_2_IE2_088_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_088_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_087		(BIT23)
	#define		ECM_ECMINCFG2_2_IE2_087_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_087_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_086		(BIT22)
	#define		ECM_ECMINCFG2_2_IE2_086_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_086_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_085		(BIT21)
	#define		ECM_ECMINCFG2_2_IE2_085_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_085_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_084		(BIT20)
	#define		ECM_ECMINCFG2_2_IE2_084_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_084_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_083		(BIT19)
	#define		ECM_ECMINCFG2_2_IE2_083_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_083_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_082		(BIT18)
	#define		ECM_ECMINCFG2_2_IE2_082_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_082_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_081		(BIT17)
	#define		ECM_ECMINCFG2_2_IE2_081_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_081_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_080		(BIT16)
	#define		ECM_ECMINCFG2_2_IE2_080_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_080_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_079		(BIT15)
	#define		ECM_ECMINCFG2_2_IE2_079_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_079_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_078		(BIT14)
	#define		ECM_ECMINCFG2_2_IE2_078_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_078_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_077		(BIT13)
	#define		ECM_ECMINCFG2_2_IE2_077_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_077_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_076		(BIT12)
	#define		ECM_ECMINCFG2_2_IE2_076_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_076_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_075		(BIT11)
	#define		ECM_ECMINCFG2_2_IE2_075_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_075_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_074		(BIT10)
	#define		ECM_ECMINCFG2_2_IE2_074_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_074_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_073		(BIT9)
	#define		ECM_ECMINCFG2_2_IE2_073_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_073_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_072		(BIT8)
	#define		ECM_ECMINCFG2_2_IE2_072_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_072_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_071		(BIT7)
	#define		ECM_ECMINCFG2_2_IE2_071_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_071_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_070		(BIT6)
	#define		ECM_ECMINCFG2_2_IE2_070_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_070_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_069		(BIT5)
	#define		ECM_ECMINCFG2_2_IE2_069_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_069_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_068		(BIT4)
	#define		ECM_ECMINCFG2_2_IE2_068_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_068_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_067		(BIT3)
	#define		ECM_ECMINCFG2_2_IE2_067_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_067_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_066		(BIT2)
	#define		ECM_ECMINCFG2_2_IE2_066_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_066_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_065		(BIT1)
	#define		ECM_ECMINCFG2_2_IE2_065_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_065_ENABLE		(1)
#define		ECM_ECMINCFG2_2_IE2_064		(BIT0)
	#define		ECM_ECMINCFG2_2_IE2_064_DISABLE	(0)
	#define		ECM_ECMINCFG2_2_IE2_064_ENABLE		(1)

/* ECMINCFG2_3 */
#define		ECM_ECMINCFG2_3_IE2_127		(BIT31)
	#define		ECM_ECMINCFG2_3_IE2_127_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_127_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_126		(BIT30)
	#define		ECM_ECMINCFG2_3_IE2_126_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_126_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_125		(BIT29)
	#define		ECM_ECMINCFG2_3_IE2_125_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_125_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_124		(BIT28)
	#define		ECM_ECMINCFG2_3_IE2_124_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_124_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_123		(BIT27)
	#define		ECM_ECMINCFG2_3_IE2_123_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_123_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_122		(BIT26)
	#define		ECM_ECMINCFG2_3_IE2_122_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_122_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_121		(BIT25)
	#define		ECM_ECMINCFG2_3_IE2_121_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_121_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_120		(BIT24)
	#define		ECM_ECMINCFG2_3_IE2_120_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_120_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_119		(BIT23)
	#define		ECM_ECMINCFG2_3_IE2_119_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_119_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_118		(BIT22)
	#define		ECM_ECMINCFG2_3_IE2_118_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_118_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_117		(BIT21)
	#define		ECM_ECMINCFG2_3_IE2_117_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_117_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_116		(BIT20)
	#define		ECM_ECMINCFG2_3_IE2_116_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_116_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_115		(BIT19)
	#define		ECM_ECMINCFG2_3_IE2_115_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_115_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_114		(BIT18)
	#define		ECM_ECMINCFG2_3_IE2_114_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_114_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_113		(BIT17)
	#define		ECM_ECMINCFG2_3_IE2_113_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_113_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_112		(BIT16)
	#define		ECM_ECMINCFG2_3_IE2_112_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_112_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_111		(BIT15)
	#define		ECM_ECMINCFG2_3_IE2_111_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_111_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_110		(BIT14)
	#define		ECM_ECMINCFG2_3_IE2_110_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_110_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_109		(BIT13)
	#define		ECM_ECMINCFG2_3_IE2_109_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_109_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_108		(BIT12)
	#define		ECM_ECMINCFG2_3_IE2_108_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_108_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_107		(BIT11)
	#define		ECM_ECMINCFG2_3_IE2_107_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_107_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_106		(BIT10)
	#define		ECM_ECMINCFG2_3_IE2_106_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_106_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_105		(BIT9)
	#define		ECM_ECMINCFG2_3_IE2_105_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_105_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_104		(BIT8)
	#define		ECM_ECMINCFG2_3_IE2_104_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_104_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_103		(BIT7)
	#define		ECM_ECMINCFG2_3_IE2_103_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_103_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_102		(BIT6)
	#define		ECM_ECMINCFG2_3_IE2_102_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_102_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_101		(BIT5)
	#define		ECM_ECMINCFG2_3_IE2_101_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_101_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_100		(BIT4)
	#define		ECM_ECMINCFG2_3_IE2_100_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_100_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_099		(BIT3)
	#define		ECM_ECMINCFG2_3_IE2_099_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_099_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_098		(BIT2)
	#define		ECM_ECMINCFG2_3_IE2_098_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_098_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_097		(BIT1)
	#define		ECM_ECMINCFG2_3_IE2_097_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_097_ENABLE		(1)
#define		ECM_ECMINCFG2_3_IE2_096		(BIT0)
	#define		ECM_ECMINCFG2_3_IE2_096_DISABLE	(0)
	#define		ECM_ECMINCFG2_3_IE2_096_ENABLE		(1)

/* ECMINCFG2_4 */
#define		ECM_ECMINCFG2_4_IE2_159		(BIT31)
	#define		ECM_ECMINCFG2_4_IE2_159_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_159_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_158		(BIT30)
	#define		ECM_ECMINCFG2_4_IE2_158_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_158_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_157		(BIT29)
	#define		ECM_ECMINCFG2_4_IE2_157_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_157_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_156		(BIT28)
	#define		ECM_ECMINCFG2_4_IE2_156_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_156_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_155		(BIT27)
	#define		ECM_ECMINCFG2_4_IE2_155_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_155_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_154		(BIT26)
	#define		ECM_ECMINCFG2_4_IE2_154_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_154_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_153		(BIT25)
	#define		ECM_ECMINCFG2_4_IE2_153_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_153_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_152		(BIT24)
	#define		ECM_ECMINCFG2_4_IE2_152_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_152_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_151		(BIT23)
	#define		ECM_ECMINCFG2_4_IE2_151_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_151_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_150		(BIT22)
	#define		ECM_ECMINCFG2_4_IE2_150_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_150_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_149		(BIT21)
	#define		ECM_ECMINCFG2_4_IE2_149_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_149_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_148		(BIT20)
	#define		ECM_ECMINCFG2_4_IE2_148_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_148_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_147		(BIT19)
	#define		ECM_ECMINCFG2_4_IE2_147_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_147_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_146		(BIT18)
	#define		ECM_ECMINCFG2_4_IE2_146_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_146_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_145		(BIT17)
	#define		ECM_ECMINCFG2_4_IE2_145_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_145_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_144		(BIT16)
	#define		ECM_ECMINCFG2_4_IE2_144_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_144_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_143		(BIT15)
	#define		ECM_ECMINCFG2_4_IE2_143_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_143_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_142		(BIT14)
	#define		ECM_ECMINCFG2_4_IE2_142_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_142_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_141		(BIT13)
	#define		ECM_ECMINCFG2_4_IE2_141_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_141_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_140		(BIT12)
	#define		ECM_ECMINCFG2_4_IE2_140_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_140_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_139		(BIT11)
	#define		ECM_ECMINCFG2_4_IE2_139_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_139_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_138		(BIT10)
	#define		ECM_ECMINCFG2_4_IE2_138_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_138_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_137		(BIT9)
	#define		ECM_ECMINCFG2_4_IE2_137_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_137_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_136		(BIT8)
	#define		ECM_ECMINCFG2_4_IE2_136_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_136_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_135		(BIT7)
	#define		ECM_ECMINCFG2_4_IE2_135_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_135_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_134		(BIT6)
	#define		ECM_ECMINCFG2_4_IE2_134_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_134_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_133		(BIT5)
	#define		ECM_ECMINCFG2_4_IE2_133_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_133_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_132		(BIT4)
	#define		ECM_ECMINCFG2_4_IE2_132_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_132_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_131		(BIT3)
	#define		ECM_ECMINCFG2_4_IE2_131_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_131_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_130		(BIT2)
	#define		ECM_ECMINCFG2_4_IE2_130_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_130_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_129		(BIT1)
	#define		ECM_ECMINCFG2_4_IE2_129_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_129_ENABLE		(1)
#define		ECM_ECMINCFG2_4_IE2_128		(BIT0)
	#define		ECM_ECMINCFG2_4_IE2_128_DISABLE	(0)
	#define		ECM_ECMINCFG2_4_IE2_128_ENABLE		(1)

/* ECMINCFG2_5 */
#define		ECM_ECMINCFG2_5_IE2_191		(BIT31)
	#define		ECM_ECMINCFG2_5_IE2_191_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_191_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_190		(BIT30)
	#define		ECM_ECMINCFG2_5_IE2_190_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_190_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_189		(BIT29)
	#define		ECM_ECMINCFG2_5_IE2_189_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_189_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_188		(BIT28)
	#define		ECM_ECMINCFG2_5_IE2_188_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_188_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_187		(BIT27)
	#define		ECM_ECMINCFG2_5_IE2_187_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_187_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_186		(BIT26)
	#define		ECM_ECMINCFG2_5_IE2_186_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_186_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_185		(BIT25)
	#define		ECM_ECMINCFG2_5_IE2_185_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_185_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_184		(BIT24)
	#define		ECM_ECMINCFG2_5_IE2_184_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_184_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_183		(BIT23)
	#define		ECM_ECMINCFG2_5_IE2_183_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_183_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_182		(BIT22)
	#define		ECM_ECMINCFG2_5_IE2_182_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_182_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_181		(BIT21)
	#define		ECM_ECMINCFG2_5_IE2_181_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_181_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_180		(BIT20)
	#define		ECM_ECMINCFG2_5_IE2_180_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_180_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_179		(BIT19)
	#define		ECM_ECMINCFG2_5_IE2_179_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_179_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_178		(BIT18)
	#define		ECM_ECMINCFG2_5_IE2_178_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_178_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_177		(BIT17)
	#define		ECM_ECMINCFG2_5_IE2_177_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_177_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_176		(BIT16)
	#define		ECM_ECMINCFG2_5_IE2_176_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_176_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_175		(BIT15)
	#define		ECM_ECMINCFG2_5_IE2_175_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_175_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_174		(BIT14)
	#define		ECM_ECMINCFG2_5_IE2_174_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_174_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_173		(BIT13)
	#define		ECM_ECMINCFG2_5_IE2_173_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_173_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_172		(BIT12)
	#define		ECM_ECMINCFG2_5_IE2_172_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_172_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_171		(BIT11)
	#define		ECM_ECMINCFG2_5_IE2_171_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_171_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_170		(BIT10)
	#define		ECM_ECMINCFG2_5_IE2_170_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_170_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_169		(BIT9)
	#define		ECM_ECMINCFG2_5_IE2_169_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_169_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_168		(BIT8)
	#define		ECM_ECMINCFG2_5_IE2_168_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_168_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_167		(BIT7)
	#define		ECM_ECMINCFG2_5_IE2_167_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_167_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_166		(BIT6)
	#define		ECM_ECMINCFG2_5_IE2_166_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_166_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_165		(BIT5)
	#define		ECM_ECMINCFG2_5_IE2_165_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_165_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_164		(BIT4)
	#define		ECM_ECMINCFG2_5_IE2_164_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_164_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_163		(BIT3)
	#define		ECM_ECMINCFG2_5_IE2_163_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_163_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_162		(BIT2)
	#define		ECM_ECMINCFG2_5_IE2_162_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_162_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_161		(BIT1)
	#define		ECM_ECMINCFG2_5_IE2_161_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_161_ENABLE		(1)
#define		ECM_ECMINCFG2_5_IE2_160		(BIT0)
	#define		ECM_ECMINCFG2_5_IE2_160_DISABLE	(0)
	#define		ECM_ECMINCFG2_5_IE2_160_ENABLE		(1)

/* ECMINCFG2_6 */
#define		ECM_ECMINCFG2_6_IE2_223		(BIT31)
	#define		ECM_ECMINCFG2_6_IE2_223_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_223_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_222		(BIT30)
	#define		ECM_ECMINCFG2_6_IE2_222_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_222_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_221		(BIT29)
	#define		ECM_ECMINCFG2_6_IE2_221_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_221_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_220		(BIT28)
	#define		ECM_ECMINCFG2_6_IE2_220_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_220_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_219		(BIT27)
	#define		ECM_ECMINCFG2_6_IE2_219_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_219_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_218		(BIT26)
	#define		ECM_ECMINCFG2_6_IE2_218_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_218_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_217		(BIT25)
	#define		ECM_ECMINCFG2_6_IE2_217_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_217_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_216		(BIT24)
	#define		ECM_ECMINCFG2_6_IE2_216_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_216_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_215		(BIT23)
	#define		ECM_ECMINCFG2_6_IE2_215_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_215_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_214		(BIT22)
	#define		ECM_ECMINCFG2_6_IE2_214_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_214_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_213		(BIT21)
	#define		ECM_ECMINCFG2_6_IE2_213_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_213_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_212		(BIT20)
	#define		ECM_ECMINCFG2_6_IE2_212_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_212_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_211		(BIT19)
	#define		ECM_ECMINCFG2_6_IE2_211_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_211_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_210		(BIT18)
	#define		ECM_ECMINCFG2_6_IE2_210_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_210_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_209		(BIT17)
	#define		ECM_ECMINCFG2_6_IE2_209_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_209_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_208		(BIT16)
	#define		ECM_ECMINCFG2_6_IE2_208_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_208_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_207		(BIT15)
	#define		ECM_ECMINCFG2_6_IE2_207_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_207_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_206		(BIT14)
	#define		ECM_ECMINCFG2_6_IE2_206_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_206_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_205		(BIT13)
	#define		ECM_ECMINCFG2_6_IE2_205_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_205_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_204		(BIT12)
	#define		ECM_ECMINCFG2_6_IE2_204_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_204_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_203		(BIT11)
	#define		ECM_ECMINCFG2_6_IE2_203_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_203_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_202		(BIT10)
	#define		ECM_ECMINCFG2_6_IE2_202_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_202_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_201		(BIT9)
	#define		ECM_ECMINCFG2_6_IE2_201_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_201_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_200		(BIT8)
	#define		ECM_ECMINCFG2_6_IE2_200_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_200_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_199		(BIT7)
	#define		ECM_ECMINCFG2_6_IE2_199_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_199_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_198		(BIT6)
	#define		ECM_ECMINCFG2_6_IE2_198_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_198_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_197		(BIT5)
	#define		ECM_ECMINCFG2_6_IE2_197_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_197_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_196		(BIT4)
	#define		ECM_ECMINCFG2_6_IE2_196_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_196_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_195		(BIT3)
	#define		ECM_ECMINCFG2_6_IE2_195_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_195_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_194		(BIT2)
	#define		ECM_ECMINCFG2_6_IE2_194_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_194_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_193		(BIT1)
	#define		ECM_ECMINCFG2_6_IE2_193_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_193_ENABLE		(1)
#define		ECM_ECMINCFG2_6_IE2_192		(BIT0)
	#define		ECM_ECMINCFG2_6_IE2_192_DISABLE	(0)
	#define		ECM_ECMINCFG2_6_IE2_192_ENABLE		(1)

/* ECMINCFG2_7 */
#define		ECM_ECMINCFG2_7_IE2_255		(BIT31)
	#define		ECM_ECMINCFG2_7_IE2_255_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_255_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_254		(BIT30)
	#define		ECM_ECMINCFG2_7_IE2_254_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_254_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_253		(BIT29)
	#define		ECM_ECMINCFG2_7_IE2_253_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_253_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_252		(BIT28)
	#define		ECM_ECMINCFG2_7_IE2_252_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_252_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_251		(BIT27)
	#define		ECM_ECMINCFG2_7_IE2_251_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_251_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_250		(BIT26)
	#define		ECM_ECMINCFG2_7_IE2_250_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_250_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_249		(BIT25)
	#define		ECM_ECMINCFG2_7_IE2_249_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_249_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_248		(BIT24)
	#define		ECM_ECMINCFG2_7_IE2_248_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_248_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_247		(BIT23)
	#define		ECM_ECMINCFG2_7_IE2_247_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_247_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_246		(BIT22)
	#define		ECM_ECMINCFG2_7_IE2_246_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_246_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_245		(BIT21)
	#define		ECM_ECMINCFG2_7_IE2_245_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_245_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_244		(BIT20)
	#define		ECM_ECMINCFG2_7_IE2_244_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_244_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_243		(BIT19)
	#define		ECM_ECMINCFG2_7_IE2_243_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_243_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_242		(BIT18)
	#define		ECM_ECMINCFG2_7_IE2_242_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_242_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_241		(BIT17)
	#define		ECM_ECMINCFG2_7_IE2_241_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_241_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_240		(BIT16)
	#define		ECM_ECMINCFG2_7_IE2_240_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_240_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_239		(BIT15)
	#define		ECM_ECMINCFG2_7_IE2_239_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_239_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_238		(BIT14)
	#define		ECM_ECMINCFG2_7_IE2_238_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_238_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_237		(BIT13)
	#define		ECM_ECMINCFG2_7_IE2_237_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_237_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_236		(BIT12)
	#define		ECM_ECMINCFG2_7_IE2_236_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_236_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_235		(BIT11)
	#define		ECM_ECMINCFG2_7_IE2_235_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_235_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_234		(BIT10)
	#define		ECM_ECMINCFG2_7_IE2_234_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_234_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_233		(BIT9)
	#define		ECM_ECMINCFG2_7_IE2_233_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_233_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_232		(BIT8)
	#define		ECM_ECMINCFG2_7_IE2_232_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_232_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_231		(BIT7)
	#define		ECM_ECMINCFG2_7_IE2_231_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_231_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_230		(BIT6)
	#define		ECM_ECMINCFG2_7_IE2_230_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_230_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_229		(BIT5)
	#define		ECM_ECMINCFG2_7_IE2_229_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_229_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_228		(BIT4)
	#define		ECM_ECMINCFG2_7_IE2_228_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_228_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_227		(BIT3)
	#define		ECM_ECMINCFG2_7_IE2_227_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_227_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_226		(BIT2)
	#define		ECM_ECMINCFG2_7_IE2_226_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_226_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_225		(BIT1)
	#define		ECM_ECMINCFG2_7_IE2_225_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_225_ENABLE		(1)
#define		ECM_ECMINCFG2_7_IE2_224		(BIT0)
	#define		ECM_ECMINCFG2_7_IE2_224_DISABLE	(0)
	#define		ECM_ECMINCFG2_7_IE2_224_ENABLE		(1)

/* ECMINCFG2_8 */
#define		ECM_ECMINCFG2_8_IE2_287		(BIT31)
	#define		ECM_ECMINCFG2_8_IE2_287_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_287_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_286		(BIT30)
	#define		ECM_ECMINCFG2_8_IE2_286_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_286_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_285		(BIT29)
	#define		ECM_ECMINCFG2_8_IE2_285_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_285_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_284		(BIT28)
	#define		ECM_ECMINCFG2_8_IE2_284_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_284_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_283		(BIT27)
	#define		ECM_ECMINCFG2_8_IE2_283_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_283_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_282		(BIT26)
	#define		ECM_ECMINCFG2_8_IE2_282_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_282_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_281		(BIT25)
	#define		ECM_ECMINCFG2_8_IE2_281_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_281_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_280		(BIT24)
	#define		ECM_ECMINCFG2_8_IE2_280_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_280_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_279		(BIT23)
	#define		ECM_ECMINCFG2_8_IE2_279_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_279_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_278		(BIT22)
	#define		ECM_ECMINCFG2_8_IE2_278_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_278_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_277		(BIT21)
	#define		ECM_ECMINCFG2_8_IE2_277_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_277_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_276		(BIT20)
	#define		ECM_ECMINCFG2_8_IE2_276_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_276_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_275		(BIT19)
	#define		ECM_ECMINCFG2_8_IE2_275_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_275_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_274		(BIT18)
	#define		ECM_ECMINCFG2_8_IE2_274_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_274_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_273		(BIT17)
	#define		ECM_ECMINCFG2_8_IE2_273_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_273_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_272		(BIT16)
	#define		ECM_ECMINCFG2_8_IE2_272_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_272_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_271		(BIT15)
	#define		ECM_ECMINCFG2_8_IE2_271_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_271_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_270		(BIT14)
	#define		ECM_ECMINCFG2_8_IE2_270_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_270_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_269		(BIT13)
	#define		ECM_ECMINCFG2_8_IE2_269_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_269_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_268		(BIT12)
	#define		ECM_ECMINCFG2_8_IE2_268_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_268_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_267		(BIT11)
	#define		ECM_ECMINCFG2_8_IE2_267_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_267_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_266		(BIT10)
	#define		ECM_ECMINCFG2_8_IE2_266_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_266_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_265		(BIT9)
	#define		ECM_ECMINCFG2_8_IE2_265_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_265_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_264		(BIT8)
	#define		ECM_ECMINCFG2_8_IE2_264_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_264_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_263		(BIT7)
	#define		ECM_ECMINCFG2_8_IE2_263_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_263_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_262		(BIT6)
	#define		ECM_ECMINCFG2_8_IE2_262_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_262_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_261		(BIT5)
	#define		ECM_ECMINCFG2_8_IE2_261_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_261_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_260		(BIT4)
	#define		ECM_ECMINCFG2_8_IE2_260_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_260_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_259		(BIT3)
	#define		ECM_ECMINCFG2_8_IE2_259_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_259_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_258		(BIT2)
	#define		ECM_ECMINCFG2_8_IE2_258_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_258_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_257		(BIT1)
	#define		ECM_ECMINCFG2_8_IE2_257_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_257_ENABLE		(1)
#define		ECM_ECMINCFG2_8_IE2_256		(BIT0)
	#define		ECM_ECMINCFG2_8_IE2_256_DISABLE	(0)
	#define		ECM_ECMINCFG2_8_IE2_256_ENABLE		(1)

/* ECMINCFG2_9 */
#define		ECM_ECMINCFG2_9_IE2_319		(BIT31)
	#define		ECM_ECMINCFG2_9_IE2_319_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_319_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_318		(BIT30)
	#define		ECM_ECMINCFG2_9_IE2_318_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_318_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_317		(BIT29)
	#define		ECM_ECMINCFG2_9_IE2_317_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_317_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_316		(BIT28)
	#define		ECM_ECMINCFG2_9_IE2_316_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_316_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_315		(BIT27)
	#define		ECM_ECMINCFG2_9_IE2_315_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_315_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_314		(BIT26)
	#define		ECM_ECMINCFG2_9_IE2_314_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_314_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_313		(BIT25)
	#define		ECM_ECMINCFG2_9_IE2_313_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_313_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_312		(BIT24)
	#define		ECM_ECMINCFG2_9_IE2_312_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_312_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_311		(BIT23)
	#define		ECM_ECMINCFG2_9_IE2_311_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_311_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_310		(BIT22)
	#define		ECM_ECMINCFG2_9_IE2_310_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_310_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_309		(BIT21)
	#define		ECM_ECMINCFG2_9_IE2_309_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_309_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_308		(BIT20)
	#define		ECM_ECMINCFG2_9_IE2_308_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_308_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_307		(BIT19)
	#define		ECM_ECMINCFG2_9_IE2_307_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_307_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_306		(BIT18)
	#define		ECM_ECMINCFG2_9_IE2_306_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_306_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_305		(BIT17)
	#define		ECM_ECMINCFG2_9_IE2_305_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_305_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_304		(BIT16)
	#define		ECM_ECMINCFG2_9_IE2_304_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_304_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_303		(BIT15)
	#define		ECM_ECMINCFG2_9_IE2_303_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_303_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_302		(BIT14)
	#define		ECM_ECMINCFG2_9_IE2_302_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_302_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_301		(BIT13)
	#define		ECM_ECMINCFG2_9_IE2_301_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_301_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_300		(BIT12)
	#define		ECM_ECMINCFG2_9_IE2_300_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_300_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_299		(BIT11)
	#define		ECM_ECMINCFG2_9_IE2_299_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_299_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_298		(BIT10)
	#define		ECM_ECMINCFG2_9_IE2_298_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_298_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_297		(BIT9)
	#define		ECM_ECMINCFG2_9_IE2_297_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_297_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_296		(BIT8)
	#define		ECM_ECMINCFG2_9_IE2_296_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_296_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_295		(BIT7)
	#define		ECM_ECMINCFG2_9_IE2_295_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_295_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_294		(BIT6)
	#define		ECM_ECMINCFG2_9_IE2_294_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_294_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_293		(BIT5)
	#define		ECM_ECMINCFG2_9_IE2_293_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_293_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_292		(BIT4)
	#define		ECM_ECMINCFG2_9_IE2_292_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_292_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_291		(BIT3)
	#define		ECM_ECMINCFG2_9_IE2_291_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_291_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_290		(BIT2)
	#define		ECM_ECMINCFG2_9_IE2_290_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_290_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_289		(BIT1)
	#define		ECM_ECMINCFG2_9_IE2_289_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_289_ENABLE		(1)
#define		ECM_ECMINCFG2_9_IE2_288		(BIT0)
	#define		ECM_ECMINCFG2_9_IE2_288_DISABLE	(0)
	#define		ECM_ECMINCFG2_9_IE2_288_ENABLE		(1)

/* ECMINCFG2_10 */
#define		ECM_ECMINCFG2_10_IE2_351		(BIT31)
	#define		ECM_ECMINCFG2_10_IE2_351_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_351_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_350		(BIT30)
	#define		ECM_ECMINCFG2_10_IE2_350_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_350_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_349		(BIT29)
	#define		ECM_ECMINCFG2_10_IE2_349_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_349_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_348		(BIT28)
	#define		ECM_ECMINCFG2_10_IE2_348_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_348_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_347		(BIT27)
	#define		ECM_ECMINCFG2_10_IE2_347_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_347_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_346		(BIT26)
	#define		ECM_ECMINCFG2_10_IE2_346_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_346_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_345		(BIT25)
	#define		ECM_ECMINCFG2_10_IE2_345_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_345_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_344		(BIT24)
	#define		ECM_ECMINCFG2_10_IE2_344_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_344_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_343		(BIT23)
	#define		ECM_ECMINCFG2_10_IE2_343_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_343_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_342		(BIT22)
	#define		ECM_ECMINCFG2_10_IE2_342_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_342_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_341		(BIT21)
	#define		ECM_ECMINCFG2_10_IE2_341_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_341_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_340		(BIT20)
	#define		ECM_ECMINCFG2_10_IE2_340_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_340_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_339		(BIT19)
	#define		ECM_ECMINCFG2_10_IE2_339_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_339_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_338		(BIT18)
	#define		ECM_ECMINCFG2_10_IE2_338_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_338_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_337		(BIT17)
	#define		ECM_ECMINCFG2_10_IE2_337_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_337_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_336		(BIT16)
	#define		ECM_ECMINCFG2_10_IE2_336_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_336_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_335		(BIT15)
	#define		ECM_ECMINCFG2_10_IE2_335_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_335_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_334		(BIT14)
	#define		ECM_ECMINCFG2_10_IE2_334_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_334_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_333		(BIT13)
	#define		ECM_ECMINCFG2_10_IE2_333_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_333_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_332		(BIT12)
	#define		ECM_ECMINCFG2_10_IE2_332_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_332_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_331		(BIT11)
	#define		ECM_ECMINCFG2_10_IE2_331_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_331_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_330		(BIT10)
	#define		ECM_ECMINCFG2_10_IE2_330_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_330_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_329		(BIT9)
	#define		ECM_ECMINCFG2_10_IE2_329_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_329_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_328		(BIT8)
	#define		ECM_ECMINCFG2_10_IE2_328_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_328_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_327		(BIT7)
	#define		ECM_ECMINCFG2_10_IE2_327_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_327_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_326		(BIT6)
	#define		ECM_ECMINCFG2_10_IE2_326_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_326_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_325		(BIT5)
	#define		ECM_ECMINCFG2_10_IE2_325_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_325_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_324		(BIT4)
	#define		ECM_ECMINCFG2_10_IE2_324_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_324_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_323		(BIT3)
	#define		ECM_ECMINCFG2_10_IE2_323_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_323_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_322		(BIT2)
	#define		ECM_ECMINCFG2_10_IE2_322_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_322_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_321		(BIT1)
	#define		ECM_ECMINCFG2_10_IE2_321_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_321_ENABLE		(1)
#define		ECM_ECMINCFG2_10_IE2_320		(BIT0)
	#define		ECM_ECMINCFG2_10_IE2_320_DISABLE	(0)
	#define		ECM_ECMINCFG2_10_IE2_320_ENABLE		(1)

/* ECMINCFG3_0 */
#define		ECM_ECMINCFG3_0_IE3_031		(BIT31)
	#define		ECM_ECMINCFG3_0_IE3_031_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_031_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_030		(BIT30)
	#define		ECM_ECMINCFG3_0_IE3_030_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_030_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_029		(BIT29)
	#define		ECM_ECMINCFG3_0_IE3_029_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_029_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_028		(BIT28)
	#define		ECM_ECMINCFG3_0_IE3_028_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_028_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_027		(BIT27)
	#define		ECM_ECMINCFG3_0_IE3_027_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_027_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_026		(BIT26)
	#define		ECM_ECMINCFG3_0_IE3_026_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_026_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_025		(BIT25)
	#define		ECM_ECMINCFG3_0_IE3_025_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_025_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_024		(BIT24)
	#define		ECM_ECMINCFG3_0_IE3_024_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_024_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_023		(BIT23)
	#define		ECM_ECMINCFG3_0_IE3_023_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_023_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_022		(BIT22)
	#define		ECM_ECMINCFG3_0_IE3_022_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_022_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_021		(BIT21)
	#define		ECM_ECMINCFG3_0_IE3_021_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_021_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_020		(BIT20)
	#define		ECM_ECMINCFG3_0_IE3_020_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_020_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_019		(BIT19)
	#define		ECM_ECMINCFG3_0_IE3_019_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_019_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_018		(BIT18)
	#define		ECM_ECMINCFG3_0_IE3_018_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_018_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_017		(BIT17)
	#define		ECM_ECMINCFG3_0_IE3_017_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_017_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_016		(BIT16)
	#define		ECM_ECMINCFG3_0_IE3_016_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_016_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_015		(BIT15)
	#define		ECM_ECMINCFG3_0_IE3_015_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_015_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_014		(BIT14)
	#define		ECM_ECMINCFG3_0_IE3_014_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_014_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_013		(BIT13)
	#define		ECM_ECMINCFG3_0_IE3_013_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_013_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_012		(BIT12)
	#define		ECM_ECMINCFG3_0_IE3_012_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_012_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_011		(BIT11)
	#define		ECM_ECMINCFG3_0_IE3_011_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_011_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_010		(BIT10)
	#define		ECM_ECMINCFG3_0_IE3_010_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_010_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_009		(BIT9)
	#define		ECM_ECMINCFG3_0_IE3_009_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_009_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_008		(BIT8)
	#define		ECM_ECMINCFG3_0_IE3_008_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_008_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_007		(BIT7)
	#define		ECM_ECMINCFG3_0_IE3_007_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_007_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_006		(BIT6)
	#define		ECM_ECMINCFG3_0_IE3_006_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_006_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_005		(BIT5)
	#define		ECM_ECMINCFG3_0_IE3_005_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_005_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_004		(BIT4)
	#define		ECM_ECMINCFG3_0_IE3_004_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_004_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_003		(BIT3)
	#define		ECM_ECMINCFG3_0_IE3_003_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_003_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_002		(BIT2)
	#define		ECM_ECMINCFG3_0_IE3_002_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_002_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_001		(BIT1)
	#define		ECM_ECMINCFG3_0_IE3_001_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_001_ENABLE		(1)
#define		ECM_ECMINCFG3_0_IE3_000		(BIT0)
	#define		ECM_ECMINCFG3_0_IE3_000_DISABLE	(0)
	#define		ECM_ECMINCFG3_0_IE3_000_ENABLE		(1)

/* ECMINCFG3_1 */
#define		ECM_ECMINCFG3_1_IE3_063		(BIT31)
	#define		ECM_ECMINCFG3_1_IE3_063_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_063_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_062		(BIT30)
	#define		ECM_ECMINCFG3_1_IE3_062_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_062_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_061		(BIT29)
	#define		ECM_ECMINCFG3_1_IE3_061_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_061_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_060		(BIT28)
	#define		ECM_ECMINCFG3_1_IE3_060_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_060_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_059		(BIT27)
	#define		ECM_ECMINCFG3_1_IE3_059_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_059_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_058		(BIT26)
	#define		ECM_ECMINCFG3_1_IE3_058_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_058_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_057		(BIT25)
	#define		ECM_ECMINCFG3_1_IE3_057_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_057_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_056		(BIT24)
	#define		ECM_ECMINCFG3_1_IE3_056_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_056_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_055		(BIT23)
	#define		ECM_ECMINCFG3_1_IE3_055_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_055_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_054		(BIT22)
	#define		ECM_ECMINCFG3_1_IE3_054_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_054_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_053		(BIT21)
	#define		ECM_ECMINCFG3_1_IE3_053_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_053_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_052		(BIT20)
	#define		ECM_ECMINCFG3_1_IE3_052_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_052_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_051		(BIT19)
	#define		ECM_ECMINCFG3_1_IE3_051_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_051_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_050		(BIT18)
	#define		ECM_ECMINCFG3_1_IE3_050_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_050_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_049		(BIT17)
	#define		ECM_ECMINCFG3_1_IE3_049_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_049_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_048		(BIT16)
	#define		ECM_ECMINCFG3_1_IE3_048_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_048_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_047		(BIT15)
	#define		ECM_ECMINCFG3_1_IE3_047_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_047_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_046		(BIT14)
	#define		ECM_ECMINCFG3_1_IE3_046_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_046_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_045		(BIT13)
	#define		ECM_ECMINCFG3_1_IE3_045_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_045_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_044		(BIT12)
	#define		ECM_ECMINCFG3_1_IE3_044_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_044_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_043		(BIT11)
	#define		ECM_ECMINCFG3_1_IE3_043_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_043_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_042		(BIT10)
	#define		ECM_ECMINCFG3_1_IE3_042_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_042_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_041		(BIT9)
	#define		ECM_ECMINCFG3_1_IE3_041_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_041_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_040		(BIT8)
	#define		ECM_ECMINCFG3_1_IE3_040_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_040_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_039		(BIT7)
	#define		ECM_ECMINCFG3_1_IE3_039_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_039_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_038		(BIT6)
	#define		ECM_ECMINCFG3_1_IE3_038_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_038_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_037		(BIT5)
	#define		ECM_ECMINCFG3_1_IE3_037_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_037_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_036		(BIT4)
	#define		ECM_ECMINCFG3_1_IE3_036_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_036_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_035		(BIT3)
	#define		ECM_ECMINCFG3_1_IE3_035_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_035_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_034		(BIT2)
	#define		ECM_ECMINCFG3_1_IE3_034_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_034_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_033		(BIT1)
	#define		ECM_ECMINCFG3_1_IE3_033_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_033_ENABLE		(1)
#define		ECM_ECMINCFG3_1_IE3_032		(BIT0)
	#define		ECM_ECMINCFG3_1_IE3_032_DISABLE	(0)
	#define		ECM_ECMINCFG3_1_IE3_032_ENABLE		(1)

/* ECMINCFG3_2 */
#define		ECM_ECMINCFG3_2_IE3_095		(BIT31)
	#define		ECM_ECMINCFG3_2_IE3_095_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_095_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_094		(BIT30)
	#define		ECM_ECMINCFG3_2_IE3_094_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_094_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_093		(BIT29)
	#define		ECM_ECMINCFG3_2_IE3_093_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_093_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_092		(BIT28)
	#define		ECM_ECMINCFG3_2_IE3_092_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_092_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_091		(BIT27)
	#define		ECM_ECMINCFG3_2_IE3_091_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_091_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_090		(BIT26)
	#define		ECM_ECMINCFG3_2_IE3_090_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_090_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_089		(BIT25)
	#define		ECM_ECMINCFG3_2_IE3_089_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_089_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_088		(BIT24)
	#define		ECM_ECMINCFG3_2_IE3_088_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_088_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_087		(BIT23)
	#define		ECM_ECMINCFG3_2_IE3_087_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_087_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_086		(BIT22)
	#define		ECM_ECMINCFG3_2_IE3_086_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_086_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_085		(BIT21)
	#define		ECM_ECMINCFG3_2_IE3_085_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_085_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_084		(BIT20)
	#define		ECM_ECMINCFG3_2_IE3_084_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_084_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_083		(BIT19)
	#define		ECM_ECMINCFG3_2_IE3_083_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_083_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_082		(BIT18)
	#define		ECM_ECMINCFG3_2_IE3_082_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_082_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_081		(BIT17)
	#define		ECM_ECMINCFG3_2_IE3_081_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_081_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_080		(BIT16)
	#define		ECM_ECMINCFG3_2_IE3_080_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_080_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_079		(BIT15)
	#define		ECM_ECMINCFG3_2_IE3_079_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_079_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_078		(BIT14)
	#define		ECM_ECMINCFG3_2_IE3_078_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_078_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_077		(BIT13)
	#define		ECM_ECMINCFG3_2_IE3_077_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_077_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_076		(BIT12)
	#define		ECM_ECMINCFG3_2_IE3_076_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_076_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_075		(BIT11)
	#define		ECM_ECMINCFG3_2_IE3_075_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_075_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_074		(BIT10)
	#define		ECM_ECMINCFG3_2_IE3_074_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_074_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_073		(BIT9)
	#define		ECM_ECMINCFG3_2_IE3_073_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_073_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_072		(BIT8)
	#define		ECM_ECMINCFG3_2_IE3_072_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_072_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_071		(BIT7)
	#define		ECM_ECMINCFG3_2_IE3_071_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_071_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_070		(BIT6)
	#define		ECM_ECMINCFG3_2_IE3_070_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_070_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_069		(BIT5)
	#define		ECM_ECMINCFG3_2_IE3_069_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_069_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_068		(BIT4)
	#define		ECM_ECMINCFG3_2_IE3_068_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_068_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_067		(BIT3)
	#define		ECM_ECMINCFG3_2_IE3_067_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_067_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_066		(BIT2)
	#define		ECM_ECMINCFG3_2_IE3_066_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_066_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_065		(BIT1)
	#define		ECM_ECMINCFG3_2_IE3_065_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_065_ENABLE		(1)
#define		ECM_ECMINCFG3_2_IE3_064		(BIT0)
	#define		ECM_ECMINCFG3_2_IE3_064_DISABLE	(0)
	#define		ECM_ECMINCFG3_2_IE3_064_ENABLE		(1)

/* ECMINCFG3_3 */
#define		ECM_ECMINCFG3_3_IE3_127		(BIT31)
	#define		ECM_ECMINCFG3_3_IE3_127_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_127_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_126		(BIT30)
	#define		ECM_ECMINCFG3_3_IE3_126_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_126_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_125		(BIT29)
	#define		ECM_ECMINCFG3_3_IE3_125_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_125_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_124		(BIT28)
	#define		ECM_ECMINCFG3_3_IE3_124_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_124_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_123		(BIT27)
	#define		ECM_ECMINCFG3_3_IE3_123_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_123_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_122		(BIT26)
	#define		ECM_ECMINCFG3_3_IE3_122_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_122_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_121		(BIT25)
	#define		ECM_ECMINCFG3_3_IE3_121_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_121_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_120		(BIT24)
	#define		ECM_ECMINCFG3_3_IE3_120_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_120_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_119		(BIT23)
	#define		ECM_ECMINCFG3_3_IE3_119_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_119_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_118		(BIT22)
	#define		ECM_ECMINCFG3_3_IE3_118_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_118_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_117		(BIT21)
	#define		ECM_ECMINCFG3_3_IE3_117_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_117_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_116		(BIT20)
	#define		ECM_ECMINCFG3_3_IE3_116_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_116_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_115		(BIT19)
	#define		ECM_ECMINCFG3_3_IE3_115_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_115_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_114		(BIT18)
	#define		ECM_ECMINCFG3_3_IE3_114_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_114_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_113		(BIT17)
	#define		ECM_ECMINCFG3_3_IE3_113_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_113_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_112		(BIT16)
	#define		ECM_ECMINCFG3_3_IE3_112_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_112_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_111		(BIT15)
	#define		ECM_ECMINCFG3_3_IE3_111_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_111_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_110		(BIT14)
	#define		ECM_ECMINCFG3_3_IE3_110_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_110_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_109		(BIT13)
	#define		ECM_ECMINCFG3_3_IE3_109_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_109_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_108		(BIT12)
	#define		ECM_ECMINCFG3_3_IE3_108_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_108_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_107		(BIT11)
	#define		ECM_ECMINCFG3_3_IE3_107_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_107_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_106		(BIT10)
	#define		ECM_ECMINCFG3_3_IE3_106_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_106_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_105		(BIT9)
	#define		ECM_ECMINCFG3_3_IE3_105_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_105_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_104		(BIT8)
	#define		ECM_ECMINCFG3_3_IE3_104_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_104_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_103		(BIT7)
	#define		ECM_ECMINCFG3_3_IE3_103_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_103_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_102		(BIT6)
	#define		ECM_ECMINCFG3_3_IE3_102_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_102_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_101		(BIT5)
	#define		ECM_ECMINCFG3_3_IE3_101_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_101_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_100		(BIT4)
	#define		ECM_ECMINCFG3_3_IE3_100_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_100_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_099		(BIT3)
	#define		ECM_ECMINCFG3_3_IE3_099_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_099_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_098		(BIT2)
	#define		ECM_ECMINCFG3_3_IE3_098_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_098_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_097		(BIT1)
	#define		ECM_ECMINCFG3_3_IE3_097_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_097_ENABLE		(1)
#define		ECM_ECMINCFG3_3_IE3_096		(BIT0)
	#define		ECM_ECMINCFG3_3_IE3_096_DISABLE	(0)
	#define		ECM_ECMINCFG3_3_IE3_096_ENABLE		(1)

/* ECMINCFG3_4 */
#define		ECM_ECMINCFG3_4_IE3_159		(BIT31)
	#define		ECM_ECMINCFG3_4_IE3_159_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_159_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_158		(BIT30)
	#define		ECM_ECMINCFG3_4_IE3_158_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_158_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_157		(BIT29)
	#define		ECM_ECMINCFG3_4_IE3_157_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_157_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_156		(BIT28)
	#define		ECM_ECMINCFG3_4_IE3_156_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_156_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_155		(BIT27)
	#define		ECM_ECMINCFG3_4_IE3_155_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_155_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_154		(BIT26)
	#define		ECM_ECMINCFG3_4_IE3_154_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_154_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_153		(BIT25)
	#define		ECM_ECMINCFG3_4_IE3_153_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_153_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_152		(BIT24)
	#define		ECM_ECMINCFG3_4_IE3_152_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_152_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_151		(BIT23)
	#define		ECM_ECMINCFG3_4_IE3_151_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_151_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_150		(BIT22)
	#define		ECM_ECMINCFG3_4_IE3_150_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_150_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_149		(BIT21)
	#define		ECM_ECMINCFG3_4_IE3_149_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_149_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_148		(BIT20)
	#define		ECM_ECMINCFG3_4_IE3_148_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_148_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_147		(BIT19)
	#define		ECM_ECMINCFG3_4_IE3_147_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_147_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_146		(BIT18)
	#define		ECM_ECMINCFG3_4_IE3_146_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_146_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_145		(BIT17)
	#define		ECM_ECMINCFG3_4_IE3_145_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_145_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_144		(BIT16)
	#define		ECM_ECMINCFG3_4_IE3_144_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_144_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_143		(BIT15)
	#define		ECM_ECMINCFG3_4_IE3_143_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_143_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_142		(BIT14)
	#define		ECM_ECMINCFG3_4_IE3_142_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_142_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_141		(BIT13)
	#define		ECM_ECMINCFG3_4_IE3_141_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_141_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_140		(BIT12)
	#define		ECM_ECMINCFG3_4_IE3_140_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_140_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_139		(BIT11)
	#define		ECM_ECMINCFG3_4_IE3_139_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_139_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_138		(BIT10)
	#define		ECM_ECMINCFG3_4_IE3_138_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_138_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_137		(BIT9)
	#define		ECM_ECMINCFG3_4_IE3_137_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_137_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_136		(BIT8)
	#define		ECM_ECMINCFG3_4_IE3_136_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_136_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_135		(BIT7)
	#define		ECM_ECMINCFG3_4_IE3_135_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_135_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_134		(BIT6)
	#define		ECM_ECMINCFG3_4_IE3_134_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_134_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_133		(BIT5)
	#define		ECM_ECMINCFG3_4_IE3_133_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_133_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_132		(BIT4)
	#define		ECM_ECMINCFG3_4_IE3_132_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_132_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_131		(BIT3)
	#define		ECM_ECMINCFG3_4_IE3_131_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_131_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_130		(BIT2)
	#define		ECM_ECMINCFG3_4_IE3_130_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_130_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_129		(BIT1)
	#define		ECM_ECMINCFG3_4_IE3_129_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_129_ENABLE		(1)
#define		ECM_ECMINCFG3_4_IE3_128		(BIT0)
	#define		ECM_ECMINCFG3_4_IE3_128_DISABLE	(0)
	#define		ECM_ECMINCFG3_4_IE3_128_ENABLE		(1)

/* ECMINCFG3_5 */
#define		ECM_ECMINCFG3_5_IE3_191		(BIT31)
	#define		ECM_ECMINCFG3_5_IE3_191_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_191_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_190		(BIT30)
	#define		ECM_ECMINCFG3_5_IE3_190_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_190_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_189		(BIT29)
	#define		ECM_ECMINCFG3_5_IE3_189_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_189_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_188		(BIT28)
	#define		ECM_ECMINCFG3_5_IE3_188_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_188_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_187		(BIT27)
	#define		ECM_ECMINCFG3_5_IE3_187_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_187_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_186		(BIT26)
	#define		ECM_ECMINCFG3_5_IE3_186_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_186_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_185		(BIT25)
	#define		ECM_ECMINCFG3_5_IE3_185_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_185_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_184		(BIT24)
	#define		ECM_ECMINCFG3_5_IE3_184_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_184_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_183		(BIT23)
	#define		ECM_ECMINCFG3_5_IE3_183_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_183_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_182		(BIT22)
	#define		ECM_ECMINCFG3_5_IE3_182_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_182_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_181		(BIT21)
	#define		ECM_ECMINCFG3_5_IE3_181_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_181_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_180		(BIT20)
	#define		ECM_ECMINCFG3_5_IE3_180_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_180_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_179		(BIT19)
	#define		ECM_ECMINCFG3_5_IE3_179_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_179_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_178		(BIT18)
	#define		ECM_ECMINCFG3_5_IE3_178_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_178_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_177		(BIT17)
	#define		ECM_ECMINCFG3_5_IE3_177_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_177_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_176		(BIT16)
	#define		ECM_ECMINCFG3_5_IE3_176_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_176_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_175		(BIT15)
	#define		ECM_ECMINCFG3_5_IE3_175_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_175_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_174		(BIT14)
	#define		ECM_ECMINCFG3_5_IE3_174_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_174_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_173		(BIT13)
	#define		ECM_ECMINCFG3_5_IE3_173_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_173_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_172		(BIT12)
	#define		ECM_ECMINCFG3_5_IE3_172_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_172_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_171		(BIT11)
	#define		ECM_ECMINCFG3_5_IE3_171_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_171_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_170		(BIT10)
	#define		ECM_ECMINCFG3_5_IE3_170_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_170_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_169		(BIT9)
	#define		ECM_ECMINCFG3_5_IE3_169_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_169_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_168		(BIT8)
	#define		ECM_ECMINCFG3_5_IE3_168_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_168_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_167		(BIT7)
	#define		ECM_ECMINCFG3_5_IE3_167_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_167_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_166		(BIT6)
	#define		ECM_ECMINCFG3_5_IE3_166_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_166_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_165		(BIT5)
	#define		ECM_ECMINCFG3_5_IE3_165_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_165_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_164		(BIT4)
	#define		ECM_ECMINCFG3_5_IE3_164_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_164_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_163		(BIT3)
	#define		ECM_ECMINCFG3_5_IE3_163_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_163_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_162		(BIT2)
	#define		ECM_ECMINCFG3_5_IE3_162_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_162_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_161		(BIT1)
	#define		ECM_ECMINCFG3_5_IE3_161_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_161_ENABLE		(1)
#define		ECM_ECMINCFG3_5_IE3_160		(BIT0)
	#define		ECM_ECMINCFG3_5_IE3_160_DISABLE	(0)
	#define		ECM_ECMINCFG3_5_IE3_160_ENABLE		(1)

/* ECMINCFG3_6 */
#define		ECM_ECMINCFG3_6_IE3_223		(BIT31)
	#define		ECM_ECMINCFG3_6_IE3_223_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_223_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_222		(BIT30)
	#define		ECM_ECMINCFG3_6_IE3_222_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_222_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_221		(BIT29)
	#define		ECM_ECMINCFG3_6_IE3_221_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_221_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_220		(BIT28)
	#define		ECM_ECMINCFG3_6_IE3_220_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_220_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_219		(BIT27)
	#define		ECM_ECMINCFG3_6_IE3_219_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_219_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_218		(BIT26)
	#define		ECM_ECMINCFG3_6_IE3_218_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_218_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_217		(BIT25)
	#define		ECM_ECMINCFG3_6_IE3_217_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_217_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_216		(BIT24)
	#define		ECM_ECMINCFG3_6_IE3_216_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_216_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_215		(BIT23)
	#define		ECM_ECMINCFG3_6_IE3_215_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_215_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_214		(BIT22)
	#define		ECM_ECMINCFG3_6_IE3_214_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_214_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_213		(BIT21)
	#define		ECM_ECMINCFG3_6_IE3_213_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_213_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_212		(BIT20)
	#define		ECM_ECMINCFG3_6_IE3_212_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_212_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_211		(BIT19)
	#define		ECM_ECMINCFG3_6_IE3_211_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_211_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_210		(BIT18)
	#define		ECM_ECMINCFG3_6_IE3_210_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_210_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_209		(BIT17)
	#define		ECM_ECMINCFG3_6_IE3_209_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_209_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_208		(BIT16)
	#define		ECM_ECMINCFG3_6_IE3_208_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_208_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_207		(BIT15)
	#define		ECM_ECMINCFG3_6_IE3_207_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_207_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_206		(BIT14)
	#define		ECM_ECMINCFG3_6_IE3_206_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_206_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_205		(BIT13)
	#define		ECM_ECMINCFG3_6_IE3_205_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_205_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_204		(BIT12)
	#define		ECM_ECMINCFG3_6_IE3_204_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_204_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_203		(BIT11)
	#define		ECM_ECMINCFG3_6_IE3_203_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_203_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_202		(BIT10)
	#define		ECM_ECMINCFG3_6_IE3_202_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_202_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_201		(BIT9)
	#define		ECM_ECMINCFG3_6_IE3_201_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_201_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_200		(BIT8)
	#define		ECM_ECMINCFG3_6_IE3_200_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_200_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_199		(BIT7)
	#define		ECM_ECMINCFG3_6_IE3_199_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_199_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_198		(BIT6)
	#define		ECM_ECMINCFG3_6_IE3_198_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_198_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_197		(BIT5)
	#define		ECM_ECMINCFG3_6_IE3_197_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_197_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_196		(BIT4)
	#define		ECM_ECMINCFG3_6_IE3_196_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_196_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_195		(BIT3)
	#define		ECM_ECMINCFG3_6_IE3_195_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_195_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_194		(BIT2)
	#define		ECM_ECMINCFG3_6_IE3_194_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_194_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_193		(BIT1)
	#define		ECM_ECMINCFG3_6_IE3_193_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_193_ENABLE		(1)
#define		ECM_ECMINCFG3_6_IE3_192		(BIT0)
	#define		ECM_ECMINCFG3_6_IE3_192_DISABLE	(0)
	#define		ECM_ECMINCFG3_6_IE3_192_ENABLE		(1)

/* ECMINCFG3_7 */
#define		ECM_ECMINCFG3_7_IE3_255		(BIT31)
	#define		ECM_ECMINCFG3_7_IE3_255_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_255_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_254		(BIT30)
	#define		ECM_ECMINCFG3_7_IE3_254_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_254_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_253		(BIT29)
	#define		ECM_ECMINCFG3_7_IE3_253_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_253_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_252		(BIT28)
	#define		ECM_ECMINCFG3_7_IE3_252_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_252_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_251		(BIT27)
	#define		ECM_ECMINCFG3_7_IE3_251_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_251_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_250		(BIT26)
	#define		ECM_ECMINCFG3_7_IE3_250_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_250_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_249		(BIT25)
	#define		ECM_ECMINCFG3_7_IE3_249_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_249_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_248		(BIT24)
	#define		ECM_ECMINCFG3_7_IE3_248_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_248_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_247		(BIT23)
	#define		ECM_ECMINCFG3_7_IE3_247_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_247_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_246		(BIT22)
	#define		ECM_ECMINCFG3_7_IE3_246_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_246_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_245		(BIT21)
	#define		ECM_ECMINCFG3_7_IE3_245_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_245_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_244		(BIT20)
	#define		ECM_ECMINCFG3_7_IE3_244_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_244_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_243		(BIT19)
	#define		ECM_ECMINCFG3_7_IE3_243_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_243_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_242		(BIT18)
	#define		ECM_ECMINCFG3_7_IE3_242_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_242_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_241		(BIT17)
	#define		ECM_ECMINCFG3_7_IE3_241_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_241_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_240		(BIT16)
	#define		ECM_ECMINCFG3_7_IE3_240_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_240_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_239		(BIT15)
	#define		ECM_ECMINCFG3_7_IE3_239_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_239_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_238		(BIT14)
	#define		ECM_ECMINCFG3_7_IE3_238_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_238_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_237		(BIT13)
	#define		ECM_ECMINCFG3_7_IE3_237_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_237_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_236		(BIT12)
	#define		ECM_ECMINCFG3_7_IE3_236_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_236_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_235		(BIT11)
	#define		ECM_ECMINCFG3_7_IE3_235_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_235_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_234		(BIT10)
	#define		ECM_ECMINCFG3_7_IE3_234_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_234_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_233		(BIT9)
	#define		ECM_ECMINCFG3_7_IE3_233_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_233_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_232		(BIT8)
	#define		ECM_ECMINCFG3_7_IE3_232_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_232_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_231		(BIT7)
	#define		ECM_ECMINCFG3_7_IE3_231_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_231_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_230		(BIT6)
	#define		ECM_ECMINCFG3_7_IE3_230_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_230_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_229		(BIT5)
	#define		ECM_ECMINCFG3_7_IE3_229_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_229_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_228		(BIT4)
	#define		ECM_ECMINCFG3_7_IE3_228_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_228_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_227		(BIT3)
	#define		ECM_ECMINCFG3_7_IE3_227_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_227_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_226		(BIT2)
	#define		ECM_ECMINCFG3_7_IE3_226_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_226_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_225		(BIT1)
	#define		ECM_ECMINCFG3_7_IE3_225_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_225_ENABLE		(1)
#define		ECM_ECMINCFG3_7_IE3_224		(BIT0)
	#define		ECM_ECMINCFG3_7_IE3_224_DISABLE	(0)
	#define		ECM_ECMINCFG3_7_IE3_224_ENABLE		(1)

/* ECMINCFG3_8 */
#define		ECM_ECMINCFG3_8_IE3_287		(BIT31)
	#define		ECM_ECMINCFG3_8_IE3_287_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_287_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_286		(BIT30)
	#define		ECM_ECMINCFG3_8_IE3_286_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_286_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_285		(BIT29)
	#define		ECM_ECMINCFG3_8_IE3_285_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_285_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_284		(BIT28)
	#define		ECM_ECMINCFG3_8_IE3_284_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_284_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_283		(BIT27)
	#define		ECM_ECMINCFG3_8_IE3_283_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_283_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_282		(BIT26)
	#define		ECM_ECMINCFG3_8_IE3_282_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_282_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_281		(BIT25)
	#define		ECM_ECMINCFG3_8_IE3_281_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_281_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_280		(BIT24)
	#define		ECM_ECMINCFG3_8_IE3_280_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_280_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_279		(BIT23)
	#define		ECM_ECMINCFG3_8_IE3_279_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_279_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_278		(BIT22)
	#define		ECM_ECMINCFG3_8_IE3_278_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_278_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_277		(BIT21)
	#define		ECM_ECMINCFG3_8_IE3_277_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_277_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_276		(BIT20)
	#define		ECM_ECMINCFG3_8_IE3_276_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_276_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_275		(BIT19)
	#define		ECM_ECMINCFG3_8_IE3_275_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_275_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_274		(BIT18)
	#define		ECM_ECMINCFG3_8_IE3_274_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_274_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_273		(BIT17)
	#define		ECM_ECMINCFG3_8_IE3_273_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_273_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_272		(BIT16)
	#define		ECM_ECMINCFG3_8_IE3_272_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_272_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_271		(BIT15)
	#define		ECM_ECMINCFG3_8_IE3_271_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_271_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_270		(BIT14)
	#define		ECM_ECMINCFG3_8_IE3_270_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_270_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_269		(BIT13)
	#define		ECM_ECMINCFG3_8_IE3_269_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_269_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_268		(BIT12)
	#define		ECM_ECMINCFG3_8_IE3_268_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_268_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_267		(BIT11)
	#define		ECM_ECMINCFG3_8_IE3_267_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_267_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_266		(BIT10)
	#define		ECM_ECMINCFG3_8_IE3_266_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_266_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_265		(BIT9)
	#define		ECM_ECMINCFG3_8_IE3_265_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_265_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_264		(BIT8)
	#define		ECM_ECMINCFG3_8_IE3_264_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_264_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_263		(BIT7)
	#define		ECM_ECMINCFG3_8_IE3_263_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_263_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_262		(BIT6)
	#define		ECM_ECMINCFG3_8_IE3_262_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_262_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_261		(BIT5)
	#define		ECM_ECMINCFG3_8_IE3_261_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_261_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_260		(BIT4)
	#define		ECM_ECMINCFG3_8_IE3_260_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_260_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_259		(BIT3)
	#define		ECM_ECMINCFG3_8_IE3_259_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_259_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_258		(BIT2)
	#define		ECM_ECMINCFG3_8_IE3_258_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_258_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_257		(BIT1)
	#define		ECM_ECMINCFG3_8_IE3_257_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_257_ENABLE		(1)
#define		ECM_ECMINCFG3_8_IE3_256		(BIT0)
	#define		ECM_ECMINCFG3_8_IE3_256_DISABLE	(0)
	#define		ECM_ECMINCFG3_8_IE3_256_ENABLE		(1)

/* ECMINCFG3_9 */
#define		ECM_ECMINCFG3_9_IE3_319		(BIT31)
	#define		ECM_ECMINCFG3_9_IE3_319_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_319_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_318		(BIT30)
	#define		ECM_ECMINCFG3_9_IE3_318_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_318_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_317		(BIT29)
	#define		ECM_ECMINCFG3_9_IE3_317_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_317_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_316		(BIT28)
	#define		ECM_ECMINCFG3_9_IE3_316_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_316_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_315		(BIT27)
	#define		ECM_ECMINCFG3_9_IE3_315_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_315_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_314		(BIT26)
	#define		ECM_ECMINCFG3_9_IE3_314_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_314_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_313		(BIT25)
	#define		ECM_ECMINCFG3_9_IE3_313_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_313_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_312		(BIT24)
	#define		ECM_ECMINCFG3_9_IE3_312_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_312_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_311		(BIT23)
	#define		ECM_ECMINCFG3_9_IE3_311_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_311_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_310		(BIT22)
	#define		ECM_ECMINCFG3_9_IE3_310_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_310_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_309		(BIT21)
	#define		ECM_ECMINCFG3_9_IE3_309_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_309_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_308		(BIT20)
	#define		ECM_ECMINCFG3_9_IE3_308_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_308_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_307		(BIT19)
	#define		ECM_ECMINCFG3_9_IE3_307_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_307_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_306		(BIT18)
	#define		ECM_ECMINCFG3_9_IE3_306_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_306_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_305		(BIT17)
	#define		ECM_ECMINCFG3_9_IE3_305_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_305_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_304		(BIT16)
	#define		ECM_ECMINCFG3_9_IE3_304_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_304_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_303		(BIT15)
	#define		ECM_ECMINCFG3_9_IE3_303_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_303_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_302		(BIT14)
	#define		ECM_ECMINCFG3_9_IE3_302_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_302_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_301		(BIT13)
	#define		ECM_ECMINCFG3_9_IE3_301_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_301_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_300		(BIT12)
	#define		ECM_ECMINCFG3_9_IE3_300_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_300_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_299		(BIT11)
	#define		ECM_ECMINCFG3_9_IE3_299_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_299_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_298		(BIT10)
	#define		ECM_ECMINCFG3_9_IE3_298_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_298_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_297		(BIT9)
	#define		ECM_ECMINCFG3_9_IE3_297_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_297_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_296		(BIT8)
	#define		ECM_ECMINCFG3_9_IE3_296_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_296_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_295		(BIT7)
	#define		ECM_ECMINCFG3_9_IE3_295_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_295_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_294		(BIT6)
	#define		ECM_ECMINCFG3_9_IE3_294_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_294_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_293		(BIT5)
	#define		ECM_ECMINCFG3_9_IE3_293_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_293_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_292		(BIT4)
	#define		ECM_ECMINCFG3_9_IE3_292_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_292_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_291		(BIT3)
	#define		ECM_ECMINCFG3_9_IE3_291_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_291_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_290		(BIT2)
	#define		ECM_ECMINCFG3_9_IE3_290_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_290_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_289		(BIT1)
	#define		ECM_ECMINCFG3_9_IE3_289_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_289_ENABLE		(1)
#define		ECM_ECMINCFG3_9_IE3_288		(BIT0)
	#define		ECM_ECMINCFG3_9_IE3_288_DISABLE	(0)
	#define		ECM_ECMINCFG3_9_IE3_288_ENABLE		(1)

/* ECMINCFG3_10 */
#define		ECM_ECMINCFG3_10_IE3_351		(BIT31)
	#define		ECM_ECMINCFG3_10_IE3_351_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_351_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_350		(BIT30)
	#define		ECM_ECMINCFG3_10_IE3_350_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_350_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_349		(BIT29)
	#define		ECM_ECMINCFG3_10_IE3_349_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_349_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_348		(BIT28)
	#define		ECM_ECMINCFG3_10_IE3_348_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_348_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_347		(BIT27)
	#define		ECM_ECMINCFG3_10_IE3_347_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_347_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_346		(BIT26)
	#define		ECM_ECMINCFG3_10_IE3_346_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_346_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_345		(BIT25)
	#define		ECM_ECMINCFG3_10_IE3_345_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_345_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_344		(BIT24)
	#define		ECM_ECMINCFG3_10_IE3_344_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_344_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_343		(BIT23)
	#define		ECM_ECMINCFG3_10_IE3_343_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_343_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_342		(BIT22)
	#define		ECM_ECMINCFG3_10_IE3_342_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_342_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_341		(BIT21)
	#define		ECM_ECMINCFG3_10_IE3_341_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_341_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_340		(BIT20)
	#define		ECM_ECMINCFG3_10_IE3_340_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_340_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_339		(BIT19)
	#define		ECM_ECMINCFG3_10_IE3_339_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_339_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_338		(BIT18)
	#define		ECM_ECMINCFG3_10_IE3_338_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_338_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_337		(BIT17)
	#define		ECM_ECMINCFG3_10_IE3_337_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_337_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_336		(BIT16)
	#define		ECM_ECMINCFG3_10_IE3_336_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_336_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_335		(BIT15)
	#define		ECM_ECMINCFG3_10_IE3_335_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_335_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_334		(BIT14)
	#define		ECM_ECMINCFG3_10_IE3_334_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_334_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_333		(BIT13)
	#define		ECM_ECMINCFG3_10_IE3_333_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_333_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_332		(BIT12)
	#define		ECM_ECMINCFG3_10_IE3_332_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_332_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_331		(BIT11)
	#define		ECM_ECMINCFG3_10_IE3_331_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_331_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_330		(BIT10)
	#define		ECM_ECMINCFG3_10_IE3_330_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_330_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_329		(BIT9)
	#define		ECM_ECMINCFG3_10_IE3_329_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_329_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_328		(BIT8)
	#define		ECM_ECMINCFG3_10_IE3_328_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_328_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_327		(BIT7)
	#define		ECM_ECMINCFG3_10_IE3_327_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_327_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_326		(BIT6)
	#define		ECM_ECMINCFG3_10_IE3_326_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_326_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_325		(BIT5)
	#define		ECM_ECMINCFG3_10_IE3_325_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_325_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_324		(BIT4)
	#define		ECM_ECMINCFG3_10_IE3_324_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_324_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_323		(BIT3)
	#define		ECM_ECMINCFG3_10_IE3_323_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_323_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_322		(BIT2)
	#define		ECM_ECMINCFG3_10_IE3_322_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_322_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_321		(BIT1)
	#define		ECM_ECMINCFG3_10_IE3_321_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_321_ENABLE		(1)
#define		ECM_ECMINCFG3_10_IE3_320		(BIT0)
	#define		ECM_ECMINCFG3_10_IE3_320_DISABLE	(0)
	#define		ECM_ECMINCFG3_10_IE3_320_ENABLE		(1)

#define		ECM_ECMINCFG5_10_IE5_325		(BIT5)
	#define		ECM_ECMINCFG5_10_IE5_325_DISABLE	(0)
	#define		ECM_ECMINCFG5_10_IE5_325_ENABLE		(1)
#define		ECM_ECMINCFG5_10_IE5_324		(BIT4)
	#define		ECM_ECMINCFG5_10_IE5_324_DISABLE	(0)
	#define		ECM_ECMINCFG5_10_IE5_324_ENABLE		(1)
#define		ECM_ECMINCFG5_10_IE5_323		(BIT3)
	#define		ECM_ECMINCFG5_10_IE5_323_DISABLE	(0)
	#define		ECM_ECMINCFG5_10_IE5_323_ENABLE		(1)
#define		ECM_ECMINCFG5_10_IE5_322		(BIT2)
	#define		ECM_ECMINCFG5_10_IE5_322_DISABLE	(0)
	#define		ECM_ECMINCFG5_10_IE5_322_ENABLE		(1)
#define		ECM_ECMINCFG5_10_IE5_321		(BIT1)
	#define		ECM_ECMINCFG5_10_IE5_321_DISABLE	(0)
	#define		ECM_ECMINCFG5_10_IE5_321_ENABLE		(1)
#define		ECM_ECMINCFG5_10_IE5_320		(BIT0)
	#define		ECM_ECMINCFG5_10_IE5_320_DISABLE	(0)
	#define		ECM_ECMINCFG5_10_IE5_320_ENABLE		(1)

/* ECMIRCFG0 */
#define		ECM_ECMIRCFG0_IRE031		(BIT31)
	#define		ECM_ECMIRCFG0_IRE031_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE031_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE030		(BIT30)
	#define		ECM_ECMIRCFG0_IRE030_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE030_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE029		(BIT29)
	#define		ECM_ECMIRCFG0_IRE029_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE029_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE028		(BIT28)
	#define		ECM_ECMIRCFG0_IRE028_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE028_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE027		(BIT27)
	#define		ECM_ECMIRCFG0_IRE027_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE027_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE026		(BIT26)
	#define		ECM_ECMIRCFG0_IRE026_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE026_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE025		(BIT25)
	#define		ECM_ECMIRCFG0_IRE025_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE025_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE024		(BIT24)
	#define		ECM_ECMIRCFG0_IRE024_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE024_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE023		(BIT23)
	#define		ECM_ECMIRCFG0_IRE023_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE023_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE022		(BIT22)
	#define		ECM_ECMIRCFG0_IRE022_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE022_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE021		(BIT21)
	#define		ECM_ECMIRCFG0_IRE021_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE021_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE020		(BIT20)
	#define		ECM_ECMIRCFG0_IRE020_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE020_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE019		(BIT19)
	#define		ECM_ECMIRCFG0_IRE019_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE019_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE018		(BIT18)
	#define		ECM_ECMIRCFG0_IRE018_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE018_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE017		(BIT17)
	#define		ECM_ECMIRCFG0_IRE017_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE017_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE016		(BIT16)
	#define		ECM_ECMIRCFG0_IRE016_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE016_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE015		(BIT15)
	#define		ECM_ECMIRCFG0_IRE015_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE015_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE014		(BIT14)
	#define		ECM_ECMIRCFG0_IRE014_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE014_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE013		(BIT13)
	#define		ECM_ECMIRCFG0_IRE013_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE013_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE012		(BIT12)
	#define		ECM_ECMIRCFG0_IRE012_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE012_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE011		(BIT11)
	#define		ECM_ECMIRCFG0_IRE011_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE011_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE010		(BIT10)
	#define		ECM_ECMIRCFG0_IRE010_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE010_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE009		(BIT9)
	#define		ECM_ECMIRCFG0_IRE009_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE009_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE008		(BIT8)
	#define		ECM_ECMIRCFG0_IRE008_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE008_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE007		(BIT7)
	#define		ECM_ECMIRCFG0_IRE007_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE007_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE006		(BIT6)
	#define		ECM_ECMIRCFG0_IRE006_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE006_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE005		(BIT5)
	#define		ECM_ECMIRCFG0_IRE005_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE005_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE004		(BIT4)
	#define		ECM_ECMIRCFG0_IRE004_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE004_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE003		(BIT3)
	#define		ECM_ECMIRCFG0_IRE003_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE003_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE002		(BIT2)
	#define		ECM_ECMIRCFG0_IRE002_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE002_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE001		(BIT1)
	#define		ECM_ECMIRCFG0_IRE001_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE001_ENABLE		(1)
#define		ECM_ECMIRCFG0_IRE000		(BIT0)
	#define		ECM_ECMIRCFG0_IRE000_DISABLE	(0)
	#define		ECM_ECMIRCFG0_IRE000_ENABLE		(1)

/* ECMIRCFG1 */
#define		ECM_ECMIRCFG1_IRE063		(BIT31)
	#define		ECM_ECMIRCFG1_IRE063_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE063_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE062		(BIT30)
	#define		ECM_ECMIRCFG1_IRE062_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE062_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE061		(BIT29)
	#define		ECM_ECMIRCFG1_IRE061_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE061_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE060		(BIT28)
	#define		ECM_ECMIRCFG1_IRE060_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE060_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE059		(BIT27)
	#define		ECM_ECMIRCFG1_IRE059_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE059_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE058		(BIT26)
	#define		ECM_ECMIRCFG1_IRE058_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE058_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE057		(BIT25)
	#define		ECM_ECMIRCFG1_IRE057_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE057_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE056		(BIT24)
	#define		ECM_ECMIRCFG1_IRE056_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE056_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE055		(BIT23)
	#define		ECM_ECMIRCFG1_IRE055_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE055_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE054		(BIT22)
	#define		ECM_ECMIRCFG1_IRE054_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE054_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE053		(BIT21)
	#define		ECM_ECMIRCFG1_IRE053_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE053_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE052		(BIT20)
	#define		ECM_ECMIRCFG1_IRE052_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE052_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE051		(BIT19)
	#define		ECM_ECMIRCFG1_IRE051_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE051_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE050		(BIT18)
	#define		ECM_ECMIRCFG1_IRE050_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE050_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE049		(BIT17)
	#define		ECM_ECMIRCFG1_IRE049_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE049_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE048		(BIT16)
	#define		ECM_ECMIRCFG1_IRE048_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE048_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE047		(BIT15)
	#define		ECM_ECMIRCFG1_IRE047_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE047_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE046		(BIT14)
	#define		ECM_ECMIRCFG1_IRE046_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE046_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE045		(BIT13)
	#define		ECM_ECMIRCFG1_IRE045_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE045_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE044		(BIT12)
	#define		ECM_ECMIRCFG1_IRE044_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE044_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE043		(BIT11)
	#define		ECM_ECMIRCFG1_IRE043_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE043_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE042		(BIT10)
	#define		ECM_ECMIRCFG1_IRE042_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE042_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE041		(BIT9)
	#define		ECM_ECMIRCFG1_IRE041_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE041_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE040		(BIT8)
	#define		ECM_ECMIRCFG1_IRE040_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE040_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE039		(BIT7)
	#define		ECM_ECMIRCFG1_IRE039_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE039_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE038		(BIT6)
	#define		ECM_ECMIRCFG1_IRE038_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE038_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE037		(BIT5)
	#define		ECM_ECMIRCFG1_IRE037_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE037_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE036		(BIT4)
	#define		ECM_ECMIRCFG1_IRE036_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE036_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE035		(BIT3)
	#define		ECM_ECMIRCFG1_IRE035_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE035_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE034		(BIT2)
	#define		ECM_ECMIRCFG1_IRE034_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE034_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE033		(BIT1)
	#define		ECM_ECMIRCFG1_IRE033_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE033_ENABLE		(1)
#define		ECM_ECMIRCFG1_IRE032		(BIT0)
	#define		ECM_ECMIRCFG1_IRE032_DISABLE	(0)
	#define		ECM_ECMIRCFG1_IRE032_ENABLE		(1)

/* ECMIRCFG2 */
#define		ECM_ECMIRCFG2_IRE095		(BIT31)
	#define		ECM_ECMIRCFG2_IRE095_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE095_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE094		(BIT30)
	#define		ECM_ECMIRCFG2_IRE094_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE094_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE093		(BIT29)
	#define		ECM_ECMIRCFG2_IRE093_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE093_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE092		(BIT28)
	#define		ECM_ECMIRCFG2_IRE092_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE092_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE091		(BIT27)
	#define		ECM_ECMIRCFG2_IRE091_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE091_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE090		(BIT26)
	#define		ECM_ECMIRCFG2_IRE090_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE090_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE089		(BIT25)
	#define		ECM_ECMIRCFG2_IRE089_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE089_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE088		(BIT24)
	#define		ECM_ECMIRCFG2_IRE088_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE088_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE087		(BIT23)
	#define		ECM_ECMIRCFG2_IRE087_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE087_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE086		(BIT22)
	#define		ECM_ECMIRCFG2_IRE086_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE086_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE085		(BIT21)
	#define		ECM_ECMIRCFG2_IRE085_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE085_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE084		(BIT20)
	#define		ECM_ECMIRCFG2_IRE084_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE084_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE083		(BIT19)
	#define		ECM_ECMIRCFG2_IRE083_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE083_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE082		(BIT18)
	#define		ECM_ECMIRCFG2_IRE082_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE082_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE081		(BIT17)
	#define		ECM_ECMIRCFG2_IRE081_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE081_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE080		(BIT16)
	#define		ECM_ECMIRCFG2_IRE080_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE080_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE079		(BIT15)
	#define		ECM_ECMIRCFG2_IRE079_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE079_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE078		(BIT14)
	#define		ECM_ECMIRCFG2_IRE078_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE078_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE077		(BIT13)
	#define		ECM_ECMIRCFG2_IRE077_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE077_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE076		(BIT12)
	#define		ECM_ECMIRCFG2_IRE076_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE076_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE075		(BIT11)
	#define		ECM_ECMIRCFG2_IRE075_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE075_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE074		(BIT10)
	#define		ECM_ECMIRCFG2_IRE074_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE074_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE073		(BIT9)
	#define		ECM_ECMIRCFG2_IRE073_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE073_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE072		(BIT8)
	#define		ECM_ECMIRCFG2_IRE072_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE072_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE071		(BIT7)
	#define		ECM_ECMIRCFG2_IRE071_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE071_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE070		(BIT6)
	#define		ECM_ECMIRCFG2_IRE070_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE070_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE069		(BIT5)
	#define		ECM_ECMIRCFG2_IRE069_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE069_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE068		(BIT4)
	#define		ECM_ECMIRCFG2_IRE068_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE068_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE067		(BIT3)
	#define		ECM_ECMIRCFG2_IRE067_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE067_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE066		(BIT2)
	#define		ECM_ECMIRCFG2_IRE066_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE066_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE065		(BIT1)
	#define		ECM_ECMIRCFG2_IRE065_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE065_ENABLE		(1)
#define		ECM_ECMIRCFG2_IRE064		(BIT0)
	#define		ECM_ECMIRCFG2_IRE064_DISABLE	(0)
	#define		ECM_ECMIRCFG2_IRE064_ENABLE		(1)

/* ECMIRCFG3 */
#define		ECM_ECMIRCFG3_IRE127		(BIT31)
	#define		ECM_ECMIRCFG3_IRE127_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE127_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE126		(BIT30)
	#define		ECM_ECMIRCFG3_IRE126_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE126_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE125		(BIT29)
	#define		ECM_ECMIRCFG3_IRE125_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE125_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE124		(BIT28)
	#define		ECM_ECMIRCFG3_IRE124_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE124_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE123		(BIT27)
	#define		ECM_ECMIRCFG3_IRE123_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE123_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE122		(BIT26)
	#define		ECM_ECMIRCFG3_IRE122_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE122_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE121		(BIT25)
	#define		ECM_ECMIRCFG3_IRE121_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE121_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE120		(BIT24)
	#define		ECM_ECMIRCFG3_IRE120_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE120_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE119		(BIT23)
	#define		ECM_ECMIRCFG3_IRE119_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE119_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE118		(BIT22)
	#define		ECM_ECMIRCFG3_IRE118_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE118_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE117		(BIT21)
	#define		ECM_ECMIRCFG3_IRE117_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE117_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE116		(BIT20)
	#define		ECM_ECMIRCFG3_IRE116_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE116_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE115		(BIT19)
	#define		ECM_ECMIRCFG3_IRE115_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE115_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE114		(BIT18)
	#define		ECM_ECMIRCFG3_IRE114_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE114_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE113		(BIT17)
	#define		ECM_ECMIRCFG3_IRE113_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE113_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE112		(BIT16)
	#define		ECM_ECMIRCFG3_IRE112_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE112_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE111		(BIT15)
	#define		ECM_ECMIRCFG3_IRE111_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE111_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE110		(BIT14)
	#define		ECM_ECMIRCFG3_IRE110_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE110_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE109		(BIT13)
	#define		ECM_ECMIRCFG3_IRE109_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE109_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE108		(BIT12)
	#define		ECM_ECMIRCFG3_IRE108_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE108_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE107		(BIT11)
	#define		ECM_ECMIRCFG3_IRE107_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE107_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE106		(BIT10)
	#define		ECM_ECMIRCFG3_IRE106_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE106_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE105		(BIT9)
	#define		ECM_ECMIRCFG3_IRE105_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE105_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE104		(BIT8)
	#define		ECM_ECMIRCFG3_IRE104_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE104_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE103		(BIT7)
	#define		ECM_ECMIRCFG3_IRE103_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE103_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE102		(BIT6)
	#define		ECM_ECMIRCFG3_IRE102_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE102_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE101		(BIT5)
	#define		ECM_ECMIRCFG3_IRE101_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE101_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE100		(BIT4)
	#define		ECM_ECMIRCFG3_IRE100_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE100_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE099		(BIT3)
	#define		ECM_ECMIRCFG3_IRE099_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE099_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE098		(BIT2)
	#define		ECM_ECMIRCFG3_IRE098_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE098_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE097		(BIT1)
	#define		ECM_ECMIRCFG3_IRE097_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE097_ENABLE		(1)
#define		ECM_ECMIRCFG3_IRE096		(BIT0)
	#define		ECM_ECMIRCFG3_IRE096_DISABLE	(0)
	#define		ECM_ECMIRCFG3_IRE096_ENABLE		(1)

/* ECMIRCFG4 */
#define		ECM_ECMIRCFG4_IRE159		(BIT31)
	#define		ECM_ECMIRCFG4_IRE159_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE159_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE158		(BIT30)
	#define		ECM_ECMIRCFG4_IRE158_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE158_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE157		(BIT29)
	#define		ECM_ECMIRCFG4_IRE157_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE157_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE156		(BIT28)
	#define		ECM_ECMIRCFG4_IRE156_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE156_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE155		(BIT27)
	#define		ECM_ECMIRCFG4_IRE155_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE155_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE154		(BIT26)
	#define		ECM_ECMIRCFG4_IRE154_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE154_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE153		(BIT25)
	#define		ECM_ECMIRCFG4_IRE153_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE153_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE152		(BIT24)
	#define		ECM_ECMIRCFG4_IRE152_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE152_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE151		(BIT23)
	#define		ECM_ECMIRCFG4_IRE151_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE151_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE150		(BIT22)
	#define		ECM_ECMIRCFG4_IRE150_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE150_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE149		(BIT21)
	#define		ECM_ECMIRCFG4_IRE149_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE149_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE148		(BIT20)
	#define		ECM_ECMIRCFG4_IRE148_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE148_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE147		(BIT19)
	#define		ECM_ECMIRCFG4_IRE147_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE147_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE146		(BIT18)
	#define		ECM_ECMIRCFG4_IRE146_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE146_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE145		(BIT17)
	#define		ECM_ECMIRCFG4_IRE145_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE145_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE144		(BIT16)
	#define		ECM_ECMIRCFG4_IRE144_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE144_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE143		(BIT15)
	#define		ECM_ECMIRCFG4_IRE143_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE143_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE142		(BIT14)
	#define		ECM_ECMIRCFG4_IRE142_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE142_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE141		(BIT13)
	#define		ECM_ECMIRCFG4_IRE141_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE141_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE140		(BIT12)
	#define		ECM_ECMIRCFG4_IRE140_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE140_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE139		(BIT11)
	#define		ECM_ECMIRCFG4_IRE139_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE139_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE138		(BIT10)
	#define		ECM_ECMIRCFG4_IRE138_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE138_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE137		(BIT9)
	#define		ECM_ECMIRCFG4_IRE137_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE137_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE136		(BIT8)
	#define		ECM_ECMIRCFG4_IRE136_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE136_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE135		(BIT7)
	#define		ECM_ECMIRCFG4_IRE135_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE135_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE134		(BIT6)
	#define		ECM_ECMIRCFG4_IRE134_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE134_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE133		(BIT5)
	#define		ECM_ECMIRCFG4_IRE133_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE133_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE132		(BIT4)
	#define		ECM_ECMIRCFG4_IRE132_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE132_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE131		(BIT3)
	#define		ECM_ECMIRCFG4_IRE131_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE131_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE130		(BIT2)
	#define		ECM_ECMIRCFG4_IRE130_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE130_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE129		(BIT1)
	#define		ECM_ECMIRCFG4_IRE129_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE129_ENABLE		(1)
#define		ECM_ECMIRCFG4_IRE128		(BIT0)
	#define		ECM_ECMIRCFG4_IRE128_DISABLE	(0)
	#define		ECM_ECMIRCFG4_IRE128_ENABLE		(1)

/* ECMIRCFG5 */
#define		ECM_ECMIRCFG5_IRE191		(BIT31)
	#define		ECM_ECMIRCFG5_IRE191_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE191_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE190		(BIT30)
	#define		ECM_ECMIRCFG5_IRE190_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE190_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE189		(BIT29)
	#define		ECM_ECMIRCFG5_IRE189_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE189_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE188		(BIT28)
	#define		ECM_ECMIRCFG5_IRE188_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE188_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE187		(BIT27)
	#define		ECM_ECMIRCFG5_IRE187_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE187_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE186		(BIT26)
	#define		ECM_ECMIRCFG5_IRE186_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE186_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE185		(BIT25)
	#define		ECM_ECMIRCFG5_IRE185_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE185_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE184		(BIT24)
	#define		ECM_ECMIRCFG5_IRE184_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE184_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE183		(BIT23)
	#define		ECM_ECMIRCFG5_IRE183_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE183_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE182		(BIT22)
	#define		ECM_ECMIRCFG5_IRE182_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE182_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE181		(BIT21)
	#define		ECM_ECMIRCFG5_IRE181_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE181_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE180		(BIT20)
	#define		ECM_ECMIRCFG5_IRE180_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE180_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE179		(BIT19)
	#define		ECM_ECMIRCFG5_IRE179_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE179_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE178		(BIT18)
	#define		ECM_ECMIRCFG5_IRE178_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE178_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE177		(BIT17)
	#define		ECM_ECMIRCFG5_IRE177_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE177_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE176		(BIT16)
	#define		ECM_ECMIRCFG5_IRE176_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE176_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE175		(BIT15)
	#define		ECM_ECMIRCFG5_IRE175_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE175_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE174		(BIT14)
	#define		ECM_ECMIRCFG5_IRE174_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE174_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE173		(BIT13)
	#define		ECM_ECMIRCFG5_IRE173_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE173_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE172		(BIT12)
	#define		ECM_ECMIRCFG5_IRE172_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE172_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE171		(BIT11)
	#define		ECM_ECMIRCFG5_IRE171_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE171_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE170		(BIT10)
	#define		ECM_ECMIRCFG5_IRE170_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE170_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE169		(BIT9)
	#define		ECM_ECMIRCFG5_IRE169_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE169_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE168		(BIT8)
	#define		ECM_ECMIRCFG5_IRE168_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE168_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE167		(BIT7)
	#define		ECM_ECMIRCFG5_IRE167_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE167_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE166		(BIT6)
	#define		ECM_ECMIRCFG5_IRE166_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE166_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE165		(BIT5)
	#define		ECM_ECMIRCFG5_IRE165_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE165_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE164		(BIT4)
	#define		ECM_ECMIRCFG5_IRE164_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE164_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE163		(BIT3)
	#define		ECM_ECMIRCFG5_IRE163_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE163_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE162		(BIT2)
	#define		ECM_ECMIRCFG5_IRE162_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE162_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE161		(BIT1)
	#define		ECM_ECMIRCFG5_IRE161_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE161_ENABLE		(1)
#define		ECM_ECMIRCFG5_IRE160		(BIT0)
	#define		ECM_ECMIRCFG5_IRE160_DISABLE	(0)
	#define		ECM_ECMIRCFG5_IRE160_ENABLE		(1)

/* ECMIRCFG6 */
#define		ECM_ECMIRCFG6_IRE223		(BIT31)
	#define		ECM_ECMIRCFG6_IRE223_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE223_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE222		(BIT30)
	#define		ECM_ECMIRCFG6_IRE222_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE222_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE221		(BIT29)
	#define		ECM_ECMIRCFG6_IRE221_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE221_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE220		(BIT28)
	#define		ECM_ECMIRCFG6_IRE220_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE220_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE219		(BIT27)
	#define		ECM_ECMIRCFG6_IRE219_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE219_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE218		(BIT26)
	#define		ECM_ECMIRCFG6_IRE218_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE218_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE217		(BIT25)
	#define		ECM_ECMIRCFG6_IRE217_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE217_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE216		(BIT24)
	#define		ECM_ECMIRCFG6_IRE216_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE216_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE215		(BIT23)
	#define		ECM_ECMIRCFG6_IRE215_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE215_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE214		(BIT22)
	#define		ECM_ECMIRCFG6_IRE214_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE214_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE213		(BIT21)
	#define		ECM_ECMIRCFG6_IRE213_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE213_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE212		(BIT20)
	#define		ECM_ECMIRCFG6_IRE212_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE212_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE211		(BIT19)
	#define		ECM_ECMIRCFG6_IRE211_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE211_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE210		(BIT18)
	#define		ECM_ECMIRCFG6_IRE210_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE210_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE209		(BIT17)
	#define		ECM_ECMIRCFG6_IRE209_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE209_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE208		(BIT16)
	#define		ECM_ECMIRCFG6_IRE208_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE208_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE207		(BIT15)
	#define		ECM_ECMIRCFG6_IRE207_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE207_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE206		(BIT14)
	#define		ECM_ECMIRCFG6_IRE206_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE206_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE205		(BIT13)
	#define		ECM_ECMIRCFG6_IRE205_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE205_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE204		(BIT12)
	#define		ECM_ECMIRCFG6_IRE204_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE204_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE203		(BIT11)
	#define		ECM_ECMIRCFG6_IRE203_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE203_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE202		(BIT10)
	#define		ECM_ECMIRCFG6_IRE202_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE202_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE201		(BIT9)
	#define		ECM_ECMIRCFG6_IRE201_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE201_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE200		(BIT8)
	#define		ECM_ECMIRCFG6_IRE200_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE200_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE199		(BIT7)
	#define		ECM_ECMIRCFG6_IRE199_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE199_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE198		(BIT6)
	#define		ECM_ECMIRCFG6_IRE198_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE198_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE197		(BIT5)
	#define		ECM_ECMIRCFG6_IRE197_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE197_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE196		(BIT4)
	#define		ECM_ECMIRCFG6_IRE196_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE196_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE195		(BIT3)
	#define		ECM_ECMIRCFG6_IRE195_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE195_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE194		(BIT2)
	#define		ECM_ECMIRCFG6_IRE194_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE194_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE193		(BIT1)
	#define		ECM_ECMIRCFG6_IRE193_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE193_ENABLE		(1)
#define		ECM_ECMIRCFG6_IRE192		(BIT0)
	#define		ECM_ECMIRCFG6_IRE192_DISABLE	(0)
	#define		ECM_ECMIRCFG6_IRE192_ENABLE		(1)

/* ECMIRCFG7 */
#define		ECM_ECMIRCFG7_IRE255		(BIT31)
	#define		ECM_ECMIRCFG7_IRE255_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE255_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE254		(BIT30)
	#define		ECM_ECMIRCFG7_IRE254_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE254_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE253		(BIT29)
	#define		ECM_ECMIRCFG7_IRE253_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE253_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE252		(BIT28)
	#define		ECM_ECMIRCFG7_IRE252_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE252_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE251		(BIT27)
	#define		ECM_ECMIRCFG7_IRE251_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE251_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE250		(BIT26)
	#define		ECM_ECMIRCFG7_IRE250_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE250_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE249		(BIT25)
	#define		ECM_ECMIRCFG7_IRE249_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE249_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE248		(BIT24)
	#define		ECM_ECMIRCFG7_IRE248_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE248_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE247		(BIT23)
	#define		ECM_ECMIRCFG7_IRE247_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE247_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE246		(BIT22)
	#define		ECM_ECMIRCFG7_IRE246_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE246_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE245		(BIT21)
	#define		ECM_ECMIRCFG7_IRE245_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE245_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE244		(BIT20)
	#define		ECM_ECMIRCFG7_IRE244_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE244_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE243		(BIT19)
	#define		ECM_ECMIRCFG7_IRE243_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE243_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE242		(BIT18)
	#define		ECM_ECMIRCFG7_IRE242_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE242_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE241		(BIT17)
	#define		ECM_ECMIRCFG7_IRE241_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE241_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE240		(BIT16)
	#define		ECM_ECMIRCFG7_IRE240_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE240_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE239		(BIT15)
	#define		ECM_ECMIRCFG7_IRE239_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE239_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE238		(BIT14)
	#define		ECM_ECMIRCFG7_IRE238_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE238_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE237		(BIT13)
	#define		ECM_ECMIRCFG7_IRE237_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE237_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE236		(BIT12)
	#define		ECM_ECMIRCFG7_IRE236_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE236_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE235		(BIT11)
	#define		ECM_ECMIRCFG7_IRE235_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE235_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE234		(BIT10)
	#define		ECM_ECMIRCFG7_IRE234_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE234_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE233		(BIT9)
	#define		ECM_ECMIRCFG7_IRE233_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE233_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE232		(BIT8)
	#define		ECM_ECMIRCFG7_IRE232_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE232_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE231		(BIT7)
	#define		ECM_ECMIRCFG7_IRE231_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE231_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE230		(BIT6)
	#define		ECM_ECMIRCFG7_IRE230_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE230_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE229		(BIT5)
	#define		ECM_ECMIRCFG7_IRE229_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE229_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE228		(BIT4)
	#define		ECM_ECMIRCFG7_IRE228_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE228_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE227		(BIT3)
	#define		ECM_ECMIRCFG7_IRE227_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE227_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE226		(BIT2)
	#define		ECM_ECMIRCFG7_IRE226_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE226_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE225		(BIT1)
	#define		ECM_ECMIRCFG7_IRE225_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE225_ENABLE		(1)
#define		ECM_ECMIRCFG7_IRE224		(BIT0)
	#define		ECM_ECMIRCFG7_IRE224_DISABLE	(0)
	#define		ECM_ECMIRCFG7_IRE224_ENABLE		(1)

/* ECMIRCFG8 */
#define		ECM_ECMIRCFG8_IRE287		(BIT31)
	#define		ECM_ECMIRCFG8_IRE287_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE287_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE286		(BIT30)
	#define		ECM_ECMIRCFG8_IRE286_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE286_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE285		(BIT29)
	#define		ECM_ECMIRCFG8_IRE285_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE285_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE284		(BIT28)
	#define		ECM_ECMIRCFG8_IRE284_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE284_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE283		(BIT27)
	#define		ECM_ECMIRCFG8_IRE283_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE283_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE282		(BIT26)
	#define		ECM_ECMIRCFG8_IRE282_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE282_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE281		(BIT25)
	#define		ECM_ECMIRCFG8_IRE281_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE281_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE280		(BIT24)
	#define		ECM_ECMIRCFG8_IRE280_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE280_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE279		(BIT23)
	#define		ECM_ECMIRCFG8_IRE279_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE279_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE278		(BIT22)
	#define		ECM_ECMIRCFG8_IRE278_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE278_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE277		(BIT21)
	#define		ECM_ECMIRCFG8_IRE277_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE277_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE276		(BIT20)
	#define		ECM_ECMIRCFG8_IRE276_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE276_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE275		(BIT19)
	#define		ECM_ECMIRCFG8_IRE275_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE275_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE274		(BIT18)
	#define		ECM_ECMIRCFG8_IRE274_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE274_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE273		(BIT17)
	#define		ECM_ECMIRCFG8_IRE273_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE273_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE272		(BIT16)
	#define		ECM_ECMIRCFG8_IRE272_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE272_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE271		(BIT15)
	#define		ECM_ECMIRCFG8_IRE271_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE271_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE270		(BIT14)
	#define		ECM_ECMIRCFG8_IRE270_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE270_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE269		(BIT13)
	#define		ECM_ECMIRCFG8_IRE269_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE269_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE268		(BIT12)
	#define		ECM_ECMIRCFG8_IRE268_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE268_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE267		(BIT11)
	#define		ECM_ECMIRCFG8_IRE267_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE267_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE266		(BIT10)
	#define		ECM_ECMIRCFG8_IRE266_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE266_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE265		(BIT9)
	#define		ECM_ECMIRCFG8_IRE265_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE265_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE264		(BIT8)
	#define		ECM_ECMIRCFG8_IRE264_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE264_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE263		(BIT7)
	#define		ECM_ECMIRCFG8_IRE263_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE263_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE262		(BIT6)
	#define		ECM_ECMIRCFG8_IRE262_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE262_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE261		(BIT5)
	#define		ECM_ECMIRCFG8_IRE261_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE261_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE260		(BIT4)
	#define		ECM_ECMIRCFG8_IRE260_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE260_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE259		(BIT3)
	#define		ECM_ECMIRCFG8_IRE259_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE259_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE258		(BIT2)
	#define		ECM_ECMIRCFG8_IRE258_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE258_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE257		(BIT1)
	#define		ECM_ECMIRCFG8_IRE257_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE257_ENABLE		(1)
#define		ECM_ECMIRCFG8_IRE256		(BIT0)
	#define		ECM_ECMIRCFG8_IRE256_DISABLE	(0)
	#define		ECM_ECMIRCFG8_IRE256_ENABLE		(1)

/* ECMIRCFG9 */
#define		ECM_ECMIRCFG9_IRE319		(BIT31)
	#define		ECM_ECMIRCFG9_IRE319_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE319_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE318		(BIT30)
	#define		ECM_ECMIRCFG9_IRE318_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE318_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE317		(BIT29)
	#define		ECM_ECMIRCFG9_IRE317_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE317_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE316		(BIT28)
	#define		ECM_ECMIRCFG9_IRE316_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE316_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE315		(BIT27)
	#define		ECM_ECMIRCFG9_IRE315_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE315_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE314		(BIT26)
	#define		ECM_ECMIRCFG9_IRE314_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE314_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE313		(BIT25)
	#define		ECM_ECMIRCFG9_IRE313_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE313_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE312		(BIT24)
	#define		ECM_ECMIRCFG9_IRE312_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE312_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE311		(BIT23)
	#define		ECM_ECMIRCFG9_IRE311_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE311_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE310		(BIT22)
	#define		ECM_ECMIRCFG9_IRE310_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE310_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE309		(BIT21)
	#define		ECM_ECMIRCFG9_IRE309_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE309_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE308		(BIT20)
	#define		ECM_ECMIRCFG9_IRE308_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE308_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE307		(BIT19)
	#define		ECM_ECMIRCFG9_IRE307_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE307_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE306		(BIT18)
	#define		ECM_ECMIRCFG9_IRE306_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE306_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE305		(BIT17)
	#define		ECM_ECMIRCFG9_IRE305_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE305_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE304		(BIT16)
	#define		ECM_ECMIRCFG9_IRE304_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE304_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE303		(BIT15)
	#define		ECM_ECMIRCFG9_IRE303_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE303_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE302		(BIT14)
	#define		ECM_ECMIRCFG9_IRE302_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE302_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE301		(BIT13)
	#define		ECM_ECMIRCFG9_IRE301_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE301_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE300		(BIT12)
	#define		ECM_ECMIRCFG9_IRE300_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE300_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE299		(BIT11)
	#define		ECM_ECMIRCFG9_IRE299_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE299_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE298		(BIT10)
	#define		ECM_ECMIRCFG9_IRE298_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE298_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE297		(BIT9)
	#define		ECM_ECMIRCFG9_IRE297_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE297_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE296		(BIT8)
	#define		ECM_ECMIRCFG9_IRE296_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE296_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE295		(BIT7)
	#define		ECM_ECMIRCFG9_IRE295_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE295_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE294		(BIT6)
	#define		ECM_ECMIRCFG9_IRE294_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE294_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE293		(BIT5)
	#define		ECM_ECMIRCFG9_IRE293_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE293_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE292		(BIT4)
	#define		ECM_ECMIRCFG9_IRE292_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE292_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE291		(BIT3)
	#define		ECM_ECMIRCFG9_IRE291_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE291_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE290		(BIT2)
	#define		ECM_ECMIRCFG9_IRE290_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE290_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE289		(BIT1)
	#define		ECM_ECMIRCFG9_IRE289_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE289_ENABLE		(1)
#define		ECM_ECMIRCFG9_IRE288		(BIT0)
	#define		ECM_ECMIRCFG9_IRE288_DISABLE	(0)
	#define		ECM_ECMIRCFG9_IRE288_ENABLE		(1)

/* ECMIRCFG10 */
#define		ECM_ECMIRCFG10_IRE351		(BIT31)
	#define		ECM_ECMIRCFG10_IRE351_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE351_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE350		(BIT30)
	#define		ECM_ECMIRCFG10_IRE350_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE350_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE349		(BIT29)
	#define		ECM_ECMIRCFG10_IRE349_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE349_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE348		(BIT28)
	#define		ECM_ECMIRCFG10_IRE348_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE348_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE347		(BIT27)
	#define		ECM_ECMIRCFG10_IRE347_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE347_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE346		(BIT26)
	#define		ECM_ECMIRCFG10_IRE346_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE346_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE345		(BIT25)
	#define		ECM_ECMIRCFG10_IRE345_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE345_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE344		(BIT24)
	#define		ECM_ECMIRCFG10_IRE344_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE344_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE343		(BIT23)
	#define		ECM_ECMIRCFG10_IRE343_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE343_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE342		(BIT22)
	#define		ECM_ECMIRCFG10_IRE342_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE342_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE341		(BIT21)
	#define		ECM_ECMIRCFG10_IRE341_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE341_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE340		(BIT20)
	#define		ECM_ECMIRCFG10_IRE340_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE340_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE339		(BIT19)
	#define		ECM_ECMIRCFG10_IRE339_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE339_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE338		(BIT18)
	#define		ECM_ECMIRCFG10_IRE338_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE338_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE337		(BIT17)
	#define		ECM_ECMIRCFG10_IRE337_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE337_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE336		(BIT16)
	#define		ECM_ECMIRCFG10_IRE336_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE336_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE335		(BIT15)
	#define		ECM_ECMIRCFG10_IRE335_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE335_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE334		(BIT14)
	#define		ECM_ECMIRCFG10_IRE334_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE334_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE333		(BIT13)
	#define		ECM_ECMIRCFG10_IRE333_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE333_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE332		(BIT12)
	#define		ECM_ECMIRCFG10_IRE332_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE332_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE331		(BIT11)
	#define		ECM_ECMIRCFG10_IRE331_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE331_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE330		(BIT10)
	#define		ECM_ECMIRCFG10_IRE330_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE330_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE329		(BIT9)
	#define		ECM_ECMIRCFG10_IRE329_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE329_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE328		(BIT8)
	#define		ECM_ECMIRCFG10_IRE328_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE328_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE327		(BIT7)
	#define		ECM_ECMIRCFG10_IRE327_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE327_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE326		(BIT6)
	#define		ECM_ECMIRCFG10_IRE326_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE326_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE325		(BIT5)
	#define		ECM_ECMIRCFG10_IRE325_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE325_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE324		(BIT4)
	#define		ECM_ECMIRCFG10_IRE324_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE324_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE323		(BIT3)
	#define		ECM_ECMIRCFG10_IRE323_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE323_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE322		(BIT2)
	#define		ECM_ECMIRCFG10_IRE322_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE322_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE321		(BIT1)
	#define		ECM_ECMIRCFG10_IRE321_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE321_ENABLE		(1)
#define		ECM_ECMIRCFG10_IRE320		(BIT0)
	#define		ECM_ECMIRCFG10_IRE320_DISABLE	(0)
	#define		ECM_ECMIRCFG10_IRE320_ENABLE		(1)

/* ECMEMK0 */
#define		ECM_ECMEMK0_EMK031		(BIT31)
	#define		ECM_ECMEMK0_EMK031_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK031_MASK		(1)
#define		ECM_ECMEMK0_EMK030		(BIT30)
	#define		ECM_ECMEMK0_EMK030_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK030_MASK		(1)
#define		ECM_ECMEMK0_EMK029		(BIT29)
	#define		ECM_ECMEMK0_EMK029_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK029_MASK		(1)
#define		ECM_ECMEMK0_EMK028		(BIT28)
	#define		ECM_ECMEMK0_EMK028_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK028_MASK		(1)
#define		ECM_ECMEMK0_EMK027		(BIT27)
	#define		ECM_ECMEMK0_EMK027_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK027_MASK		(1)
#define		ECM_ECMEMK0_EMK026		(BIT26)
	#define		ECM_ECMEMK0_EMK026_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK026_MASK		(1)
#define		ECM_ECMEMK0_EMK025		(BIT25)
	#define		ECM_ECMEMK0_EMK025_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK025_MASK		(1)
#define		ECM_ECMEMK0_EMK024		(BIT24)
	#define		ECM_ECMEMK0_EMK024_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK024_MASK		(1)
#define		ECM_ECMEMK0_EMK023		(BIT23)
	#define		ECM_ECMEMK0_EMK023_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK023_MASK		(1)
#define		ECM_ECMEMK0_EMK022		(BIT22)
	#define		ECM_ECMEMK0_EMK022_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK022_MASK		(1)
#define		ECM_ECMEMK0_EMK021		(BIT21)
	#define		ECM_ECMEMK0_EMK021_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK021_MASK		(1)
#define		ECM_ECMEMK0_EMK020		(BIT20)
	#define		ECM_ECMEMK0_EMK020_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK020_MASK		(1)
#define		ECM_ECMEMK0_EMK011		(BIT11)
	#define		ECM_ECMEMK0_EMK011_NOMASK	(0)
	#define		ECM_ECMEMK0_EMK011_MASK		(1)

/* ECMEMK1 */
#define		ECM_ECMEMK1_EMK063		(BIT31)
	#define		ECM_ECMEMK1_EMK063_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK063_MASK		(1)
#define		ECM_ECMEMK1_EMK062		(BIT30)
	#define		ECM_ECMEMK1_EMK062_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK062_MASK		(1)
#define		ECM_ECMEMK1_EMK061		(BIT29)
	#define		ECM_ECMEMK1_EMK061_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK061_MASK		(1)
#define		ECM_ECMEMK1_EMK060		(BIT28)
	#define		ECM_ECMEMK1_EMK060_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK060_MASK		(1)
#define		ECM_ECMEMK1_EMK059		(BIT27)
	#define		ECM_ECMEMK1_EMK059_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK059_MASK		(1)
#define		ECM_ECMEMK1_EMK058		(BIT26)
	#define		ECM_ECMEMK1_EMK058_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK058_MASK		(1)
#define		ECM_ECMEMK1_EMK057		(BIT25)
	#define		ECM_ECMEMK1_EMK057_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK057_MASK		(1)
#define		ECM_ECMEMK1_EMK056		(BIT24)
	#define		ECM_ECMEMK1_EMK056_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK056_MASK		(1)
#define		ECM_ECMEMK1_EMK055		(BIT23)
	#define		ECM_ECMEMK1_EMK055_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK055_MASK		(1)
#define		ECM_ECMEMK1_EMK054		(BIT22)
	#define		ECM_ECMEMK1_EMK054_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK054_MASK		(1)
#define		ECM_ECMEMK1_EMK053		(BIT21)
	#define		ECM_ECMEMK1_EMK053_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK053_MASK		(1)
#define		ECM_ECMEMK1_EMK052		(BIT20)
	#define		ECM_ECMEMK1_EMK052_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK052_MASK		(1)
#define		ECM_ECMEMK1_EMK051		(BIT19)
	#define		ECM_ECMEMK1_EMK051_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK051_MASK		(1)
#define		ECM_ECMEMK1_EMK050		(BIT18)
	#define		ECM_ECMEMK1_EMK050_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK050_MASK		(1)
#define		ECM_ECMEMK1_EMK049		(BIT17)
	#define		ECM_ECMEMK1_EMK049_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK049_MASK		(1)
#define		ECM_ECMEMK1_EMK048		(BIT16)
	#define		ECM_ECMEMK1_EMK048_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK048_MASK		(1)
#define		ECM_ECMEMK1_EMK047		(BIT15)
	#define		ECM_ECMEMK1_EMK047_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK047_MASK		(1)
#define		ECM_ECMEMK1_EMK046		(BIT14)
	#define		ECM_ECMEMK1_EMK046_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK046_MASK		(1)
#define		ECM_ECMEMK1_EMK045		(BIT13)
	#define		ECM_ECMEMK1_EMK045_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK045_MASK		(1)
#define		ECM_ECMEMK1_EMK044		(BIT12)
	#define		ECM_ECMEMK1_EMK044_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK044_MASK		(1)
#define		ECM_ECMEMK1_EMK043		(BIT11)
	#define		ECM_ECMEMK1_EMK043_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK043_MASK		(1)
#define		ECM_ECMEMK1_EMK042		(BIT10)
	#define		ECM_ECMEMK1_EMK042_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK042_MASK		(1)
#define		ECM_ECMEMK1_EMK041		(BIT9)
	#define		ECM_ECMEMK1_EMK041_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK041_MASK		(1)
#define		ECM_ECMEMK1_EMK040		(BIT8)
	#define		ECM_ECMEMK1_EMK040_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK040_MASK		(1)
#define		ECM_ECMEMK1_EMK039		(BIT7)
	#define		ECM_ECMEMK1_EMK039_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK039_MASK		(1)
#define		ECM_ECMEMK1_EMK038		(BIT6)
	#define		ECM_ECMEMK1_EMK038_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK038_MASK		(1)
#define		ECM_ECMEMK1_EMK037		(BIT5)
	#define		ECM_ECMEMK1_EMK037_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK037_MASK		(1)
#define		ECM_ECMEMK1_EMK036		(BIT4)
	#define		ECM_ECMEMK1_EMK036_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK036_MASK		(1)
#define		ECM_ECMEMK1_EMK035		(BIT3)
	#define		ECM_ECMEMK1_EMK035_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK035_MASK		(1)
#define		ECM_ECMEMK1_EMK034		(BIT2)
	#define		ECM_ECMEMK1_EMK034_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK034_MASK		(1)
#define		ECM_ECMEMK1_EMK033		(BIT1)
	#define		ECM_ECMEMK1_EMK033_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK033_MASK		(1)
#define		ECM_ECMEMK1_EMK032		(BIT0)
	#define		ECM_ECMEMK1_EMK032_NOMASK	(0)
	#define		ECM_ECMEMK1_EMK032_MASK		(1)

/* ECMEMK2 */
#define		ECM_ECMEMK2_EMK095		(BIT31)
	#define		ECM_ECMEMK2_EMK095_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK095_MASK		(1)
#define		ECM_ECMEMK2_EMK094		(BIT30)
	#define		ECM_ECMEMK2_EMK094_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK094_MASK		(1)
#define		ECM_ECMEMK2_EMK093		(BIT29)
	#define		ECM_ECMEMK2_EMK093_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK093_MASK		(1)
#define		ECM_ECMEMK2_EMK092		(BIT28)
	#define		ECM_ECMEMK2_EMK092_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK092_MASK		(1)
#define		ECM_ECMEMK2_EMK091		(BIT27)
	#define		ECM_ECMEMK2_EMK091_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK091_MASK		(1)
#define		ECM_ECMEMK2_EMK090		(BIT26)
	#define		ECM_ECMEMK2_EMK090_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK090_MASK		(1)
#define		ECM_ECMEMK2_EMK089		(BIT25)
	#define		ECM_ECMEMK2_EMK089_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK089_MASK		(1)
#define		ECM_ECMEMK2_EMK088		(BIT24)
	#define		ECM_ECMEMK2_EMK088_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK088_MASK		(1)
#define		ECM_ECMEMK2_EMK087		(BIT23)
	#define		ECM_ECMEMK2_EMK087_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK087_MASK		(1)
#define		ECM_ECMEMK2_EMK086		(BIT22)
	#define		ECM_ECMEMK2_EMK086_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK086_MASK		(1)
#define		ECM_ECMEMK2_EMK085		(BIT21)
	#define		ECM_ECMEMK2_EMK085_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK085_MASK		(1)
#define		ECM_ECMEMK2_EMK084		(BIT20)
	#define		ECM_ECMEMK2_EMK084_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK084_MASK		(1)
#define		ECM_ECMEMK2_EMK083		(BIT19)
	#define		ECM_ECMEMK2_EMK083_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK083_MASK		(1)
#define		ECM_ECMEMK2_EMK082		(BIT18)
	#define		ECM_ECMEMK2_EMK082_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK082_MASK		(1)
#define		ECM_ECMEMK2_EMK081		(BIT17)
	#define		ECM_ECMEMK2_EMK081_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK081_MASK		(1)
#define		ECM_ECMEMK2_EMK080		(BIT16)
	#define		ECM_ECMEMK2_EMK080_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK080_MASK		(1)
#define		ECM_ECMEMK2_EMK079		(BIT15)
	#define		ECM_ECMEMK2_EMK079_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK079_MASK		(1)
#define		ECM_ECMEMK2_EMK078		(BIT14)
	#define		ECM_ECMEMK2_EMK078_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK078_MASK		(1)
#define		ECM_ECMEMK2_EMK077		(BIT13)
	#define		ECM_ECMEMK2_EMK077_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK077_MASK		(1)
#define		ECM_ECMEMK2_EMK076		(BIT12)
	#define		ECM_ECMEMK2_EMK076_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK076_MASK		(1)
#define		ECM_ECMEMK2_EMK075		(BIT11)
	#define		ECM_ECMEMK2_EMK075_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK075_MASK		(1)
#define		ECM_ECMEMK2_EMK074		(BIT10)
	#define		ECM_ECMEMK2_EMK074_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK074_MASK		(1)
#define		ECM_ECMEMK2_EMK073		(BIT9)
	#define		ECM_ECMEMK2_EMK073_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK073_MASK		(1)
#define		ECM_ECMEMK2_EMK072		(BIT8)
	#define		ECM_ECMEMK2_EMK072_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK072_MASK		(1)
#define		ECM_ECMEMK2_EMK071		(BIT7)
	#define		ECM_ECMEMK2_EMK071_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK071_MASK		(1)
#define		ECM_ECMEMK2_EMK070		(BIT6)
	#define		ECM_ECMEMK2_EMK070_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK070_MASK		(1)
#define		ECM_ECMEMK2_EMK069		(BIT5)
	#define		ECM_ECMEMK2_EMK069_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK069_MASK		(1)
#define		ECM_ECMEMK2_EMK068		(BIT4)
	#define		ECM_ECMEMK2_EMK068_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK068_MASK		(1)
#define		ECM_ECMEMK2_EMK067		(BIT3)
	#define		ECM_ECMEMK2_EMK067_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK067_MASK		(1)
#define		ECM_ECMEMK2_EMK066		(BIT2)
	#define		ECM_ECMEMK2_EMK066_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK066_MASK		(1)
#define		ECM_ECMEMK2_EMK065		(BIT1)
	#define		ECM_ECMEMK2_EMK065_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK065_MASK		(1)
#define		ECM_ECMEMK2_EMK064		(BIT0)
	#define		ECM_ECMEMK2_EMK064_NOMASK	(0)
	#define		ECM_ECMEMK2_EMK064_MASK		(1)

/* ECMEMK3 */
#define		ECM_ECMEMK3_EMK127		(BIT31)
	#define		ECM_ECMEMK3_EMK127_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK127_MASK		(1)
#define		ECM_ECMEMK3_EMK126		(BIT30)
	#define		ECM_ECMEMK3_EMK126_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK126_MASK		(1)
#define		ECM_ECMEMK3_EMK125		(BIT29)
	#define		ECM_ECMEMK3_EMK125_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK125_MASK		(1)
#define		ECM_ECMEMK3_EMK124		(BIT28)
	#define		ECM_ECMEMK3_EMK124_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK124_MASK		(1)
#define		ECM_ECMEMK3_EMK123		(BIT27)
	#define		ECM_ECMEMK3_EMK123_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK123_MASK		(1)
#define		ECM_ECMEMK3_EMK122		(BIT26)
	#define		ECM_ECMEMK3_EMK122_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK122_MASK		(1)
#define		ECM_ECMEMK3_EMK121		(BIT25)
	#define		ECM_ECMEMK3_EMK121_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK121_MASK		(1)
#define		ECM_ECMEMK3_EMK120		(BIT24)
	#define		ECM_ECMEMK3_EMK120_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK120_MASK		(1)
#define		ECM_ECMEMK3_EMK119		(BIT23)
	#define		ECM_ECMEMK3_EMK119_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK119_MASK		(1)
#define		ECM_ECMEMK3_EMK118		(BIT22)
	#define		ECM_ECMEMK3_EMK118_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK118_MASK		(1)
#define		ECM_ECMEMK3_EMK117		(BIT21)
	#define		ECM_ECMEMK3_EMK117_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK117_MASK		(1)
#define		ECM_ECMEMK3_EMK116		(BIT20)
	#define		ECM_ECMEMK3_EMK116_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK116_MASK		(1)
#define		ECM_ECMEMK3_EMK115		(BIT19)
	#define		ECM_ECMEMK3_EMK115_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK115_MASK		(1)
#define		ECM_ECMEMK3_EMK114		(BIT18)
	#define		ECM_ECMEMK3_EMK114_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK114_MASK		(1)
#define		ECM_ECMEMK3_EMK113		(BIT17)
	#define		ECM_ECMEMK3_EMK113_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK113_MASK		(1)
#define		ECM_ECMEMK3_EMK112		(BIT16)
	#define		ECM_ECMEMK3_EMK112_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK112_MASK		(1)
#define		ECM_ECMEMK3_EMK111		(BIT15)
	#define		ECM_ECMEMK3_EMK111_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK111_MASK		(1)
#define		ECM_ECMEMK3_EMK110		(BIT14)
	#define		ECM_ECMEMK3_EMK110_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK110_MASK		(1)
#define		ECM_ECMEMK3_EMK109		(BIT13)
	#define		ECM_ECMEMK3_EMK109_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK109_MASK		(1)
#define		ECM_ECMEMK3_EMK108		(BIT12)
	#define		ECM_ECMEMK3_EMK108_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK108_MASK		(1)
#define		ECM_ECMEMK3_EMK107		(BIT11)
	#define		ECM_ECMEMK3_EMK107_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK107_MASK		(1)
#define		ECM_ECMEMK3_EMK106		(BIT10)
	#define		ECM_ECMEMK3_EMK106_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK106_MASK		(1)
#define		ECM_ECMEMK3_EMK105		(BIT9)
	#define		ECM_ECMEMK3_EMK105_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK105_MASK		(1)
#define		ECM_ECMEMK3_EMK104		(BIT8)
	#define		ECM_ECMEMK3_EMK104_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK104_MASK		(1)
#define		ECM_ECMEMK3_EMK103		(BIT7)
	#define		ECM_ECMEMK3_EMK103_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK103_MASK		(1)
#define		ECM_ECMEMK3_EMK102		(BIT6)
	#define		ECM_ECMEMK3_EMK102_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK102_MASK		(1)
#define		ECM_ECMEMK3_EMK101		(BIT5)
	#define		ECM_ECMEMK3_EMK101_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK101_MASK		(1)
#define		ECM_ECMEMK3_EMK100		(BIT4)
	#define		ECM_ECMEMK3_EMK100_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK100_MASK		(1)
#define		ECM_ECMEMK3_EMK099		(BIT3)
	#define		ECM_ECMEMK3_EMK099_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK099_MASK		(1)
#define		ECM_ECMEMK3_EMK098		(BIT2)
	#define		ECM_ECMEMK3_EMK098_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK098_MASK		(1)
#define		ECM_ECMEMK3_EMK097		(BIT1)
	#define		ECM_ECMEMK3_EMK097_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK097_MASK		(1)
#define		ECM_ECMEMK3_EMK096		(BIT0)
	#define		ECM_ECMEMK3_EMK096_NOMASK	(0)
	#define		ECM_ECMEMK3_EMK096_MASK		(1)

/* ECMEMK4 */
#define		ECM_ECMEMK4_EMK159		(BIT31)
	#define		ECM_ECMEMK4_EMK159_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK159_MASK		(1)
#define		ECM_ECMEMK4_EMK158		(BIT30)
	#define		ECM_ECMEMK4_EMK158_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK158_MASK		(1)
#define		ECM_ECMEMK4_EMK157		(BIT29)
	#define		ECM_ECMEMK4_EMK157_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK157_MASK		(1)
#define		ECM_ECMEMK4_EMK156		(BIT28)
	#define		ECM_ECMEMK4_EMK156_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK156_MASK		(1)
#define		ECM_ECMEMK4_EMK155		(BIT27)
	#define		ECM_ECMEMK4_EMK155_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK155_MASK		(1)
#define		ECM_ECMEMK4_EMK154		(BIT26)
	#define		ECM_ECMEMK4_EMK154_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK154_MASK		(1)
#define		ECM_ECMEMK4_EMK153		(BIT25)
	#define		ECM_ECMEMK4_EMK153_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK153_MASK		(1)
#define		ECM_ECMEMK4_EMK152		(BIT24)
	#define		ECM_ECMEMK4_EMK152_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK152_MASK		(1)
#define		ECM_ECMEMK4_EMK151		(BIT23)
	#define		ECM_ECMEMK4_EMK151_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK151_MASK		(1)
#define		ECM_ECMEMK4_EMK150		(BIT22)
	#define		ECM_ECMEMK4_EMK150_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK150_MASK		(1)
#define		ECM_ECMEMK4_EMK149		(BIT21)
	#define		ECM_ECMEMK4_EMK149_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK149_MASK		(1)
#define		ECM_ECMEMK4_EMK148		(BIT20)
	#define		ECM_ECMEMK4_EMK148_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK148_MASK		(1)
#define		ECM_ECMEMK4_EMK147		(BIT19)
	#define		ECM_ECMEMK4_EMK147_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK147_MASK		(1)
#define		ECM_ECMEMK4_EMK146		(BIT18)
	#define		ECM_ECMEMK4_EMK146_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK146_MASK		(1)
#define		ECM_ECMEMK4_EMK145		(BIT17)
	#define		ECM_ECMEMK4_EMK145_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK145_MASK		(1)
#define		ECM_ECMEMK4_EMK144		(BIT16)
	#define		ECM_ECMEMK4_EMK144_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK144_MASK		(1)
#define		ECM_ECMEMK4_EMK143		(BIT15)
	#define		ECM_ECMEMK4_EMK143_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK143_MASK		(1)
#define		ECM_ECMEMK4_EMK142		(BIT14)
	#define		ECM_ECMEMK4_EMK142_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK142_MASK		(1)
#define		ECM_ECMEMK4_EMK141		(BIT13)
	#define		ECM_ECMEMK4_EMK141_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK141_MASK		(1)
#define		ECM_ECMEMK4_EMK140		(BIT12)
	#define		ECM_ECMEMK4_EMK140_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK140_MASK		(1)
#define		ECM_ECMEMK4_EMK139		(BIT11)
	#define		ECM_ECMEMK4_EMK139_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK139_MASK		(1)
#define		ECM_ECMEMK4_EMK138		(BIT10)
	#define		ECM_ECMEMK4_EMK138_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK138_MASK		(1)
#define		ECM_ECMEMK4_EMK137		(BIT9)
	#define		ECM_ECMEMK4_EMK137_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK137_MASK		(1)
#define		ECM_ECMEMK4_EMK136		(BIT8)
	#define		ECM_ECMEMK4_EMK136_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK136_MASK		(1)
#define		ECM_ECMEMK4_EMK135		(BIT7)
	#define		ECM_ECMEMK4_EMK135_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK135_MASK		(1)
#define		ECM_ECMEMK4_EMK134		(BIT6)
	#define		ECM_ECMEMK4_EMK134_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK134_MASK		(1)
#define		ECM_ECMEMK4_EMK133		(BIT5)
	#define		ECM_ECMEMK4_EMK133_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK133_MASK		(1)
#define		ECM_ECMEMK4_EMK132		(BIT4)
	#define		ECM_ECMEMK4_EMK132_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK132_MASK		(1)
#define		ECM_ECMEMK4_EMK131		(BIT3)
	#define		ECM_ECMEMK4_EMK131_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK131_MASK		(1)
#define		ECM_ECMEMK4_EMK130		(BIT2)
	#define		ECM_ECMEMK4_EMK130_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK130_MASK		(1)
#define		ECM_ECMEMK4_EMK129		(BIT1)
	#define		ECM_ECMEMK4_EMK129_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK129_MASK		(1)
#define		ECM_ECMEMK4_EMK128		(BIT0)
	#define		ECM_ECMEMK4_EMK128_NOMASK	(0)
	#define		ECM_ECMEMK4_EMK128_MASK		(1)

/* ECMEMK5 */
#define		ECM_ECMEMK5_EMK191		(BIT31)
	#define		ECM_ECMEMK5_EMK191_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK191_MASK		(1)
#define		ECM_ECMEMK5_EMK190		(BIT30)
	#define		ECM_ECMEMK5_EMK190_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK190_MASK		(1)
#define		ECM_ECMEMK5_EMK189		(BIT29)
	#define		ECM_ECMEMK5_EMK189_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK189_MASK		(1)
#define		ECM_ECMEMK5_EMK188		(BIT28)
	#define		ECM_ECMEMK5_EMK188_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK188_MASK		(1)
#define		ECM_ECMEMK5_EMK187		(BIT27)
	#define		ECM_ECMEMK5_EMK187_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK187_MASK		(1)
#define		ECM_ECMEMK5_EMK186		(BIT26)
	#define		ECM_ECMEMK5_EMK186_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK186_MASK		(1)
#define		ECM_ECMEMK5_EMK185		(BIT25)
	#define		ECM_ECMEMK5_EMK185_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK185_MASK		(1)
#define		ECM_ECMEMK5_EMK184		(BIT24)
	#define		ECM_ECMEMK5_EMK184_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK184_MASK		(1)
#define		ECM_ECMEMK5_EMK183		(BIT23)
	#define		ECM_ECMEMK5_EMK183_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK183_MASK		(1)
#define		ECM_ECMEMK5_EMK182		(BIT22)
	#define		ECM_ECMEMK5_EMK182_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK182_MASK		(1)
#define		ECM_ECMEMK5_EMK181		(BIT21)
	#define		ECM_ECMEMK5_EMK181_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK181_MASK		(1)
#define		ECM_ECMEMK5_EMK180		(BIT20)
	#define		ECM_ECMEMK5_EMK180_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK180_MASK		(1)
#define		ECM_ECMEMK5_EMK179		(BIT19)
	#define		ECM_ECMEMK5_EMK179_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK179_MASK		(1)
#define		ECM_ECMEMK5_EMK178		(BIT18)
	#define		ECM_ECMEMK5_EMK178_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK178_MASK		(1)
#define		ECM_ECMEMK5_EMK177		(BIT17)
	#define		ECM_ECMEMK5_EMK177_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK177_MASK		(1)
#define		ECM_ECMEMK5_EMK176		(BIT16)
	#define		ECM_ECMEMK5_EMK176_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK176_MASK		(1)
#define		ECM_ECMEMK5_EMK175		(BIT15)
	#define		ECM_ECMEMK5_EMK175_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK175_MASK		(1)
#define		ECM_ECMEMK5_EMK174		(BIT14)
	#define		ECM_ECMEMK5_EMK174_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK174_MASK		(1)
#define		ECM_ECMEMK5_EMK173		(BIT13)
	#define		ECM_ECMEMK5_EMK173_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK173_MASK		(1)
#define		ECM_ECMEMK5_EMK172		(BIT12)
	#define		ECM_ECMEMK5_EMK172_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK172_MASK		(1)
#define		ECM_ECMEMK5_EMK171		(BIT11)
	#define		ECM_ECMEMK5_EMK171_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK171_MASK		(1)
#define		ECM_ECMEMK5_EMK170		(BIT10)
	#define		ECM_ECMEMK5_EMK170_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK170_MASK		(1)
#define		ECM_ECMEMK5_EMK169		(BIT9)
	#define		ECM_ECMEMK5_EMK169_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK169_MASK		(1)
#define		ECM_ECMEMK5_EMK168		(BIT8)
	#define		ECM_ECMEMK5_EMK168_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK168_MASK		(1)
#define		ECM_ECMEMK5_EMK167		(BIT7)
	#define		ECM_ECMEMK5_EMK167_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK167_MASK		(1)
#define		ECM_ECMEMK5_EMK166		(BIT6)
	#define		ECM_ECMEMK5_EMK166_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK166_MASK		(1)
#define		ECM_ECMEMK5_EMK165		(BIT5)
	#define		ECM_ECMEMK5_EMK165_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK165_MASK		(1)
#define		ECM_ECMEMK5_EMK164		(BIT4)
	#define		ECM_ECMEMK5_EMK164_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK164_MASK		(1)
#define		ECM_ECMEMK5_EMK163		(BIT3)
	#define		ECM_ECMEMK5_EMK163_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK163_MASK		(1)
#define		ECM_ECMEMK5_EMK162		(BIT2)
	#define		ECM_ECMEMK5_EMK162_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK162_MASK		(1)
#define		ECM_ECMEMK5_EMK161		(BIT1)
	#define		ECM_ECMEMK5_EMK161_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK161_MASK		(1)
#define		ECM_ECMEMK5_EMK160		(BIT0)
	#define		ECM_ECMEMK5_EMK160_NOMASK	(0)
	#define		ECM_ECMEMK5_EMK160_MASK		(1)

/* ECMEMK6 */
#define		ECM_ECMEMK6_EMK223		(BIT31)
	#define		ECM_ECMEMK6_EMK223_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK223_MASK		(1)
#define		ECM_ECMEMK6_EMK222		(BIT30)
	#define		ECM_ECMEMK6_EMK222_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK222_MASK		(1)
#define		ECM_ECMEMK6_EMK221		(BIT29)
	#define		ECM_ECMEMK6_EMK221_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK221_MASK		(1)
#define		ECM_ECMEMK6_EMK220		(BIT28)
	#define		ECM_ECMEMK6_EMK220_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK220_MASK		(1)
#define		ECM_ECMEMK6_EMK219		(BIT27)
	#define		ECM_ECMEMK6_EMK219_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK219_MASK		(1)
#define		ECM_ECMEMK6_EMK218		(BIT26)
	#define		ECM_ECMEMK6_EMK218_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK218_MASK		(1)
#define		ECM_ECMEMK6_EMK217		(BIT25)
	#define		ECM_ECMEMK6_EMK217_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK217_MASK		(1)
#define		ECM_ECMEMK6_EMK216		(BIT24)
	#define		ECM_ECMEMK6_EMK216_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK216_MASK		(1)
#define		ECM_ECMEMK6_EMK215		(BIT23)
	#define		ECM_ECMEMK6_EMK215_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK215_MASK		(1)
#define		ECM_ECMEMK6_EMK214		(BIT22)
	#define		ECM_ECMEMK6_EMK214_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK214_MASK		(1)
#define		ECM_ECMEMK6_EMK213		(BIT21)
	#define		ECM_ECMEMK6_EMK213_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK213_MASK		(1)
#define		ECM_ECMEMK6_EMK212		(BIT20)
	#define		ECM_ECMEMK6_EMK212_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK212_MASK		(1)
#define		ECM_ECMEMK6_EMK211		(BIT19)
	#define		ECM_ECMEMK6_EMK211_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK211_MASK		(1)
#define		ECM_ECMEMK6_EMK210		(BIT18)
	#define		ECM_ECMEMK6_EMK210_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK210_MASK		(1)
#define		ECM_ECMEMK6_EMK209		(BIT17)
	#define		ECM_ECMEMK6_EMK209_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK209_MASK		(1)
#define		ECM_ECMEMK6_EMK208		(BIT16)
	#define		ECM_ECMEMK6_EMK208_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK208_MASK		(1)
#define		ECM_ECMEMK6_EMK207		(BIT15)
	#define		ECM_ECMEMK6_EMK207_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK207_MASK		(1)
#define		ECM_ECMEMK6_EMK206		(BIT14)
	#define		ECM_ECMEMK6_EMK206_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK206_MASK		(1)
#define		ECM_ECMEMK6_EMK205		(BIT13)
	#define		ECM_ECMEMK6_EMK205_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK205_MASK		(1)
#define		ECM_ECMEMK6_EMK204		(BIT12)
	#define		ECM_ECMEMK6_EMK204_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK204_MASK		(1)
#define		ECM_ECMEMK6_EMK203		(BIT11)
	#define		ECM_ECMEMK6_EMK203_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK203_MASK		(1)
#define		ECM_ECMEMK6_EMK202		(BIT10)
	#define		ECM_ECMEMK6_EMK202_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK202_MASK		(1)
#define		ECM_ECMEMK6_EMK201		(BIT9)
	#define		ECM_ECMEMK6_EMK201_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK201_MASK		(1)
#define		ECM_ECMEMK6_EMK200		(BIT8)
	#define		ECM_ECMEMK6_EMK200_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK200_MASK		(1)
#define		ECM_ECMEMK6_EMK199		(BIT7)
	#define		ECM_ECMEMK6_EMK199_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK199_MASK		(1)
#define		ECM_ECMEMK6_EMK198		(BIT6)
	#define		ECM_ECMEMK6_EMK198_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK198_MASK		(1)
#define		ECM_ECMEMK6_EMK197		(BIT5)
	#define		ECM_ECMEMK6_EMK197_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK197_MASK		(1)
#define		ECM_ECMEMK6_EMK196		(BIT4)
	#define		ECM_ECMEMK6_EMK196_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK196_MASK		(1)
#define		ECM_ECMEMK6_EMK195		(BIT3)
	#define		ECM_ECMEMK6_EMK195_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK195_MASK		(1)
#define		ECM_ECMEMK6_EMK194		(BIT2)
	#define		ECM_ECMEMK6_EMK194_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK194_MASK		(1)
#define		ECM_ECMEMK6_EMK193		(BIT1)
	#define		ECM_ECMEMK6_EMK193_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK193_MASK		(1)
#define		ECM_ECMEMK6_EMK192		(BIT0)
	#define		ECM_ECMEMK6_EMK192_NOMASK	(0)
	#define		ECM_ECMEMK6_EMK192_MASK		(1)

/* ECMEMK7 */
#define		ECM_ECMEMK7_EMK255		(BIT31)
	#define		ECM_ECMEMK7_EMK255_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK255_MASK		(1)
#define		ECM_ECMEMK7_EMK254		(BIT30)
	#define		ECM_ECMEMK7_EMK254_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK254_MASK		(1)
#define		ECM_ECMEMK7_EMK253		(BIT29)
	#define		ECM_ECMEMK7_EMK253_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK253_MASK		(1)
#define		ECM_ECMEMK7_EMK252		(BIT28)
	#define		ECM_ECMEMK7_EMK252_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK252_MASK		(1)
#define		ECM_ECMEMK7_EMK251		(BIT27)
	#define		ECM_ECMEMK7_EMK251_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK251_MASK		(1)
#define		ECM_ECMEMK7_EMK250		(BIT26)
	#define		ECM_ECMEMK7_EMK250_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK250_MASK		(1)
#define		ECM_ECMEMK7_EMK249		(BIT25)
	#define		ECM_ECMEMK7_EMK249_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK249_MASK		(1)
#define		ECM_ECMEMK7_EMK248		(BIT24)
	#define		ECM_ECMEMK7_EMK248_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK248_MASK		(1)
#define		ECM_ECMEMK7_EMK247		(BIT23)
	#define		ECM_ECMEMK7_EMK247_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK247_MASK		(1)
#define		ECM_ECMEMK7_EMK246		(BIT22)
	#define		ECM_ECMEMK7_EMK246_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK246_MASK		(1)
#define		ECM_ECMEMK7_EMK245		(BIT21)
	#define		ECM_ECMEMK7_EMK245_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK245_MASK		(1)
#define		ECM_ECMEMK7_EMK244		(BIT20)
	#define		ECM_ECMEMK7_EMK244_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK244_MASK		(1)
#define		ECM_ECMEMK7_EMK243		(BIT19)
	#define		ECM_ECMEMK7_EMK243_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK243_MASK		(1)
#define		ECM_ECMEMK7_EMK242		(BIT18)
	#define		ECM_ECMEMK7_EMK242_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK242_MASK		(1)
#define		ECM_ECMEMK7_EMK241		(BIT17)
	#define		ECM_ECMEMK7_EMK241_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK241_MASK		(1)
#define		ECM_ECMEMK7_EMK240		(BIT16)
	#define		ECM_ECMEMK7_EMK240_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK240_MASK		(1)
#define		ECM_ECMEMK7_EMK239		(BIT15)
	#define		ECM_ECMEMK7_EMK239_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK239_MASK		(1)
#define		ECM_ECMEMK7_EMK238		(BIT14)
	#define		ECM_ECMEMK7_EMK238_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK238_MASK		(1)
#define		ECM_ECMEMK7_EMK237		(BIT13)
	#define		ECM_ECMEMK7_EMK237_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK237_MASK		(1)
#define		ECM_ECMEMK7_EMK236		(BIT12)
	#define		ECM_ECMEMK7_EMK236_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK236_MASK		(1)
#define		ECM_ECMEMK7_EMK235		(BIT11)
	#define		ECM_ECMEMK7_EMK235_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK235_MASK		(1)
#define		ECM_ECMEMK7_EMK234		(BIT10)
	#define		ECM_ECMEMK7_EMK234_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK234_MASK		(1)
#define		ECM_ECMEMK7_EMK233		(BIT9)
	#define		ECM_ECMEMK7_EMK233_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK233_MASK		(1)
#define		ECM_ECMEMK7_EMK232		(BIT8)
	#define		ECM_ECMEMK7_EMK232_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK232_MASK		(1)
#define		ECM_ECMEMK7_EMK231		(BIT7)
	#define		ECM_ECMEMK7_EMK231_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK231_MASK		(1)
#define		ECM_ECMEMK7_EMK230		(BIT6)
	#define		ECM_ECMEMK7_EMK230_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK230_MASK		(1)
#define		ECM_ECMEMK7_EMK229		(BIT5)
	#define		ECM_ECMEMK7_EMK229_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK229_MASK		(1)
#define		ECM_ECMEMK7_EMK228		(BIT4)
	#define		ECM_ECMEMK7_EMK228_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK228_MASK		(1)
#define		ECM_ECMEMK7_EMK227		(BIT3)
	#define		ECM_ECMEMK7_EMK227_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK227_MASK		(1)
#define		ECM_ECMEMK7_EMK226		(BIT2)
	#define		ECM_ECMEMK7_EMK226_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK226_MASK		(1)
#define		ECM_ECMEMK7_EMK225		(BIT1)
	#define		ECM_ECMEMK7_EMK225_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK225_MASK		(1)
#define		ECM_ECMEMK7_EMK224		(BIT0)
	#define		ECM_ECMEMK7_EMK224_NOMASK	(0)
	#define		ECM_ECMEMK7_EMK224_MASK		(1)

/* ECMEMK8 */
#define		ECM_ECMEMK8_EMK287		(BIT31)
	#define		ECM_ECMEMK8_EMK287_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK287_MASK		(1)
#define		ECM_ECMEMK8_EMK286		(BIT30)
	#define		ECM_ECMEMK8_EMK286_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK286_MASK		(1)
#define		ECM_ECMEMK8_EMK285		(BIT29)
	#define		ECM_ECMEMK8_EMK285_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK285_MASK		(1)
#define		ECM_ECMEMK8_EMK284		(BIT28)
	#define		ECM_ECMEMK8_EMK284_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK284_MASK		(1)
#define		ECM_ECMEMK8_EMK283		(BIT27)
	#define		ECM_ECMEMK8_EMK283_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK283_MASK		(1)
#define		ECM_ECMEMK8_EMK282		(BIT26)
	#define		ECM_ECMEMK8_EMK282_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK282_MASK		(1)
#define		ECM_ECMEMK8_EMK281		(BIT25)
	#define		ECM_ECMEMK8_EMK281_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK281_MASK		(1)
#define		ECM_ECMEMK8_EMK280		(BIT24)
	#define		ECM_ECMEMK8_EMK280_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK280_MASK		(1)
#define		ECM_ECMEMK8_EMK279		(BIT23)
	#define		ECM_ECMEMK8_EMK279_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK279_MASK		(1)
#define		ECM_ECMEMK8_EMK278		(BIT22)
	#define		ECM_ECMEMK8_EMK278_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK278_MASK		(1)
#define		ECM_ECMEMK8_EMK277		(BIT21)
	#define		ECM_ECMEMK8_EMK277_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK277_MASK		(1)
#define		ECM_ECMEMK8_EMK276		(BIT20)
	#define		ECM_ECMEMK8_EMK276_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK276_MASK		(1)
#define		ECM_ECMEMK8_EMK275		(BIT19)
	#define		ECM_ECMEMK8_EMK275_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK275_MASK		(1)
#define		ECM_ECMEMK8_EMK274		(BIT18)
	#define		ECM_ECMEMK8_EMK274_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK274_MASK		(1)
#define		ECM_ECMEMK8_EMK273		(BIT17)
	#define		ECM_ECMEMK8_EMK273_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK273_MASK		(1)
#define		ECM_ECMEMK8_EMK272		(BIT16)
	#define		ECM_ECMEMK8_EMK272_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK272_MASK		(1)
#define		ECM_ECMEMK8_EMK271		(BIT15)
	#define		ECM_ECMEMK8_EMK271_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK271_MASK		(1)
#define		ECM_ECMEMK8_EMK270		(BIT14)
	#define		ECM_ECMEMK8_EMK270_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK270_MASK		(1)
#define		ECM_ECMEMK8_EMK269		(BIT13)
	#define		ECM_ECMEMK8_EMK269_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK269_MASK		(1)
#define		ECM_ECMEMK8_EMK268		(BIT12)
	#define		ECM_ECMEMK8_EMK268_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK268_MASK		(1)
#define		ECM_ECMEMK8_EMK267		(BIT11)
	#define		ECM_ECMEMK8_EMK267_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK267_MASK		(1)
#define		ECM_ECMEMK8_EMK266		(BIT10)
	#define		ECM_ECMEMK8_EMK266_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK266_MASK		(1)
#define		ECM_ECMEMK8_EMK265		(BIT9)
	#define		ECM_ECMEMK8_EMK265_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK265_MASK		(1)
#define		ECM_ECMEMK8_EMK264		(BIT8)
	#define		ECM_ECMEMK8_EMK264_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK264_MASK		(1)
#define		ECM_ECMEMK8_EMK263		(BIT7)
	#define		ECM_ECMEMK8_EMK263_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK263_MASK		(1)
#define		ECM_ECMEMK8_EMK262		(BIT6)
	#define		ECM_ECMEMK8_EMK262_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK262_MASK		(1)
#define		ECM_ECMEMK8_EMK261		(BIT5)
	#define		ECM_ECMEMK8_EMK261_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK261_MASK		(1)
#define		ECM_ECMEMK8_EMK260		(BIT4)
	#define		ECM_ECMEMK8_EMK260_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK260_MASK		(1)
#define		ECM_ECMEMK8_EMK259		(BIT3)
	#define		ECM_ECMEMK8_EMK259_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK259_MASK		(1)
#define		ECM_ECMEMK8_EMK258		(BIT2)
	#define		ECM_ECMEMK8_EMK258_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK258_MASK		(1)
#define		ECM_ECMEMK8_EMK257		(BIT1)
	#define		ECM_ECMEMK8_EMK257_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK257_MASK		(1)
#define		ECM_ECMEMK8_EMK256		(BIT0)
	#define		ECM_ECMEMK8_EMK256_NOMASK	(0)
	#define		ECM_ECMEMK8_EMK256_MASK		(1)

/* ECMEMK9 */
#define		ECM_ECMEMK9_EMK319		(BIT31)
	#define		ECM_ECMEMK9_EMK319_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK319_MASK		(1)
#define		ECM_ECMEMK9_EMK318		(BIT30)
	#define		ECM_ECMEMK9_EMK318_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK318_MASK		(1)
#define		ECM_ECMEMK9_EMK317		(BIT29)
	#define		ECM_ECMEMK9_EMK317_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK317_MASK		(1)
#define		ECM_ECMEMK9_EMK316		(BIT28)
	#define		ECM_ECMEMK9_EMK316_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK316_MASK		(1)
#define		ECM_ECMEMK9_EMK315		(BIT27)
	#define		ECM_ECMEMK9_EMK315_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK315_MASK		(1)
#define		ECM_ECMEMK9_EMK314		(BIT26)
	#define		ECM_ECMEMK9_EMK314_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK314_MASK		(1)
#define		ECM_ECMEMK9_EMK313		(BIT25)
	#define		ECM_ECMEMK9_EMK313_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK313_MASK		(1)
#define		ECM_ECMEMK9_EMK312		(BIT24)
	#define		ECM_ECMEMK9_EMK312_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK312_MASK		(1)
#define		ECM_ECMEMK9_EMK311		(BIT23)
	#define		ECM_ECMEMK9_EMK311_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK311_MASK		(1)
#define		ECM_ECMEMK9_EMK310		(BIT22)
	#define		ECM_ECMEMK9_EMK310_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK310_MASK		(1)
#define		ECM_ECMEMK9_EMK309		(BIT21)
	#define		ECM_ECMEMK9_EMK309_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK309_MASK		(1)
#define		ECM_ECMEMK9_EMK308		(BIT20)
	#define		ECM_ECMEMK9_EMK308_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK308_MASK		(1)
#define		ECM_ECMEMK9_EMK307		(BIT19)
	#define		ECM_ECMEMK9_EMK307_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK307_MASK		(1)
#define		ECM_ECMEMK9_EMK306		(BIT18)
	#define		ECM_ECMEMK9_EMK306_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK306_MASK		(1)
#define		ECM_ECMEMK9_EMK305		(BIT17)
	#define		ECM_ECMEMK9_EMK305_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK305_MASK		(1)
#define		ECM_ECMEMK9_EMK304		(BIT16)
	#define		ECM_ECMEMK9_EMK304_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK304_MASK		(1)
#define		ECM_ECMEMK9_EMK303		(BIT15)
	#define		ECM_ECMEMK9_EMK303_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK303_MASK		(1)
#define		ECM_ECMEMK9_EMK302		(BIT14)
	#define		ECM_ECMEMK9_EMK302_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK302_MASK		(1)
#define		ECM_ECMEMK9_EMK301		(BIT13)
	#define		ECM_ECMEMK9_EMK301_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK301_MASK		(1)
#define		ECM_ECMEMK9_EMK300		(BIT12)
	#define		ECM_ECMEMK9_EMK300_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK300_MASK		(1)
#define		ECM_ECMEMK9_EMK299		(BIT11)
	#define		ECM_ECMEMK9_EMK299_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK299_MASK		(1)
#define		ECM_ECMEMK9_EMK298		(BIT10)
	#define		ECM_ECMEMK9_EMK298_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK298_MASK		(1)
#define		ECM_ECMEMK9_EMK297		(BIT9)
	#define		ECM_ECMEMK9_EMK297_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK297_MASK		(1)
#define		ECM_ECMEMK9_EMK296		(BIT8)
	#define		ECM_ECMEMK9_EMK296_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK296_MASK		(1)
#define		ECM_ECMEMK9_EMK295		(BIT7)
	#define		ECM_ECMEMK9_EMK295_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK295_MASK		(1)
#define		ECM_ECMEMK9_EMK294		(BIT6)
	#define		ECM_ECMEMK9_EMK294_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK294_MASK		(1)
#define		ECM_ECMEMK9_EMK293		(BIT5)
	#define		ECM_ECMEMK9_EMK293_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK293_MASK		(1)
#define		ECM_ECMEMK9_EMK292		(BIT4)
	#define		ECM_ECMEMK9_EMK292_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK292_MASK		(1)
#define		ECM_ECMEMK9_EMK291		(BIT3)
	#define		ECM_ECMEMK9_EMK291_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK291_MASK		(1)
#define		ECM_ECMEMK9_EMK290		(BIT2)
	#define		ECM_ECMEMK9_EMK290_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK290_MASK		(1)
#define		ECM_ECMEMK9_EMK289		(BIT1)
	#define		ECM_ECMEMK9_EMK289_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK289_MASK		(1)
#define		ECM_ECMEMK9_EMK288		(BIT0)
	#define		ECM_ECMEMK9_EMK288_NOMASK	(0)
	#define		ECM_ECMEMK9_EMK288_MASK		(1)

/* ECMEMK10 */
#define		ECM_ECMEMK10_EMK351		(BIT31)
	#define		ECM_ECMEMK10_EMK351_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK351_MASK		(1)
#define		ECM_ECMEMK10_EMK350		(BIT30)
	#define		ECM_ECMEMK10_EMK350_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK350_MASK		(1)
#define		ECM_ECMEMK10_EMK349		(BIT29)
	#define		ECM_ECMEMK10_EMK349_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK349_MASK		(1)
#define		ECM_ECMEMK10_EMK348		(BIT28)
	#define		ECM_ECMEMK10_EMK348_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK348_MASK		(1)
#define		ECM_ECMEMK10_EMK347		(BIT27)
	#define		ECM_ECMEMK10_EMK347_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK347_MASK		(1)
#define		ECM_ECMEMK10_EMK346		(BIT26)
	#define		ECM_ECMEMK10_EMK346_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK346_MASK		(1)
#define		ECM_ECMEMK10_EMK345		(BIT25)
	#define		ECM_ECMEMK10_EMK345_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK345_MASK		(1)
#define		ECM_ECMEMK10_EMK344		(BIT24)
	#define		ECM_ECMEMK10_EMK344_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK344_MASK		(1)
#define		ECM_ECMEMK10_EMK343		(BIT23)
	#define		ECM_ECMEMK10_EMK343_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK343_MASK		(1)
#define		ECM_ECMEMK10_EMK342		(BIT22)
	#define		ECM_ECMEMK10_EMK342_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK342_MASK		(1)
#define		ECM_ECMEMK10_EMK341		(BIT21)
	#define		ECM_ECMEMK10_EMK341_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK341_MASK		(1)
#define		ECM_ECMEMK10_EMK340		(BIT20)
	#define		ECM_ECMEMK10_EMK340_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK340_MASK		(1)
#define		ECM_ECMEMK10_EMK339		(BIT19)
	#define		ECM_ECMEMK10_EMK339_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK339_MASK		(1)
#define		ECM_ECMEMK10_EMK338		(BIT18)
	#define		ECM_ECMEMK10_EMK338_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK338_MASK		(1)
#define		ECM_ECMEMK10_EMK337		(BIT17)
	#define		ECM_ECMEMK10_EMK337_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK337_MASK		(1)
#define		ECM_ECMEMK10_EMK336		(BIT16)
	#define		ECM_ECMEMK10_EMK336_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK336_MASK		(1)
#define		ECM_ECMEMK10_EMK335		(BIT15)
	#define		ECM_ECMEMK10_EMK335_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK335_MASK		(1)
#define		ECM_ECMEMK10_EMK334		(BIT14)
	#define		ECM_ECMEMK10_EMK334_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK334_MASK		(1)
#define		ECM_ECMEMK10_EMK333		(BIT13)
	#define		ECM_ECMEMK10_EMK333_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK333_MASK		(1)
#define		ECM_ECMEMK10_EMK332		(BIT12)
	#define		ECM_ECMEMK10_EMK332_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK332_MASK		(1)
#define		ECM_ECMEMK10_EMK331		(BIT11)
	#define		ECM_ECMEMK10_EMK331_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK331_MASK		(1)
#define		ECM_ECMEMK10_EMK330		(BIT10)
	#define		ECM_ECMEMK10_EMK330_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK330_MASK		(1)
#define		ECM_ECMEMK10_EMK329		(BIT9)
	#define		ECM_ECMEMK10_EMK329_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK329_MASK		(1)
#define		ECM_ECMEMK10_EMK328		(BIT8)
	#define		ECM_ECMEMK10_EMK328_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK328_MASK		(1)
#define		ECM_ECMEMK10_EMK327		(BIT7)
	#define		ECM_ECMEMK10_EMK327_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK327_MASK		(1)
#define		ECM_ECMEMK10_EMK326		(BIT6)
	#define		ECM_ECMEMK10_EMK326_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK326_MASK		(1)
#define		ECM_ECMEMK10_EMK325		(BIT5)
	#define		ECM_ECMEMK10_EMK325_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK325_MASK		(1)
#define		ECM_ECMEMK10_EMK324		(BIT4)
	#define		ECM_ECMEMK10_EMK324_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK324_MASK		(1)
#define		ECM_ECMEMK10_EMK323		(BIT3)
	#define		ECM_ECMEMK10_EMK323_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK323_MASK		(1)
#define		ECM_ECMEMK10_EMK322		(BIT2)
	#define		ECM_ECMEMK10_EMK322_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK322_MASK		(1)
#define		ECM_ECMEMK10_EMK321		(BIT1)
	#define		ECM_ECMEMK10_EMK321_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK321_MASK		(1)
#define		ECM_ECMEMK10_EMK320		(BIT0)
	#define		ECM_ECMEMK10_EMK320_NOMASK	(0)
	#define		ECM_ECMEMK10_EMK320_MASK		(1)

/* ECMETMK0_0 */
#define		ECM_ECMETMK0_0_ETMK0_031		(BIT31)
	#define		ECM_ECMETMK0_0_ETMK0_031_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_031_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_030		(BIT30)
	#define		ECM_ECMETMK0_0_ETMK0_030_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_030_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_029		(BIT29)
	#define		ECM_ECMETMK0_0_ETMK0_029_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_029_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_028		(BIT28)
	#define		ECM_ECMETMK0_0_ETMK0_028_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_028_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_027		(BIT27)
	#define		ECM_ECMETMK0_0_ETMK0_027_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_027_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_026		(BIT26)
	#define		ECM_ECMETMK0_0_ETMK0_026_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_026_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_025		(BIT25)
	#define		ECM_ECMETMK0_0_ETMK0_025_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_025_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_024		(BIT24)
	#define		ECM_ECMETMK0_0_ETMK0_024_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_024_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_023		(BIT23)
	#define		ECM_ECMETMK0_0_ETMK0_023_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_023_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_022		(BIT22)
	#define		ECM_ECMETMK0_0_ETMK0_022_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_022_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_021		(BIT21)
	#define		ECM_ECMETMK0_0_ETMK0_021_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_021_MASK		(1)
#define		ECM_ECMETMK0_0_ETMK0_020		(BIT20)
	#define		ECM_ECMETMK0_0_ETMK0_020_NOMASK	(0)
	#define		ECM_ECMETMK0_0_ETMK0_020_MASK		(1)

/* ECMETMK0_1 */
#define		ECM_ECMETMK0_1_ETMK0_063		(BIT31)
	#define		ECM_ECMETMK0_1_ETMK0_063_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_063_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_062		(BIT30)
	#define		ECM_ECMETMK0_1_ETMK0_062_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_062_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_061		(BIT29)
	#define		ECM_ECMETMK0_1_ETMK0_061_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_061_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_060		(BIT28)
	#define		ECM_ECMETMK0_1_ETMK0_060_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_060_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_059		(BIT27)
	#define		ECM_ECMETMK0_1_ETMK0_059_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_059_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_058		(BIT26)
	#define		ECM_ECMETMK0_1_ETMK0_058_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_058_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_057		(BIT25)
	#define		ECM_ECMETMK0_1_ETMK0_057_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_057_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_056		(BIT24)
	#define		ECM_ECMETMK0_1_ETMK0_056_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_056_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_055		(BIT23)
	#define		ECM_ECMETMK0_1_ETMK0_055_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_055_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_054		(BIT22)
	#define		ECM_ECMETMK0_1_ETMK0_054_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_054_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_053		(BIT21)
	#define		ECM_ECMETMK0_1_ETMK0_053_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_053_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_052		(BIT20)
	#define		ECM_ECMETMK0_1_ETMK0_052_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_052_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_051		(BIT19)
	#define		ECM_ECMETMK0_1_ETMK0_051_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_051_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_050		(BIT18)
	#define		ECM_ECMETMK0_1_ETMK0_050_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_050_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_049		(BIT17)
	#define		ECM_ECMETMK0_1_ETMK0_049_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_049_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_048		(BIT16)
	#define		ECM_ECMETMK0_1_ETMK0_048_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_048_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_047		(BIT15)
	#define		ECM_ECMETMK0_1_ETMK0_047_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_047_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_046		(BIT14)
	#define		ECM_ECMETMK0_1_ETMK0_046_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_046_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_045		(BIT13)
	#define		ECM_ECMETMK0_1_ETMK0_045_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_045_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_044		(BIT12)
	#define		ECM_ECMETMK0_1_ETMK0_044_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_044_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_043		(BIT11)
	#define		ECM_ECMETMK0_1_ETMK0_043_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_043_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_042		(BIT10)
	#define		ECM_ECMETMK0_1_ETMK0_042_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_042_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_041		(BIT9)
	#define		ECM_ECMETMK0_1_ETMK0_041_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_041_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_040		(BIT8)
	#define		ECM_ECMETMK0_1_ETMK0_040_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_040_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_039		(BIT7)
	#define		ECM_ECMETMK0_1_ETMK0_039_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_039_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_038		(BIT6)
	#define		ECM_ECMETMK0_1_ETMK0_038_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_038_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_037		(BIT5)
	#define		ECM_ECMETMK0_1_ETMK0_037_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_037_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_036		(BIT4)
	#define		ECM_ECMETMK0_1_ETMK0_036_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_036_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_035		(BIT3)
	#define		ECM_ECMETMK0_1_ETMK0_035_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_035_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_034		(BIT2)
	#define		ECM_ECMETMK0_1_ETMK0_034_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_034_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_033		(BIT1)
	#define		ECM_ECMETMK0_1_ETMK0_033_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_033_MASK		(1)
#define		ECM_ECMETMK0_1_ETMK0_032		(BIT0)
	#define		ECM_ECMETMK0_1_ETMK0_032_NOMASK	(0)
	#define		ECM_ECMETMK0_1_ETMK0_032_MASK		(1)

/* ECMETMK0_2 */
#define		ECM_ECMETMK0_2_ETMK0_095		(BIT31)
	#define		ECM_ECMETMK0_2_ETMK0_095_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_095_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_094		(BIT30)
	#define		ECM_ECMETMK0_2_ETMK0_094_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_094_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_093		(BIT29)
	#define		ECM_ECMETMK0_2_ETMK0_093_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_093_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_092		(BIT28)
	#define		ECM_ECMETMK0_2_ETMK0_092_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_092_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_091		(BIT27)
	#define		ECM_ECMETMK0_2_ETMK0_091_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_091_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_090		(BIT26)
	#define		ECM_ECMETMK0_2_ETMK0_090_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_090_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_089		(BIT25)
	#define		ECM_ECMETMK0_2_ETMK0_089_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_089_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_088		(BIT24)
	#define		ECM_ECMETMK0_2_ETMK0_088_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_088_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_087		(BIT23)
	#define		ECM_ECMETMK0_2_ETMK0_087_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_087_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_086		(BIT22)
	#define		ECM_ECMETMK0_2_ETMK0_086_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_086_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_085		(BIT21)
	#define		ECM_ECMETMK0_2_ETMK0_085_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_085_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_084		(BIT20)
	#define		ECM_ECMETMK0_2_ETMK0_084_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_084_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_083		(BIT19)
	#define		ECM_ECMETMK0_2_ETMK0_083_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_083_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_082		(BIT18)
	#define		ECM_ECMETMK0_2_ETMK0_082_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_082_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_081		(BIT17)
	#define		ECM_ECMETMK0_2_ETMK0_081_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_081_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_080		(BIT16)
	#define		ECM_ECMETMK0_2_ETMK0_080_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_080_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_079		(BIT15)
	#define		ECM_ECMETMK0_2_ETMK0_079_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_079_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_078		(BIT14)
	#define		ECM_ECMETMK0_2_ETMK0_078_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_078_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_077		(BIT13)
	#define		ECM_ECMETMK0_2_ETMK0_077_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_077_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_076		(BIT12)
	#define		ECM_ECMETMK0_2_ETMK0_076_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_076_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_075		(BIT11)
	#define		ECM_ECMETMK0_2_ETMK0_075_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_075_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_074		(BIT10)
	#define		ECM_ECMETMK0_2_ETMK0_074_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_074_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_073		(BIT9)
	#define		ECM_ECMETMK0_2_ETMK0_073_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_073_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_072		(BIT8)
	#define		ECM_ECMETMK0_2_ETMK0_072_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_072_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_071		(BIT7)
	#define		ECM_ECMETMK0_2_ETMK0_071_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_071_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_070		(BIT6)
	#define		ECM_ECMETMK0_2_ETMK0_070_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_070_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_069		(BIT5)
	#define		ECM_ECMETMK0_2_ETMK0_069_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_069_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_068		(BIT4)
	#define		ECM_ECMETMK0_2_ETMK0_068_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_068_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_067		(BIT3)
	#define		ECM_ECMETMK0_2_ETMK0_067_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_067_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_066		(BIT2)
	#define		ECM_ECMETMK0_2_ETMK0_066_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_066_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_065		(BIT1)
	#define		ECM_ECMETMK0_2_ETMK0_065_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_065_MASK		(1)
#define		ECM_ECMETMK0_2_ETMK0_064		(BIT0)
	#define		ECM_ECMETMK0_2_ETMK0_064_NOMASK	(0)
	#define		ECM_ECMETMK0_2_ETMK0_064_MASK		(1)

/* ECMETMK0_3 */
#define		ECM_ECMETMK0_3_ETMK0_127		(BIT31)
	#define		ECM_ECMETMK0_3_ETMK0_127_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_127_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_126		(BIT30)
	#define		ECM_ECMETMK0_3_ETMK0_126_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_126_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_125		(BIT29)
	#define		ECM_ECMETMK0_3_ETMK0_125_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_125_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_124		(BIT28)
	#define		ECM_ECMETMK0_3_ETMK0_124_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_124_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_123		(BIT27)
	#define		ECM_ECMETMK0_3_ETMK0_123_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_123_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_122		(BIT26)
	#define		ECM_ECMETMK0_3_ETMK0_122_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_122_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_121		(BIT25)
	#define		ECM_ECMETMK0_3_ETMK0_121_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_121_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_120		(BIT24)
	#define		ECM_ECMETMK0_3_ETMK0_120_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_120_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_119		(BIT23)
	#define		ECM_ECMETMK0_3_ETMK0_119_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_119_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_118		(BIT22)
	#define		ECM_ECMETMK0_3_ETMK0_118_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_118_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_117		(BIT21)
	#define		ECM_ECMETMK0_3_ETMK0_117_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_117_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_116		(BIT20)
	#define		ECM_ECMETMK0_3_ETMK0_116_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_116_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_115		(BIT19)
	#define		ECM_ECMETMK0_3_ETMK0_115_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_115_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_114		(BIT18)
	#define		ECM_ECMETMK0_3_ETMK0_114_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_114_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_113		(BIT17)
	#define		ECM_ECMETMK0_3_ETMK0_113_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_113_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_112		(BIT16)
	#define		ECM_ECMETMK0_3_ETMK0_112_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_112_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_111		(BIT15)
	#define		ECM_ECMETMK0_3_ETMK0_111_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_111_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_110		(BIT14)
	#define		ECM_ECMETMK0_3_ETMK0_110_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_110_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_109		(BIT13)
	#define		ECM_ECMETMK0_3_ETMK0_109_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_109_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_108		(BIT12)
	#define		ECM_ECMETMK0_3_ETMK0_108_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_108_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_107		(BIT11)
	#define		ECM_ECMETMK0_3_ETMK0_107_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_107_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_106		(BIT10)
	#define		ECM_ECMETMK0_3_ETMK0_106_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_106_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_105		(BIT9)
	#define		ECM_ECMETMK0_3_ETMK0_105_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_105_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_104		(BIT8)
	#define		ECM_ECMETMK0_3_ETMK0_104_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_104_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_103		(BIT7)
	#define		ECM_ECMETMK0_3_ETMK0_103_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_103_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_102		(BIT6)
	#define		ECM_ECMETMK0_3_ETMK0_102_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_102_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_101		(BIT5)
	#define		ECM_ECMETMK0_3_ETMK0_101_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_101_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_100		(BIT4)
	#define		ECM_ECMETMK0_3_ETMK0_100_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_100_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_099		(BIT3)
	#define		ECM_ECMETMK0_3_ETMK0_099_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_099_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_098		(BIT2)
	#define		ECM_ECMETMK0_3_ETMK0_098_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_098_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_097		(BIT1)
	#define		ECM_ECMETMK0_3_ETMK0_097_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_097_MASK		(1)
#define		ECM_ECMETMK0_3_ETMK0_096		(BIT0)
	#define		ECM_ECMETMK0_3_ETMK0_096_NOMASK	(0)
	#define		ECM_ECMETMK0_3_ETMK0_096_MASK		(1)

/* ECMETMK0_4 */
#define		ECM_ECMETMK0_4_ETMK0_159		(BIT31)
	#define		ECM_ECMETMK0_4_ETMK0_159_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_159_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_158		(BIT30)
	#define		ECM_ECMETMK0_4_ETMK0_158_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_158_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_157		(BIT29)
	#define		ECM_ECMETMK0_4_ETMK0_157_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_157_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_156		(BIT28)
	#define		ECM_ECMETMK0_4_ETMK0_156_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_156_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_155		(BIT27)
	#define		ECM_ECMETMK0_4_ETMK0_155_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_155_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_154		(BIT26)
	#define		ECM_ECMETMK0_4_ETMK0_154_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_154_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_153		(BIT25)
	#define		ECM_ECMETMK0_4_ETMK0_153_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_153_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_152		(BIT24)
	#define		ECM_ECMETMK0_4_ETMK0_152_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_152_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_151		(BIT23)
	#define		ECM_ECMETMK0_4_ETMK0_151_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_151_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_150		(BIT22)
	#define		ECM_ECMETMK0_4_ETMK0_150_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_150_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_149		(BIT21)
	#define		ECM_ECMETMK0_4_ETMK0_149_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_149_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_148		(BIT20)
	#define		ECM_ECMETMK0_4_ETMK0_148_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_148_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_147		(BIT19)
	#define		ECM_ECMETMK0_4_ETMK0_147_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_147_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_146		(BIT18)
	#define		ECM_ECMETMK0_4_ETMK0_146_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_146_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_145		(BIT17)
	#define		ECM_ECMETMK0_4_ETMK0_145_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_145_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_144		(BIT16)
	#define		ECM_ECMETMK0_4_ETMK0_144_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_144_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_143		(BIT15)
	#define		ECM_ECMETMK0_4_ETMK0_143_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_143_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_142		(BIT14)
	#define		ECM_ECMETMK0_4_ETMK0_142_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_142_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_141		(BIT13)
	#define		ECM_ECMETMK0_4_ETMK0_141_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_141_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_140		(BIT12)
	#define		ECM_ECMETMK0_4_ETMK0_140_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_140_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_139		(BIT11)
	#define		ECM_ECMETMK0_4_ETMK0_139_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_139_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_138		(BIT10)
	#define		ECM_ECMETMK0_4_ETMK0_138_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_138_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_137		(BIT9)
	#define		ECM_ECMETMK0_4_ETMK0_137_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_137_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_136		(BIT8)
	#define		ECM_ECMETMK0_4_ETMK0_136_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_136_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_135		(BIT7)
	#define		ECM_ECMETMK0_4_ETMK0_135_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_135_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_134		(BIT6)
	#define		ECM_ECMETMK0_4_ETMK0_134_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_134_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_133		(BIT5)
	#define		ECM_ECMETMK0_4_ETMK0_133_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_133_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_132		(BIT4)
	#define		ECM_ECMETMK0_4_ETMK0_132_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_132_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_131		(BIT3)
	#define		ECM_ECMETMK0_4_ETMK0_131_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_131_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_130		(BIT2)
	#define		ECM_ECMETMK0_4_ETMK0_130_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_130_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_129		(BIT1)
	#define		ECM_ECMETMK0_4_ETMK0_129_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_129_MASK		(1)
#define		ECM_ECMETMK0_4_ETMK0_128		(BIT0)
	#define		ECM_ECMETMK0_4_ETMK0_128_NOMASK	(0)
	#define		ECM_ECMETMK0_4_ETMK0_128_MASK		(1)

/* ECMETMK0_5 */
#define		ECM_ECMETMK0_5_ETMK0_191		(BIT31)
	#define		ECM_ECMETMK0_5_ETMK0_191_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_191_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_190		(BIT30)
	#define		ECM_ECMETMK0_5_ETMK0_190_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_190_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_189		(BIT29)
	#define		ECM_ECMETMK0_5_ETMK0_189_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_189_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_188		(BIT28)
	#define		ECM_ECMETMK0_5_ETMK0_188_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_188_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_187		(BIT27)
	#define		ECM_ECMETMK0_5_ETMK0_187_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_187_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_186		(BIT26)
	#define		ECM_ECMETMK0_5_ETMK0_186_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_186_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_185		(BIT25)
	#define		ECM_ECMETMK0_5_ETMK0_185_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_185_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_184		(BIT24)
	#define		ECM_ECMETMK0_5_ETMK0_184_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_184_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_183		(BIT23)
	#define		ECM_ECMETMK0_5_ETMK0_183_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_183_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_182		(BIT22)
	#define		ECM_ECMETMK0_5_ETMK0_182_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_182_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_181		(BIT21)
	#define		ECM_ECMETMK0_5_ETMK0_181_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_181_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_180		(BIT20)
	#define		ECM_ECMETMK0_5_ETMK0_180_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_180_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_179		(BIT19)
	#define		ECM_ECMETMK0_5_ETMK0_179_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_179_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_178		(BIT18)
	#define		ECM_ECMETMK0_5_ETMK0_178_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_178_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_177		(BIT17)
	#define		ECM_ECMETMK0_5_ETMK0_177_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_177_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_176		(BIT16)
	#define		ECM_ECMETMK0_5_ETMK0_176_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_176_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_175		(BIT15)
	#define		ECM_ECMETMK0_5_ETMK0_175_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_175_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_174		(BIT14)
	#define		ECM_ECMETMK0_5_ETMK0_174_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_174_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_173		(BIT13)
	#define		ECM_ECMETMK0_5_ETMK0_173_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_173_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_172		(BIT12)
	#define		ECM_ECMETMK0_5_ETMK0_172_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_172_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_171		(BIT11)
	#define		ECM_ECMETMK0_5_ETMK0_171_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_171_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_170		(BIT10)
	#define		ECM_ECMETMK0_5_ETMK0_170_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_170_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_169		(BIT9)
	#define		ECM_ECMETMK0_5_ETMK0_169_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_169_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_168		(BIT8)
	#define		ECM_ECMETMK0_5_ETMK0_168_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_168_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_167		(BIT7)
	#define		ECM_ECMETMK0_5_ETMK0_167_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_167_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_166		(BIT6)
	#define		ECM_ECMETMK0_5_ETMK0_166_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_166_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_165		(BIT5)
	#define		ECM_ECMETMK0_5_ETMK0_165_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_165_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_164		(BIT4)
	#define		ECM_ECMETMK0_5_ETMK0_164_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_164_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_163		(BIT3)
	#define		ECM_ECMETMK0_5_ETMK0_163_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_163_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_162		(BIT2)
	#define		ECM_ECMETMK0_5_ETMK0_162_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_162_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_161		(BIT1)
	#define		ECM_ECMETMK0_5_ETMK0_161_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_161_MASK		(1)
#define		ECM_ECMETMK0_5_ETMK0_160		(BIT0)
	#define		ECM_ECMETMK0_5_ETMK0_160_NOMASK	(0)
	#define		ECM_ECMETMK0_5_ETMK0_160_MASK		(1)

/* ECMETMK0_6 */
#define		ECM_ECMETMK0_6_ETMK0_223		(BIT31)
	#define		ECM_ECMETMK0_6_ETMK0_223_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_223_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_222		(BIT30)
	#define		ECM_ECMETMK0_6_ETMK0_222_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_222_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_221		(BIT29)
	#define		ECM_ECMETMK0_6_ETMK0_221_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_221_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_220		(BIT28)
	#define		ECM_ECMETMK0_6_ETMK0_220_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_220_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_219		(BIT27)
	#define		ECM_ECMETMK0_6_ETMK0_219_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_219_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_218		(BIT26)
	#define		ECM_ECMETMK0_6_ETMK0_218_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_218_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_217		(BIT25)
	#define		ECM_ECMETMK0_6_ETMK0_217_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_217_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_216		(BIT24)
	#define		ECM_ECMETMK0_6_ETMK0_216_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_216_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_215		(BIT23)
	#define		ECM_ECMETMK0_6_ETMK0_215_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_215_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_214		(BIT22)
	#define		ECM_ECMETMK0_6_ETMK0_214_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_214_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_213		(BIT21)
	#define		ECM_ECMETMK0_6_ETMK0_213_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_213_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_212		(BIT20)
	#define		ECM_ECMETMK0_6_ETMK0_212_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_212_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_211		(BIT19)
	#define		ECM_ECMETMK0_6_ETMK0_211_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_211_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_210		(BIT18)
	#define		ECM_ECMETMK0_6_ETMK0_210_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_210_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_209		(BIT17)
	#define		ECM_ECMETMK0_6_ETMK0_209_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_209_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_208		(BIT16)
	#define		ECM_ECMETMK0_6_ETMK0_208_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_208_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_207		(BIT15)
	#define		ECM_ECMETMK0_6_ETMK0_207_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_207_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_206		(BIT14)
	#define		ECM_ECMETMK0_6_ETMK0_206_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_206_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_205		(BIT13)
	#define		ECM_ECMETMK0_6_ETMK0_205_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_205_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_204		(BIT12)
	#define		ECM_ECMETMK0_6_ETMK0_204_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_204_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_203		(BIT11)
	#define		ECM_ECMETMK0_6_ETMK0_203_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_203_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_202		(BIT10)
	#define		ECM_ECMETMK0_6_ETMK0_202_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_202_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_201		(BIT9)
	#define		ECM_ECMETMK0_6_ETMK0_201_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_201_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_200		(BIT8)
	#define		ECM_ECMETMK0_6_ETMK0_200_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_200_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_199		(BIT7)
	#define		ECM_ECMETMK0_6_ETMK0_199_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_199_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_198		(BIT6)
	#define		ECM_ECMETMK0_6_ETMK0_198_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_198_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_197		(BIT5)
	#define		ECM_ECMETMK0_6_ETMK0_197_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_197_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_196		(BIT4)
	#define		ECM_ECMETMK0_6_ETMK0_196_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_196_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_195		(BIT3)
	#define		ECM_ECMETMK0_6_ETMK0_195_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_195_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_194		(BIT2)
	#define		ECM_ECMETMK0_6_ETMK0_194_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_194_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_193		(BIT1)
	#define		ECM_ECMETMK0_6_ETMK0_193_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_193_MASK		(1)
#define		ECM_ECMETMK0_6_ETMK0_192		(BIT0)
	#define		ECM_ECMETMK0_6_ETMK0_192_NOMASK	(0)
	#define		ECM_ECMETMK0_6_ETMK0_192_MASK		(1)

/* ECMETMK0_7 */
#define		ECM_ECMETMK0_7_ETMK0_255		(BIT31)
	#define		ECM_ECMETMK0_7_ETMK0_255_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_255_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_254		(BIT30)
	#define		ECM_ECMETMK0_7_ETMK0_254_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_254_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_253		(BIT29)
	#define		ECM_ECMETMK0_7_ETMK0_253_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_253_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_252		(BIT28)
	#define		ECM_ECMETMK0_7_ETMK0_252_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_252_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_251		(BIT27)
	#define		ECM_ECMETMK0_7_ETMK0_251_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_251_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_250		(BIT26)
	#define		ECM_ECMETMK0_7_ETMK0_250_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_250_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_249		(BIT25)
	#define		ECM_ECMETMK0_7_ETMK0_249_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_249_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_248		(BIT24)
	#define		ECM_ECMETMK0_7_ETMK0_248_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_248_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_247		(BIT23)
	#define		ECM_ECMETMK0_7_ETMK0_247_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_247_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_246		(BIT22)
	#define		ECM_ECMETMK0_7_ETMK0_246_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_246_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_245		(BIT21)
	#define		ECM_ECMETMK0_7_ETMK0_245_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_245_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_244		(BIT20)
	#define		ECM_ECMETMK0_7_ETMK0_244_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_244_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_243		(BIT19)
	#define		ECM_ECMETMK0_7_ETMK0_243_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_243_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_242		(BIT18)
	#define		ECM_ECMETMK0_7_ETMK0_242_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_242_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_241		(BIT17)
	#define		ECM_ECMETMK0_7_ETMK0_241_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_241_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_240		(BIT16)
	#define		ECM_ECMETMK0_7_ETMK0_240_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_240_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_239		(BIT15)
	#define		ECM_ECMETMK0_7_ETMK0_239_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_239_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_238		(BIT14)
	#define		ECM_ECMETMK0_7_ETMK0_238_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_238_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_237		(BIT13)
	#define		ECM_ECMETMK0_7_ETMK0_237_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_237_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_236		(BIT12)
	#define		ECM_ECMETMK0_7_ETMK0_236_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_236_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_235		(BIT11)
	#define		ECM_ECMETMK0_7_ETMK0_235_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_235_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_234		(BIT10)
	#define		ECM_ECMETMK0_7_ETMK0_234_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_234_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_233		(BIT9)
	#define		ECM_ECMETMK0_7_ETMK0_233_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_233_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_232		(BIT8)
	#define		ECM_ECMETMK0_7_ETMK0_232_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_232_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_231		(BIT7)
	#define		ECM_ECMETMK0_7_ETMK0_231_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_231_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_230		(BIT6)
	#define		ECM_ECMETMK0_7_ETMK0_230_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_230_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_229		(BIT5)
	#define		ECM_ECMETMK0_7_ETMK0_229_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_229_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_228		(BIT4)
	#define		ECM_ECMETMK0_7_ETMK0_228_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_228_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_227		(BIT3)
	#define		ECM_ECMETMK0_7_ETMK0_227_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_227_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_226		(BIT2)
	#define		ECM_ECMETMK0_7_ETMK0_226_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_226_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_225		(BIT1)
	#define		ECM_ECMETMK0_7_ETMK0_225_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_225_MASK		(1)
#define		ECM_ECMETMK0_7_ETMK0_224		(BIT0)
	#define		ECM_ECMETMK0_7_ETMK0_224_NOMASK	(0)
	#define		ECM_ECMETMK0_7_ETMK0_224_MASK		(1)

/* ECMETMK0_8 */
#define		ECM_ECMETMK0_8_ETMK0_287		(BIT31)
	#define		ECM_ECMETMK0_8_ETMK0_287_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_287_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_286		(BIT30)
	#define		ECM_ECMETMK0_8_ETMK0_286_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_286_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_285		(BIT29)
	#define		ECM_ECMETMK0_8_ETMK0_285_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_285_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_284		(BIT28)
	#define		ECM_ECMETMK0_8_ETMK0_284_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_284_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_283		(BIT27)
	#define		ECM_ECMETMK0_8_ETMK0_283_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_283_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_282		(BIT26)
	#define		ECM_ECMETMK0_8_ETMK0_282_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_282_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_281		(BIT25)
	#define		ECM_ECMETMK0_8_ETMK0_281_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_281_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_280		(BIT24)
	#define		ECM_ECMETMK0_8_ETMK0_280_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_280_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_279		(BIT23)
	#define		ECM_ECMETMK0_8_ETMK0_279_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_279_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_278		(BIT22)
	#define		ECM_ECMETMK0_8_ETMK0_278_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_278_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_277		(BIT21)
	#define		ECM_ECMETMK0_8_ETMK0_277_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_277_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_276		(BIT20)
	#define		ECM_ECMETMK0_8_ETMK0_276_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_276_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_275		(BIT19)
	#define		ECM_ECMETMK0_8_ETMK0_275_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_275_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_274		(BIT18)
	#define		ECM_ECMETMK0_8_ETMK0_274_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_274_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_273		(BIT17)
	#define		ECM_ECMETMK0_8_ETMK0_273_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_273_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_272		(BIT16)
	#define		ECM_ECMETMK0_8_ETMK0_272_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_272_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_271		(BIT15)
	#define		ECM_ECMETMK0_8_ETMK0_271_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_271_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_270		(BIT14)
	#define		ECM_ECMETMK0_8_ETMK0_270_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_270_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_269		(BIT13)
	#define		ECM_ECMETMK0_8_ETMK0_269_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_269_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_268		(BIT12)
	#define		ECM_ECMETMK0_8_ETMK0_268_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_268_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_267		(BIT11)
	#define		ECM_ECMETMK0_8_ETMK0_267_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_267_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_266		(BIT10)
	#define		ECM_ECMETMK0_8_ETMK0_266_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_266_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_265		(BIT9)
	#define		ECM_ECMETMK0_8_ETMK0_265_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_265_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_264		(BIT8)
	#define		ECM_ECMETMK0_8_ETMK0_264_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_264_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_263		(BIT7)
	#define		ECM_ECMETMK0_8_ETMK0_263_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_263_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_262		(BIT6)
	#define		ECM_ECMETMK0_8_ETMK0_262_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_262_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_261		(BIT5)
	#define		ECM_ECMETMK0_8_ETMK0_261_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_261_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_260		(BIT4)
	#define		ECM_ECMETMK0_8_ETMK0_260_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_260_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_259		(BIT3)
	#define		ECM_ECMETMK0_8_ETMK0_259_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_259_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_258		(BIT2)
	#define		ECM_ECMETMK0_8_ETMK0_258_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_258_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_257		(BIT1)
	#define		ECM_ECMETMK0_8_ETMK0_257_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_257_MASK		(1)
#define		ECM_ECMETMK0_8_ETMK0_256		(BIT0)
	#define		ECM_ECMETMK0_8_ETMK0_256_NOMASK	(0)
	#define		ECM_ECMETMK0_8_ETMK0_256_MASK		(1)

/* ECMETMK0_9 */
#define		ECM_ECMETMK0_9_ETMK0_319		(BIT31)
	#define		ECM_ECMETMK0_9_ETMK0_319_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_319_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_318		(BIT30)
	#define		ECM_ECMETMK0_9_ETMK0_318_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_318_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_317		(BIT29)
	#define		ECM_ECMETMK0_9_ETMK0_317_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_317_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_316		(BIT28)
	#define		ECM_ECMETMK0_9_ETMK0_316_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_316_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_315		(BIT27)
	#define		ECM_ECMETMK0_9_ETMK0_315_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_315_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_314		(BIT26)
	#define		ECM_ECMETMK0_9_ETMK0_314_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_314_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_313		(BIT25)
	#define		ECM_ECMETMK0_9_ETMK0_313_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_313_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_312		(BIT24)
	#define		ECM_ECMETMK0_9_ETMK0_312_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_312_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_311		(BIT23)
	#define		ECM_ECMETMK0_9_ETMK0_311_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_311_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_310		(BIT22)
	#define		ECM_ECMETMK0_9_ETMK0_310_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_310_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_309		(BIT21)
	#define		ECM_ECMETMK0_9_ETMK0_309_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_309_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_308		(BIT20)
	#define		ECM_ECMETMK0_9_ETMK0_308_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_308_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_307		(BIT19)
	#define		ECM_ECMETMK0_9_ETMK0_307_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_307_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_306		(BIT18)
	#define		ECM_ECMETMK0_9_ETMK0_306_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_306_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_305		(BIT17)
	#define		ECM_ECMETMK0_9_ETMK0_305_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_305_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_304		(BIT16)
	#define		ECM_ECMETMK0_9_ETMK0_304_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_304_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_303		(BIT15)
	#define		ECM_ECMETMK0_9_ETMK0_303_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_303_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_302		(BIT14)
	#define		ECM_ECMETMK0_9_ETMK0_302_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_302_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_301		(BIT13)
	#define		ECM_ECMETMK0_9_ETMK0_301_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_301_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_300		(BIT12)
	#define		ECM_ECMETMK0_9_ETMK0_300_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_300_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_299		(BIT11)
	#define		ECM_ECMETMK0_9_ETMK0_299_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_299_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_298		(BIT10)
	#define		ECM_ECMETMK0_9_ETMK0_298_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_298_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_297		(BIT9)
	#define		ECM_ECMETMK0_9_ETMK0_297_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_297_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_296		(BIT8)
	#define		ECM_ECMETMK0_9_ETMK0_296_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_296_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_295		(BIT7)
	#define		ECM_ECMETMK0_9_ETMK0_295_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_295_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_294		(BIT6)
	#define		ECM_ECMETMK0_9_ETMK0_294_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_294_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_293		(BIT5)
	#define		ECM_ECMETMK0_9_ETMK0_293_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_293_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_292		(BIT4)
	#define		ECM_ECMETMK0_9_ETMK0_292_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_292_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_291		(BIT3)
	#define		ECM_ECMETMK0_9_ETMK0_291_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_291_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_290		(BIT2)
	#define		ECM_ECMETMK0_9_ETMK0_290_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_290_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_289		(BIT1)
	#define		ECM_ECMETMK0_9_ETMK0_289_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_289_MASK		(1)
#define		ECM_ECMETMK0_9_ETMK0_288		(BIT0)
	#define		ECM_ECMETMK0_9_ETMK0_288_NOMASK	(0)
	#define		ECM_ECMETMK0_9_ETMK0_288_MASK		(1)

/* ECMETMK0_10 */
#define		ECM_ECMETMK0_10_ETMK0_351		(BIT31)
	#define		ECM_ECMETMK0_10_ETMK0_351_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_351_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_350		(BIT30)
	#define		ECM_ECMETMK0_10_ETMK0_350_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_350_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_349		(BIT29)
	#define		ECM_ECMETMK0_10_ETMK0_349_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_349_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_348		(BIT28)
	#define		ECM_ECMETMK0_10_ETMK0_348_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_348_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_347		(BIT27)
	#define		ECM_ECMETMK0_10_ETMK0_347_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_347_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_346		(BIT26)
	#define		ECM_ECMETMK0_10_ETMK0_346_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_346_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_345		(BIT25)
	#define		ECM_ECMETMK0_10_ETMK0_345_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_345_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_344		(BIT24)
	#define		ECM_ECMETMK0_10_ETMK0_344_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_344_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_343		(BIT23)
	#define		ECM_ECMETMK0_10_ETMK0_343_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_343_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_342		(BIT22)
	#define		ECM_ECMETMK0_10_ETMK0_342_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_342_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_341		(BIT21)
	#define		ECM_ECMETMK0_10_ETMK0_341_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_341_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_340		(BIT20)
	#define		ECM_ECMETMK0_10_ETMK0_340_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_340_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_339		(BIT19)
	#define		ECM_ECMETMK0_10_ETMK0_339_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_339_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_338		(BIT18)
	#define		ECM_ECMETMK0_10_ETMK0_338_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_338_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_337		(BIT17)
	#define		ECM_ECMETMK0_10_ETMK0_337_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_337_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_336		(BIT16)
	#define		ECM_ECMETMK0_10_ETMK0_336_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_336_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_335		(BIT15)
	#define		ECM_ECMETMK0_10_ETMK0_335_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_335_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_334		(BIT14)
	#define		ECM_ECMETMK0_10_ETMK0_334_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_334_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_333		(BIT13)
	#define		ECM_ECMETMK0_10_ETMK0_333_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_333_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_332		(BIT12)
	#define		ECM_ECMETMK0_10_ETMK0_332_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_332_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_331		(BIT11)
	#define		ECM_ECMETMK0_10_ETMK0_331_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_331_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_330		(BIT10)
	#define		ECM_ECMETMK0_10_ETMK0_330_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_330_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_329		(BIT9)
	#define		ECM_ECMETMK0_10_ETMK0_329_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_329_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_328		(BIT8)
	#define		ECM_ECMETMK0_10_ETMK0_328_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_328_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_327		(BIT7)
	#define		ECM_ECMETMK0_10_ETMK0_327_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_327_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_326		(BIT6)
	#define		ECM_ECMETMK0_10_ETMK0_326_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_326_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_325		(BIT5)
	#define		ECM_ECMETMK0_10_ETMK0_325_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_325_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_324		(BIT4)
	#define		ECM_ECMETMK0_10_ETMK0_324_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_324_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_323		(BIT3)
	#define		ECM_ECMETMK0_10_ETMK0_323_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_323_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_322		(BIT2)
	#define		ECM_ECMETMK0_10_ETMK0_322_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_322_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_321		(BIT1)
	#define		ECM_ECMETMK0_10_ETMK0_321_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_321_MASK		(1)
#define		ECM_ECMETMK0_10_ETMK0_320		(BIT0)
	#define		ECM_ECMETMK0_10_ETMK0_320_NOMASK	(0)
	#define		ECM_ECMETMK0_10_ETMK0_320_MASK		(1)

/* ECMETMK1_0 */
#define		ECM_ECMETMK1_0_ETMK1_031		(BIT31)
	#define		ECM_ECMETMK1_0_ETMK1_031_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_031_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_030		(BIT30)
	#define		ECM_ECMETMK1_0_ETMK1_030_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_030_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_029		(BIT29)
	#define		ECM_ECMETMK1_0_ETMK1_029_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_029_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_028		(BIT28)
	#define		ECM_ECMETMK1_0_ETMK1_028_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_028_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_027		(BIT27)
	#define		ECM_ECMETMK1_0_ETMK1_027_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_027_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_026		(BIT26)
	#define		ECM_ECMETMK1_0_ETMK1_026_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_026_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_025		(BIT25)
	#define		ECM_ECMETMK1_0_ETMK1_025_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_025_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_024		(BIT24)
	#define		ECM_ECMETMK1_0_ETMK1_024_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_024_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_023		(BIT23)
	#define		ECM_ECMETMK1_0_ETMK1_023_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_023_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_022		(BIT22)
	#define		ECM_ECMETMK1_0_ETMK1_022_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_022_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_021		(BIT21)
	#define		ECM_ECMETMK1_0_ETMK1_021_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_021_MASK		(1)
#define		ECM_ECMETMK1_0_ETMK1_020		(BIT20)
	#define		ECM_ECMETMK1_0_ETMK1_020_NOMASK	(0)
	#define		ECM_ECMETMK1_0_ETMK1_020_MASK		(1)

/* ECMETMK1_1 */
#define		ECM_ECMETMK1_1_ETMK1_063		(BIT31)
	#define		ECM_ECMETMK1_1_ETMK1_063_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_063_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_062		(BIT30)
	#define		ECM_ECMETMK1_1_ETMK1_062_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_062_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_061		(BIT29)
	#define		ECM_ECMETMK1_1_ETMK1_061_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_061_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_060		(BIT28)
	#define		ECM_ECMETMK1_1_ETMK1_060_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_060_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_059		(BIT27)
	#define		ECM_ECMETMK1_1_ETMK1_059_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_059_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_058		(BIT26)
	#define		ECM_ECMETMK1_1_ETMK1_058_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_058_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_057		(BIT25)
	#define		ECM_ECMETMK1_1_ETMK1_057_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_057_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_056		(BIT24)
	#define		ECM_ECMETMK1_1_ETMK1_056_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_056_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_055		(BIT23)
	#define		ECM_ECMETMK1_1_ETMK1_055_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_055_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_054		(BIT22)
	#define		ECM_ECMETMK1_1_ETMK1_054_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_054_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_053		(BIT21)
	#define		ECM_ECMETMK1_1_ETMK1_053_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_053_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_052		(BIT20)
	#define		ECM_ECMETMK1_1_ETMK1_052_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_052_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_051		(BIT19)
	#define		ECM_ECMETMK1_1_ETMK1_051_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_051_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_050		(BIT18)
	#define		ECM_ECMETMK1_1_ETMK1_050_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_050_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_049		(BIT17)
	#define		ECM_ECMETMK1_1_ETMK1_049_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_049_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_048		(BIT16)
	#define		ECM_ECMETMK1_1_ETMK1_048_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_048_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_047		(BIT15)
	#define		ECM_ECMETMK1_1_ETMK1_047_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_047_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_046		(BIT14)
	#define		ECM_ECMETMK1_1_ETMK1_046_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_046_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_045		(BIT13)
	#define		ECM_ECMETMK1_1_ETMK1_045_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_045_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_044		(BIT12)
	#define		ECM_ECMETMK1_1_ETMK1_044_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_044_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_043		(BIT11)
	#define		ECM_ECMETMK1_1_ETMK1_043_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_043_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_042		(BIT10)
	#define		ECM_ECMETMK1_1_ETMK1_042_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_042_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_041		(BIT9)
	#define		ECM_ECMETMK1_1_ETMK1_041_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_041_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_040		(BIT8)
	#define		ECM_ECMETMK1_1_ETMK1_040_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_040_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_039		(BIT7)
	#define		ECM_ECMETMK1_1_ETMK1_039_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_039_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_038		(BIT6)
	#define		ECM_ECMETMK1_1_ETMK1_038_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_038_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_037		(BIT5)
	#define		ECM_ECMETMK1_1_ETMK1_037_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_037_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_036		(BIT4)
	#define		ECM_ECMETMK1_1_ETMK1_036_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_036_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_035		(BIT3)
	#define		ECM_ECMETMK1_1_ETMK1_035_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_035_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_034		(BIT2)
	#define		ECM_ECMETMK1_1_ETMK1_034_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_034_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_033		(BIT1)
	#define		ECM_ECMETMK1_1_ETMK1_033_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_033_MASK		(1)
#define		ECM_ECMETMK1_1_ETMK1_032		(BIT0)
	#define		ECM_ECMETMK1_1_ETMK1_032_NOMASK	(0)
	#define		ECM_ECMETMK1_1_ETMK1_032_MASK		(1)

/* ECMETMK1_2 */
#define		ECM_ECMETMK1_2_ETMK1_095		(BIT31)
	#define		ECM_ECMETMK1_2_ETMK1_095_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_095_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_094		(BIT30)
	#define		ECM_ECMETMK1_2_ETMK1_094_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_094_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_093		(BIT29)
	#define		ECM_ECMETMK1_2_ETMK1_093_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_093_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_092		(BIT28)
	#define		ECM_ECMETMK1_2_ETMK1_092_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_092_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_091		(BIT27)
	#define		ECM_ECMETMK1_2_ETMK1_091_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_091_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_090		(BIT26)
	#define		ECM_ECMETMK1_2_ETMK1_090_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_090_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_089		(BIT25)
	#define		ECM_ECMETMK1_2_ETMK1_089_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_089_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_088		(BIT24)
	#define		ECM_ECMETMK1_2_ETMK1_088_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_088_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_087		(BIT23)
	#define		ECM_ECMETMK1_2_ETMK1_087_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_087_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_086		(BIT22)
	#define		ECM_ECMETMK1_2_ETMK1_086_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_086_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_085		(BIT21)
	#define		ECM_ECMETMK1_2_ETMK1_085_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_085_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_084		(BIT20)
	#define		ECM_ECMETMK1_2_ETMK1_084_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_084_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_083		(BIT19)
	#define		ECM_ECMETMK1_2_ETMK1_083_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_083_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_082		(BIT18)
	#define		ECM_ECMETMK1_2_ETMK1_082_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_082_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_081		(BIT17)
	#define		ECM_ECMETMK1_2_ETMK1_081_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_081_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_080		(BIT16)
	#define		ECM_ECMETMK1_2_ETMK1_080_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_080_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_079		(BIT15)
	#define		ECM_ECMETMK1_2_ETMK1_079_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_079_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_078		(BIT14)
	#define		ECM_ECMETMK1_2_ETMK1_078_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_078_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_077		(BIT13)
	#define		ECM_ECMETMK1_2_ETMK1_077_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_077_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_076		(BIT12)
	#define		ECM_ECMETMK1_2_ETMK1_076_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_076_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_075		(BIT11)
	#define		ECM_ECMETMK1_2_ETMK1_075_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_075_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_074		(BIT10)
	#define		ECM_ECMETMK1_2_ETMK1_074_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_074_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_073		(BIT9)
	#define		ECM_ECMETMK1_2_ETMK1_073_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_073_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_072		(BIT8)
	#define		ECM_ECMETMK1_2_ETMK1_072_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_072_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_071		(BIT7)
	#define		ECM_ECMETMK1_2_ETMK1_071_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_071_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_070		(BIT6)
	#define		ECM_ECMETMK1_2_ETMK1_070_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_070_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_069		(BIT5)
	#define		ECM_ECMETMK1_2_ETMK1_069_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_069_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_068		(BIT4)
	#define		ECM_ECMETMK1_2_ETMK1_068_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_068_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_067		(BIT3)
	#define		ECM_ECMETMK1_2_ETMK1_067_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_067_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_066		(BIT2)
	#define		ECM_ECMETMK1_2_ETMK1_066_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_066_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_065		(BIT1)
	#define		ECM_ECMETMK1_2_ETMK1_065_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_065_MASK		(1)
#define		ECM_ECMETMK1_2_ETMK1_064		(BIT0)
	#define		ECM_ECMETMK1_2_ETMK1_064_NOMASK	(0)
	#define		ECM_ECMETMK1_2_ETMK1_064_MASK		(1)

/* ECMETMK1_3 */
#define		ECM_ECMETMK1_3_ETMK1_127		(BIT31)
	#define		ECM_ECMETMK1_3_ETMK1_127_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_127_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_126		(BIT30)
	#define		ECM_ECMETMK1_3_ETMK1_126_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_126_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_125		(BIT29)
	#define		ECM_ECMETMK1_3_ETMK1_125_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_125_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_124		(BIT28)
	#define		ECM_ECMETMK1_3_ETMK1_124_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_124_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_123		(BIT27)
	#define		ECM_ECMETMK1_3_ETMK1_123_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_123_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_122		(BIT26)
	#define		ECM_ECMETMK1_3_ETMK1_122_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_122_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_121		(BIT25)
	#define		ECM_ECMETMK1_3_ETMK1_121_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_121_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_120		(BIT24)
	#define		ECM_ECMETMK1_3_ETMK1_120_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_120_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_119		(BIT23)
	#define		ECM_ECMETMK1_3_ETMK1_119_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_119_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_118		(BIT22)
	#define		ECM_ECMETMK1_3_ETMK1_118_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_118_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_117		(BIT21)
	#define		ECM_ECMETMK1_3_ETMK1_117_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_117_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_116		(BIT20)
	#define		ECM_ECMETMK1_3_ETMK1_116_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_116_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_115		(BIT19)
	#define		ECM_ECMETMK1_3_ETMK1_115_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_115_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_114		(BIT18)
	#define		ECM_ECMETMK1_3_ETMK1_114_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_114_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_113		(BIT17)
	#define		ECM_ECMETMK1_3_ETMK1_113_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_113_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_112		(BIT16)
	#define		ECM_ECMETMK1_3_ETMK1_112_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_112_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_111		(BIT15)
	#define		ECM_ECMETMK1_3_ETMK1_111_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_111_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_110		(BIT14)
	#define		ECM_ECMETMK1_3_ETMK1_110_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_110_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_109		(BIT13)
	#define		ECM_ECMETMK1_3_ETMK1_109_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_109_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_108		(BIT12)
	#define		ECM_ECMETMK1_3_ETMK1_108_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_108_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_107		(BIT11)
	#define		ECM_ECMETMK1_3_ETMK1_107_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_107_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_106		(BIT10)
	#define		ECM_ECMETMK1_3_ETMK1_106_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_106_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_105		(BIT9)
	#define		ECM_ECMETMK1_3_ETMK1_105_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_105_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_104		(BIT8)
	#define		ECM_ECMETMK1_3_ETMK1_104_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_104_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_103		(BIT7)
	#define		ECM_ECMETMK1_3_ETMK1_103_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_103_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_102		(BIT6)
	#define		ECM_ECMETMK1_3_ETMK1_102_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_102_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_101		(BIT5)
	#define		ECM_ECMETMK1_3_ETMK1_101_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_101_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_100		(BIT4)
	#define		ECM_ECMETMK1_3_ETMK1_100_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_100_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_099		(BIT3)
	#define		ECM_ECMETMK1_3_ETMK1_099_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_099_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_098		(BIT2)
	#define		ECM_ECMETMK1_3_ETMK1_098_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_098_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_097		(BIT1)
	#define		ECM_ECMETMK1_3_ETMK1_097_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_097_MASK		(1)
#define		ECM_ECMETMK1_3_ETMK1_096		(BIT0)
	#define		ECM_ECMETMK1_3_ETMK1_096_NOMASK	(0)
	#define		ECM_ECMETMK1_3_ETMK1_096_MASK		(1)

/* ECMETMK1_4 */
#define		ECM_ECMETMK1_4_ETMK1_159		(BIT31)
	#define		ECM_ECMETMK1_4_ETMK1_159_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_159_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_158		(BIT30)
	#define		ECM_ECMETMK1_4_ETMK1_158_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_158_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_157		(BIT29)
	#define		ECM_ECMETMK1_4_ETMK1_157_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_157_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_156		(BIT28)
	#define		ECM_ECMETMK1_4_ETMK1_156_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_156_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_155		(BIT27)
	#define		ECM_ECMETMK1_4_ETMK1_155_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_155_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_154		(BIT26)
	#define		ECM_ECMETMK1_4_ETMK1_154_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_154_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_153		(BIT25)
	#define		ECM_ECMETMK1_4_ETMK1_153_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_153_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_152		(BIT24)
	#define		ECM_ECMETMK1_4_ETMK1_152_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_152_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_151		(BIT23)
	#define		ECM_ECMETMK1_4_ETMK1_151_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_151_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_150		(BIT22)
	#define		ECM_ECMETMK1_4_ETMK1_150_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_150_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_149		(BIT21)
	#define		ECM_ECMETMK1_4_ETMK1_149_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_149_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_148		(BIT20)
	#define		ECM_ECMETMK1_4_ETMK1_148_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_148_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_147		(BIT19)
	#define		ECM_ECMETMK1_4_ETMK1_147_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_147_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_146		(BIT18)
	#define		ECM_ECMETMK1_4_ETMK1_146_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_146_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_145		(BIT17)
	#define		ECM_ECMETMK1_4_ETMK1_145_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_145_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_144		(BIT16)
	#define		ECM_ECMETMK1_4_ETMK1_144_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_144_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_143		(BIT15)
	#define		ECM_ECMETMK1_4_ETMK1_143_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_143_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_142		(BIT14)
	#define		ECM_ECMETMK1_4_ETMK1_142_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_142_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_141		(BIT13)
	#define		ECM_ECMETMK1_4_ETMK1_141_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_141_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_140		(BIT12)
	#define		ECM_ECMETMK1_4_ETMK1_140_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_140_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_139		(BIT11)
	#define		ECM_ECMETMK1_4_ETMK1_139_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_139_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_138		(BIT10)
	#define		ECM_ECMETMK1_4_ETMK1_138_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_138_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_137		(BIT9)
	#define		ECM_ECMETMK1_4_ETMK1_137_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_137_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_136		(BIT8)
	#define		ECM_ECMETMK1_4_ETMK1_136_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_136_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_135		(BIT7)
	#define		ECM_ECMETMK1_4_ETMK1_135_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_135_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_134		(BIT6)
	#define		ECM_ECMETMK1_4_ETMK1_134_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_134_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_133		(BIT5)
	#define		ECM_ECMETMK1_4_ETMK1_133_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_133_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_132		(BIT4)
	#define		ECM_ECMETMK1_4_ETMK1_132_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_132_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_131		(BIT3)
	#define		ECM_ECMETMK1_4_ETMK1_131_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_131_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_130		(BIT2)
	#define		ECM_ECMETMK1_4_ETMK1_130_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_130_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_129		(BIT1)
	#define		ECM_ECMETMK1_4_ETMK1_129_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_129_MASK		(1)
#define		ECM_ECMETMK1_4_ETMK1_128		(BIT0)
	#define		ECM_ECMETMK1_4_ETMK1_128_NOMASK	(0)
	#define		ECM_ECMETMK1_4_ETMK1_128_MASK		(1)

/* ECMETMK1_5 */
#define		ECM_ECMETMK1_5_ETMK1_191		(BIT31)
	#define		ECM_ECMETMK1_5_ETMK1_191_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_191_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_190		(BIT30)
	#define		ECM_ECMETMK1_5_ETMK1_190_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_190_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_189		(BIT29)
	#define		ECM_ECMETMK1_5_ETMK1_189_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_189_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_188		(BIT28)
	#define		ECM_ECMETMK1_5_ETMK1_188_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_188_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_187		(BIT27)
	#define		ECM_ECMETMK1_5_ETMK1_187_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_187_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_186		(BIT26)
	#define		ECM_ECMETMK1_5_ETMK1_186_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_186_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_185		(BIT25)
	#define		ECM_ECMETMK1_5_ETMK1_185_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_185_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_184		(BIT24)
	#define		ECM_ECMETMK1_5_ETMK1_184_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_184_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_183		(BIT23)
	#define		ECM_ECMETMK1_5_ETMK1_183_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_183_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_182		(BIT22)
	#define		ECM_ECMETMK1_5_ETMK1_182_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_182_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_181		(BIT21)
	#define		ECM_ECMETMK1_5_ETMK1_181_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_181_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_180		(BIT20)
	#define		ECM_ECMETMK1_5_ETMK1_180_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_180_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_179		(BIT19)
	#define		ECM_ECMETMK1_5_ETMK1_179_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_179_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_178		(BIT18)
	#define		ECM_ECMETMK1_5_ETMK1_178_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_178_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_177		(BIT17)
	#define		ECM_ECMETMK1_5_ETMK1_177_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_177_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_176		(BIT16)
	#define		ECM_ECMETMK1_5_ETMK1_176_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_176_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_175		(BIT15)
	#define		ECM_ECMETMK1_5_ETMK1_175_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_175_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_174		(BIT14)
	#define		ECM_ECMETMK1_5_ETMK1_174_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_174_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_173		(BIT13)
	#define		ECM_ECMETMK1_5_ETMK1_173_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_173_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_172		(BIT12)
	#define		ECM_ECMETMK1_5_ETMK1_172_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_172_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_171		(BIT11)
	#define		ECM_ECMETMK1_5_ETMK1_171_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_171_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_170		(BIT10)
	#define		ECM_ECMETMK1_5_ETMK1_170_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_170_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_169		(BIT9)
	#define		ECM_ECMETMK1_5_ETMK1_169_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_169_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_168		(BIT8)
	#define		ECM_ECMETMK1_5_ETMK1_168_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_168_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_167		(BIT7)
	#define		ECM_ECMETMK1_5_ETMK1_167_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_167_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_166		(BIT6)
	#define		ECM_ECMETMK1_5_ETMK1_166_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_166_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_165		(BIT5)
	#define		ECM_ECMETMK1_5_ETMK1_165_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_165_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_164		(BIT4)
	#define		ECM_ECMETMK1_5_ETMK1_164_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_164_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_163		(BIT3)
	#define		ECM_ECMETMK1_5_ETMK1_163_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_163_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_162		(BIT2)
	#define		ECM_ECMETMK1_5_ETMK1_162_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_162_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_161		(BIT1)
	#define		ECM_ECMETMK1_5_ETMK1_161_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_161_MASK		(1)
#define		ECM_ECMETMK1_5_ETMK1_160		(BIT0)
	#define		ECM_ECMETMK1_5_ETMK1_160_NOMASK	(0)
	#define		ECM_ECMETMK1_5_ETMK1_160_MASK		(1)

/* ECMETMK1_6 */
#define		ECM_ECMETMK1_6_ETMK1_223		(BIT31)
	#define		ECM_ECMETMK1_6_ETMK1_223_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_223_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_222		(BIT30)
	#define		ECM_ECMETMK1_6_ETMK1_222_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_222_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_221		(BIT29)
	#define		ECM_ECMETMK1_6_ETMK1_221_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_221_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_220		(BIT28)
	#define		ECM_ECMETMK1_6_ETMK1_220_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_220_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_219		(BIT27)
	#define		ECM_ECMETMK1_6_ETMK1_219_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_219_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_218		(BIT26)
	#define		ECM_ECMETMK1_6_ETMK1_218_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_218_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_217		(BIT25)
	#define		ECM_ECMETMK1_6_ETMK1_217_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_217_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_216		(BIT24)
	#define		ECM_ECMETMK1_6_ETMK1_216_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_216_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_215		(BIT23)
	#define		ECM_ECMETMK1_6_ETMK1_215_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_215_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_214		(BIT22)
	#define		ECM_ECMETMK1_6_ETMK1_214_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_214_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_213		(BIT21)
	#define		ECM_ECMETMK1_6_ETMK1_213_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_213_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_212		(BIT20)
	#define		ECM_ECMETMK1_6_ETMK1_212_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_212_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_211		(BIT19)
	#define		ECM_ECMETMK1_6_ETMK1_211_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_211_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_210		(BIT18)
	#define		ECM_ECMETMK1_6_ETMK1_210_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_210_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_209		(BIT17)
	#define		ECM_ECMETMK1_6_ETMK1_209_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_209_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_208		(BIT16)
	#define		ECM_ECMETMK1_6_ETMK1_208_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_208_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_207		(BIT15)
	#define		ECM_ECMETMK1_6_ETMK1_207_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_207_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_206		(BIT14)
	#define		ECM_ECMETMK1_6_ETMK1_206_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_206_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_205		(BIT13)
	#define		ECM_ECMETMK1_6_ETMK1_205_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_205_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_204		(BIT12)
	#define		ECM_ECMETMK1_6_ETMK1_204_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_204_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_203		(BIT11)
	#define		ECM_ECMETMK1_6_ETMK1_203_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_203_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_202		(BIT10)
	#define		ECM_ECMETMK1_6_ETMK1_202_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_202_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_201		(BIT9)
	#define		ECM_ECMETMK1_6_ETMK1_201_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_201_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_200		(BIT8)
	#define		ECM_ECMETMK1_6_ETMK1_200_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_200_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_199		(BIT7)
	#define		ECM_ECMETMK1_6_ETMK1_199_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_199_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_198		(BIT6)
	#define		ECM_ECMETMK1_6_ETMK1_198_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_198_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_197		(BIT5)
	#define		ECM_ECMETMK1_6_ETMK1_197_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_197_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_196		(BIT4)
	#define		ECM_ECMETMK1_6_ETMK1_196_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_196_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_195		(BIT3)
	#define		ECM_ECMETMK1_6_ETMK1_195_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_195_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_194		(BIT2)
	#define		ECM_ECMETMK1_6_ETMK1_194_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_194_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_193		(BIT1)
	#define		ECM_ECMETMK1_6_ETMK1_193_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_193_MASK		(1)
#define		ECM_ECMETMK1_6_ETMK1_192		(BIT0)
	#define		ECM_ECMETMK1_6_ETMK1_192_NOMASK	(0)
	#define		ECM_ECMETMK1_6_ETMK1_192_MASK		(1)

/* ECMETMK1_7 */
#define		ECM_ECMETMK1_7_ETMK1_255		(BIT31)
	#define		ECM_ECMETMK1_7_ETMK1_255_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_255_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_254		(BIT30)
	#define		ECM_ECMETMK1_7_ETMK1_254_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_254_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_253		(BIT29)
	#define		ECM_ECMETMK1_7_ETMK1_253_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_253_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_252		(BIT28)
	#define		ECM_ECMETMK1_7_ETMK1_252_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_252_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_251		(BIT27)
	#define		ECM_ECMETMK1_7_ETMK1_251_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_251_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_250		(BIT26)
	#define		ECM_ECMETMK1_7_ETMK1_250_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_250_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_249		(BIT25)
	#define		ECM_ECMETMK1_7_ETMK1_249_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_249_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_248		(BIT24)
	#define		ECM_ECMETMK1_7_ETMK1_248_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_248_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_247		(BIT23)
	#define		ECM_ECMETMK1_7_ETMK1_247_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_247_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_246		(BIT22)
	#define		ECM_ECMETMK1_7_ETMK1_246_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_246_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_245		(BIT21)
	#define		ECM_ECMETMK1_7_ETMK1_245_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_245_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_244		(BIT20)
	#define		ECM_ECMETMK1_7_ETMK1_244_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_244_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_243		(BIT19)
	#define		ECM_ECMETMK1_7_ETMK1_243_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_243_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_242		(BIT18)
	#define		ECM_ECMETMK1_7_ETMK1_242_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_242_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_241		(BIT17)
	#define		ECM_ECMETMK1_7_ETMK1_241_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_241_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_240		(BIT16)
	#define		ECM_ECMETMK1_7_ETMK1_240_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_240_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_239		(BIT15)
	#define		ECM_ECMETMK1_7_ETMK1_239_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_239_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_238		(BIT14)
	#define		ECM_ECMETMK1_7_ETMK1_238_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_238_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_237		(BIT13)
	#define		ECM_ECMETMK1_7_ETMK1_237_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_237_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_236		(BIT12)
	#define		ECM_ECMETMK1_7_ETMK1_236_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_236_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_235		(BIT11)
	#define		ECM_ECMETMK1_7_ETMK1_235_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_235_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_234		(BIT10)
	#define		ECM_ECMETMK1_7_ETMK1_234_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_234_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_233		(BIT9)
	#define		ECM_ECMETMK1_7_ETMK1_233_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_233_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_232		(BIT8)
	#define		ECM_ECMETMK1_7_ETMK1_232_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_232_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_231		(BIT7)
	#define		ECM_ECMETMK1_7_ETMK1_231_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_231_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_230		(BIT6)
	#define		ECM_ECMETMK1_7_ETMK1_230_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_230_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_229		(BIT5)
	#define		ECM_ECMETMK1_7_ETMK1_229_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_229_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_228		(BIT4)
	#define		ECM_ECMETMK1_7_ETMK1_228_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_228_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_227		(BIT3)
	#define		ECM_ECMETMK1_7_ETMK1_227_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_227_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_226		(BIT2)
	#define		ECM_ECMETMK1_7_ETMK1_226_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_226_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_225		(BIT1)
	#define		ECM_ECMETMK1_7_ETMK1_225_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_225_MASK		(1)
#define		ECM_ECMETMK1_7_ETMK1_224		(BIT0)
	#define		ECM_ECMETMK1_7_ETMK1_224_NOMASK	(0)
	#define		ECM_ECMETMK1_7_ETMK1_224_MASK		(1)

/* ECMETMK1_8 */
#define		ECM_ECMETMK1_8_ETMK1_287		(BIT31)
	#define		ECM_ECMETMK1_8_ETMK1_287_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_287_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_286		(BIT30)
	#define		ECM_ECMETMK1_8_ETMK1_286_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_286_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_285		(BIT29)
	#define		ECM_ECMETMK1_8_ETMK1_285_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_285_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_284		(BIT28)
	#define		ECM_ECMETMK1_8_ETMK1_284_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_284_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_283		(BIT27)
	#define		ECM_ECMETMK1_8_ETMK1_283_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_283_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_282		(BIT26)
	#define		ECM_ECMETMK1_8_ETMK1_282_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_282_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_281		(BIT25)
	#define		ECM_ECMETMK1_8_ETMK1_281_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_281_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_280		(BIT24)
	#define		ECM_ECMETMK1_8_ETMK1_280_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_280_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_279		(BIT23)
	#define		ECM_ECMETMK1_8_ETMK1_279_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_279_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_278		(BIT22)
	#define		ECM_ECMETMK1_8_ETMK1_278_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_278_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_277		(BIT21)
	#define		ECM_ECMETMK1_8_ETMK1_277_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_277_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_276		(BIT20)
	#define		ECM_ECMETMK1_8_ETMK1_276_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_276_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_275		(BIT19)
	#define		ECM_ECMETMK1_8_ETMK1_275_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_275_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_274		(BIT18)
	#define		ECM_ECMETMK1_8_ETMK1_274_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_274_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_273		(BIT17)
	#define		ECM_ECMETMK1_8_ETMK1_273_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_273_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_272		(BIT16)
	#define		ECM_ECMETMK1_8_ETMK1_272_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_272_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_271		(BIT15)
	#define		ECM_ECMETMK1_8_ETMK1_271_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_271_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_270		(BIT14)
	#define		ECM_ECMETMK1_8_ETMK1_270_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_270_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_269		(BIT13)
	#define		ECM_ECMETMK1_8_ETMK1_269_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_269_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_268		(BIT12)
	#define		ECM_ECMETMK1_8_ETMK1_268_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_268_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_267		(BIT11)
	#define		ECM_ECMETMK1_8_ETMK1_267_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_267_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_266		(BIT10)
	#define		ECM_ECMETMK1_8_ETMK1_266_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_266_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_265		(BIT9)
	#define		ECM_ECMETMK1_8_ETMK1_265_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_265_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_264		(BIT8)
	#define		ECM_ECMETMK1_8_ETMK1_264_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_264_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_263		(BIT7)
	#define		ECM_ECMETMK1_8_ETMK1_263_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_263_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_262		(BIT6)
	#define		ECM_ECMETMK1_8_ETMK1_262_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_262_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_261		(BIT5)
	#define		ECM_ECMETMK1_8_ETMK1_261_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_261_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_260		(BIT4)
	#define		ECM_ECMETMK1_8_ETMK1_260_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_260_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_259		(BIT3)
	#define		ECM_ECMETMK1_8_ETMK1_259_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_259_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_258		(BIT2)
	#define		ECM_ECMETMK1_8_ETMK1_258_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_258_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_257		(BIT1)
	#define		ECM_ECMETMK1_8_ETMK1_257_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_257_MASK		(1)
#define		ECM_ECMETMK1_8_ETMK1_256		(BIT0)
	#define		ECM_ECMETMK1_8_ETMK1_256_NOMASK	(0)
	#define		ECM_ECMETMK1_8_ETMK1_256_MASK		(1)

/* ECMETMK1_9 */
#define		ECM_ECMETMK1_9_ETMK1_319		(BIT31)
	#define		ECM_ECMETMK1_9_ETMK1_319_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_319_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_318		(BIT30)
	#define		ECM_ECMETMK1_9_ETMK1_318_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_318_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_317		(BIT29)
	#define		ECM_ECMETMK1_9_ETMK1_317_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_317_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_316		(BIT28)
	#define		ECM_ECMETMK1_9_ETMK1_316_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_316_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_315		(BIT27)
	#define		ECM_ECMETMK1_9_ETMK1_315_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_315_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_314		(BIT26)
	#define		ECM_ECMETMK1_9_ETMK1_314_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_314_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_313		(BIT25)
	#define		ECM_ECMETMK1_9_ETMK1_313_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_313_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_312		(BIT24)
	#define		ECM_ECMETMK1_9_ETMK1_312_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_312_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_311		(BIT23)
	#define		ECM_ECMETMK1_9_ETMK1_311_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_311_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_310		(BIT22)
	#define		ECM_ECMETMK1_9_ETMK1_310_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_310_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_309		(BIT21)
	#define		ECM_ECMETMK1_9_ETMK1_309_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_309_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_308		(BIT20)
	#define		ECM_ECMETMK1_9_ETMK1_308_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_308_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_307		(BIT19)
	#define		ECM_ECMETMK1_9_ETMK1_307_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_307_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_306		(BIT18)
	#define		ECM_ECMETMK1_9_ETMK1_306_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_306_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_305		(BIT17)
	#define		ECM_ECMETMK1_9_ETMK1_305_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_305_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_304		(BIT16)
	#define		ECM_ECMETMK1_9_ETMK1_304_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_304_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_303		(BIT15)
	#define		ECM_ECMETMK1_9_ETMK1_303_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_303_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_302		(BIT14)
	#define		ECM_ECMETMK1_9_ETMK1_302_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_302_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_301		(BIT13)
	#define		ECM_ECMETMK1_9_ETMK1_301_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_301_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_300		(BIT12)
	#define		ECM_ECMETMK1_9_ETMK1_300_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_300_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_299		(BIT11)
	#define		ECM_ECMETMK1_9_ETMK1_299_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_299_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_298		(BIT10)
	#define		ECM_ECMETMK1_9_ETMK1_298_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_298_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_297		(BIT9)
	#define		ECM_ECMETMK1_9_ETMK1_297_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_297_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_296		(BIT8)
	#define		ECM_ECMETMK1_9_ETMK1_296_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_296_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_295		(BIT7)
	#define		ECM_ECMETMK1_9_ETMK1_295_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_295_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_294		(BIT6)
	#define		ECM_ECMETMK1_9_ETMK1_294_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_294_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_293		(BIT5)
	#define		ECM_ECMETMK1_9_ETMK1_293_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_293_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_292		(BIT4)
	#define		ECM_ECMETMK1_9_ETMK1_292_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_292_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_291		(BIT3)
	#define		ECM_ECMETMK1_9_ETMK1_291_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_291_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_290		(BIT2)
	#define		ECM_ECMETMK1_9_ETMK1_290_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_290_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_289		(BIT1)
	#define		ECM_ECMETMK1_9_ETMK1_289_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_289_MASK		(1)
#define		ECM_ECMETMK1_9_ETMK1_288		(BIT0)
	#define		ECM_ECMETMK1_9_ETMK1_288_NOMASK	(0)
	#define		ECM_ECMETMK1_9_ETMK1_288_MASK		(1)

/* ECMETMK1_10 */
#define		ECM_ECMETMK1_10_ETMK1_351		(BIT31)
	#define		ECM_ECMETMK1_10_ETMK1_351_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_351_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_350		(BIT30)
	#define		ECM_ECMETMK1_10_ETMK1_350_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_350_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_349		(BIT29)
	#define		ECM_ECMETMK1_10_ETMK1_349_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_349_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_348		(BIT28)
	#define		ECM_ECMETMK1_10_ETMK1_348_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_348_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_347		(BIT27)
	#define		ECM_ECMETMK1_10_ETMK1_347_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_347_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_346		(BIT26)
	#define		ECM_ECMETMK1_10_ETMK1_346_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_346_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_345		(BIT25)
	#define		ECM_ECMETMK1_10_ETMK1_345_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_345_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_344		(BIT24)
	#define		ECM_ECMETMK1_10_ETMK1_344_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_344_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_343		(BIT23)
	#define		ECM_ECMETMK1_10_ETMK1_343_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_343_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_342		(BIT22)
	#define		ECM_ECMETMK1_10_ETMK1_342_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_342_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_341		(BIT21)
	#define		ECM_ECMETMK1_10_ETMK1_341_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_341_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_340		(BIT20)
	#define		ECM_ECMETMK1_10_ETMK1_340_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_340_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_339		(BIT19)
	#define		ECM_ECMETMK1_10_ETMK1_339_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_339_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_338		(BIT18)
	#define		ECM_ECMETMK1_10_ETMK1_338_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_338_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_337		(BIT17)
	#define		ECM_ECMETMK1_10_ETMK1_337_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_337_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_336		(BIT16)
	#define		ECM_ECMETMK1_10_ETMK1_336_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_336_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_335		(BIT15)
	#define		ECM_ECMETMK1_10_ETMK1_335_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_335_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_334		(BIT14)
	#define		ECM_ECMETMK1_10_ETMK1_334_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_334_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_333		(BIT13)
	#define		ECM_ECMETMK1_10_ETMK1_333_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_333_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_332		(BIT12)
	#define		ECM_ECMETMK1_10_ETMK1_332_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_332_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_331		(BIT11)
	#define		ECM_ECMETMK1_10_ETMK1_331_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_331_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_330		(BIT10)
	#define		ECM_ECMETMK1_10_ETMK1_330_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_330_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_329		(BIT9)
	#define		ECM_ECMETMK1_10_ETMK1_329_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_329_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_328		(BIT8)
	#define		ECM_ECMETMK1_10_ETMK1_328_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_328_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_327		(BIT7)
	#define		ECM_ECMETMK1_10_ETMK1_327_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_327_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_326		(BIT6)
	#define		ECM_ECMETMK1_10_ETMK1_326_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_326_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_325		(BIT5)
	#define		ECM_ECMETMK1_10_ETMK1_325_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_325_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_324		(BIT4)
	#define		ECM_ECMETMK1_10_ETMK1_324_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_324_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_323		(BIT3)
	#define		ECM_ECMETMK1_10_ETMK1_323_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_323_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_322		(BIT2)
	#define		ECM_ECMETMK1_10_ETMK1_322_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_322_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_321		(BIT1)
	#define		ECM_ECMETMK1_10_ETMK1_321_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_321_MASK		(1)
#define		ECM_ECMETMK1_10_ETMK1_320		(BIT0)
	#define		ECM_ECMETMK1_10_ETMK1_320_NOMASK	(0)
	#define		ECM_ECMETMK1_10_ETMK1_320_MASK		(1)

/* ECMETMK2_0 */
#define		ECM_ECMETMK2_0_ETMK2_031		(BIT31)
	#define		ECM_ECMETMK2_0_ETMK2_031_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_031_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_030		(BIT30)
	#define		ECM_ECMETMK2_0_ETMK2_030_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_030_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_029		(BIT29)
	#define		ECM_ECMETMK2_0_ETMK2_029_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_029_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_028		(BIT28)
	#define		ECM_ECMETMK2_0_ETMK2_028_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_028_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_027		(BIT27)
	#define		ECM_ECMETMK2_0_ETMK2_027_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_027_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_026		(BIT26)
	#define		ECM_ECMETMK2_0_ETMK2_026_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_026_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_025		(BIT25)
	#define		ECM_ECMETMK2_0_ETMK2_025_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_025_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_024		(BIT24)
	#define		ECM_ECMETMK2_0_ETMK2_024_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_024_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_023		(BIT23)
	#define		ECM_ECMETMK2_0_ETMK2_023_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_023_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_022		(BIT22)
	#define		ECM_ECMETMK2_0_ETMK2_022_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_022_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_021		(BIT21)
	#define		ECM_ECMETMK2_0_ETMK2_021_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_021_MASK		(1)
#define		ECM_ECMETMK2_0_ETMK2_020		(BIT20)
	#define		ECM_ECMETMK2_0_ETMK2_020_NOMASK	(0)
	#define		ECM_ECMETMK2_0_ETMK2_020_MASK		(1)

/* ECMETMK2_1 */
#define		ECM_ECMETMK2_1_ETMK2_063		(BIT31)
	#define		ECM_ECMETMK2_1_ETMK2_063_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_063_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_062		(BIT30)
	#define		ECM_ECMETMK2_1_ETMK2_062_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_062_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_061		(BIT29)
	#define		ECM_ECMETMK2_1_ETMK2_061_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_061_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_060		(BIT28)
	#define		ECM_ECMETMK2_1_ETMK2_060_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_060_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_059		(BIT27)
	#define		ECM_ECMETMK2_1_ETMK2_059_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_059_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_058		(BIT26)
	#define		ECM_ECMETMK2_1_ETMK2_058_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_058_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_057		(BIT25)
	#define		ECM_ECMETMK2_1_ETMK2_057_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_057_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_056		(BIT24)
	#define		ECM_ECMETMK2_1_ETMK2_056_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_056_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_055		(BIT23)
	#define		ECM_ECMETMK2_1_ETMK2_055_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_055_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_054		(BIT22)
	#define		ECM_ECMETMK2_1_ETMK2_054_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_054_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_053		(BIT21)
	#define		ECM_ECMETMK2_1_ETMK2_053_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_053_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_052		(BIT20)
	#define		ECM_ECMETMK2_1_ETMK2_052_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_052_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_051		(BIT19)
	#define		ECM_ECMETMK2_1_ETMK2_051_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_051_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_050		(BIT18)
	#define		ECM_ECMETMK2_1_ETMK2_050_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_050_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_049		(BIT17)
	#define		ECM_ECMETMK2_1_ETMK2_049_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_049_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_048		(BIT16)
	#define		ECM_ECMETMK2_1_ETMK2_048_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_048_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_047		(BIT15)
	#define		ECM_ECMETMK2_1_ETMK2_047_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_047_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_046		(BIT14)
	#define		ECM_ECMETMK2_1_ETMK2_046_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_046_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_045		(BIT13)
	#define		ECM_ECMETMK2_1_ETMK2_045_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_045_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_044		(BIT12)
	#define		ECM_ECMETMK2_1_ETMK2_044_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_044_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_043		(BIT11)
	#define		ECM_ECMETMK2_1_ETMK2_043_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_043_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_042		(BIT10)
	#define		ECM_ECMETMK2_1_ETMK2_042_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_042_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_041		(BIT9)
	#define		ECM_ECMETMK2_1_ETMK2_041_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_041_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_040		(BIT8)
	#define		ECM_ECMETMK2_1_ETMK2_040_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_040_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_039		(BIT7)
	#define		ECM_ECMETMK2_1_ETMK2_039_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_039_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_038		(BIT6)
	#define		ECM_ECMETMK2_1_ETMK2_038_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_038_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_037		(BIT5)
	#define		ECM_ECMETMK2_1_ETMK2_037_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_037_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_036		(BIT4)
	#define		ECM_ECMETMK2_1_ETMK2_036_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_036_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_035		(BIT3)
	#define		ECM_ECMETMK2_1_ETMK2_035_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_035_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_034		(BIT2)
	#define		ECM_ECMETMK2_1_ETMK2_034_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_034_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_033		(BIT1)
	#define		ECM_ECMETMK2_1_ETMK2_033_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_033_MASK		(1)
#define		ECM_ECMETMK2_1_ETMK2_032		(BIT0)
	#define		ECM_ECMETMK2_1_ETMK2_032_NOMASK	(0)
	#define		ECM_ECMETMK2_1_ETMK2_032_MASK		(1)

/* ECMETMK2_2 */
#define		ECM_ECMETMK2_2_ETMK2_095		(BIT31)
	#define		ECM_ECMETMK2_2_ETMK2_095_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_095_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_094		(BIT30)
	#define		ECM_ECMETMK2_2_ETMK2_094_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_094_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_093		(BIT29)
	#define		ECM_ECMETMK2_2_ETMK2_093_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_093_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_092		(BIT28)
	#define		ECM_ECMETMK2_2_ETMK2_092_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_092_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_091		(BIT27)
	#define		ECM_ECMETMK2_2_ETMK2_091_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_091_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_090		(BIT26)
	#define		ECM_ECMETMK2_2_ETMK2_090_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_090_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_089		(BIT25)
	#define		ECM_ECMETMK2_2_ETMK2_089_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_089_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_088		(BIT24)
	#define		ECM_ECMETMK2_2_ETMK2_088_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_088_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_087		(BIT23)
	#define		ECM_ECMETMK2_2_ETMK2_087_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_087_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_086		(BIT22)
	#define		ECM_ECMETMK2_2_ETMK2_086_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_086_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_085		(BIT21)
	#define		ECM_ECMETMK2_2_ETMK2_085_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_085_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_084		(BIT20)
	#define		ECM_ECMETMK2_2_ETMK2_084_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_084_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_083		(BIT19)
	#define		ECM_ECMETMK2_2_ETMK2_083_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_083_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_082		(BIT18)
	#define		ECM_ECMETMK2_2_ETMK2_082_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_082_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_081		(BIT17)
	#define		ECM_ECMETMK2_2_ETMK2_081_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_081_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_080		(BIT16)
	#define		ECM_ECMETMK2_2_ETMK2_080_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_080_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_079		(BIT15)
	#define		ECM_ECMETMK2_2_ETMK2_079_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_079_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_078		(BIT14)
	#define		ECM_ECMETMK2_2_ETMK2_078_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_078_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_077		(BIT13)
	#define		ECM_ECMETMK2_2_ETMK2_077_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_077_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_076		(BIT12)
	#define		ECM_ECMETMK2_2_ETMK2_076_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_076_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_075		(BIT11)
	#define		ECM_ECMETMK2_2_ETMK2_075_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_075_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_074		(BIT10)
	#define		ECM_ECMETMK2_2_ETMK2_074_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_074_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_073		(BIT9)
	#define		ECM_ECMETMK2_2_ETMK2_073_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_073_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_072		(BIT8)
	#define		ECM_ECMETMK2_2_ETMK2_072_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_072_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_071		(BIT7)
	#define		ECM_ECMETMK2_2_ETMK2_071_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_071_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_070		(BIT6)
	#define		ECM_ECMETMK2_2_ETMK2_070_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_070_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_069		(BIT5)
	#define		ECM_ECMETMK2_2_ETMK2_069_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_069_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_068		(BIT4)
	#define		ECM_ECMETMK2_2_ETMK2_068_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_068_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_067		(BIT3)
	#define		ECM_ECMETMK2_2_ETMK2_067_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_067_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_066		(BIT2)
	#define		ECM_ECMETMK2_2_ETMK2_066_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_066_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_065		(BIT1)
	#define		ECM_ECMETMK2_2_ETMK2_065_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_065_MASK		(1)
#define		ECM_ECMETMK2_2_ETMK2_064		(BIT0)
	#define		ECM_ECMETMK2_2_ETMK2_064_NOMASK	(0)
	#define		ECM_ECMETMK2_2_ETMK2_064_MASK		(1)

/* ECMETMK2_3 */
#define		ECM_ECMETMK2_3_ETMK2_127		(BIT31)
	#define		ECM_ECMETMK2_3_ETMK2_127_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_127_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_126		(BIT30)
	#define		ECM_ECMETMK2_3_ETMK2_126_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_126_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_125		(BIT29)
	#define		ECM_ECMETMK2_3_ETMK2_125_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_125_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_124		(BIT28)
	#define		ECM_ECMETMK2_3_ETMK2_124_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_124_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_123		(BIT27)
	#define		ECM_ECMETMK2_3_ETMK2_123_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_123_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_122		(BIT26)
	#define		ECM_ECMETMK2_3_ETMK2_122_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_122_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_121		(BIT25)
	#define		ECM_ECMETMK2_3_ETMK2_121_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_121_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_120		(BIT24)
	#define		ECM_ECMETMK2_3_ETMK2_120_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_120_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_119		(BIT23)
	#define		ECM_ECMETMK2_3_ETMK2_119_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_119_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_118		(BIT22)
	#define		ECM_ECMETMK2_3_ETMK2_118_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_118_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_117		(BIT21)
	#define		ECM_ECMETMK2_3_ETMK2_117_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_117_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_116		(BIT20)
	#define		ECM_ECMETMK2_3_ETMK2_116_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_116_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_115		(BIT19)
	#define		ECM_ECMETMK2_3_ETMK2_115_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_115_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_114		(BIT18)
	#define		ECM_ECMETMK2_3_ETMK2_114_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_114_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_113		(BIT17)
	#define		ECM_ECMETMK2_3_ETMK2_113_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_113_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_112		(BIT16)
	#define		ECM_ECMETMK2_3_ETMK2_112_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_112_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_111		(BIT15)
	#define		ECM_ECMETMK2_3_ETMK2_111_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_111_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_110		(BIT14)
	#define		ECM_ECMETMK2_3_ETMK2_110_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_110_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_109		(BIT13)
	#define		ECM_ECMETMK2_3_ETMK2_109_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_109_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_108		(BIT12)
	#define		ECM_ECMETMK2_3_ETMK2_108_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_108_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_107		(BIT11)
	#define		ECM_ECMETMK2_3_ETMK2_107_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_107_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_106		(BIT10)
	#define		ECM_ECMETMK2_3_ETMK2_106_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_106_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_105		(BIT9)
	#define		ECM_ECMETMK2_3_ETMK2_105_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_105_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_104		(BIT8)
	#define		ECM_ECMETMK2_3_ETMK2_104_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_104_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_103		(BIT7)
	#define		ECM_ECMETMK2_3_ETMK2_103_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_103_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_102		(BIT6)
	#define		ECM_ECMETMK2_3_ETMK2_102_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_102_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_101		(BIT5)
	#define		ECM_ECMETMK2_3_ETMK2_101_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_101_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_100		(BIT4)
	#define		ECM_ECMETMK2_3_ETMK2_100_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_100_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_099		(BIT3)
	#define		ECM_ECMETMK2_3_ETMK2_099_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_099_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_098		(BIT2)
	#define		ECM_ECMETMK2_3_ETMK2_098_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_098_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_097		(BIT1)
	#define		ECM_ECMETMK2_3_ETMK2_097_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_097_MASK		(1)
#define		ECM_ECMETMK2_3_ETMK2_096		(BIT0)
	#define		ECM_ECMETMK2_3_ETMK2_096_NOMASK	(0)
	#define		ECM_ECMETMK2_3_ETMK2_096_MASK		(1)

/* ECMETMK2_4 */
#define		ECM_ECMETMK2_4_ETMK2_159		(BIT31)
	#define		ECM_ECMETMK2_4_ETMK2_159_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_159_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_158		(BIT30)
	#define		ECM_ECMETMK2_4_ETMK2_158_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_158_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_157		(BIT29)
	#define		ECM_ECMETMK2_4_ETMK2_157_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_157_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_156		(BIT28)
	#define		ECM_ECMETMK2_4_ETMK2_156_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_156_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_155		(BIT27)
	#define		ECM_ECMETMK2_4_ETMK2_155_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_155_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_154		(BIT26)
	#define		ECM_ECMETMK2_4_ETMK2_154_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_154_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_153		(BIT25)
	#define		ECM_ECMETMK2_4_ETMK2_153_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_153_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_152		(BIT24)
	#define		ECM_ECMETMK2_4_ETMK2_152_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_152_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_151		(BIT23)
	#define		ECM_ECMETMK2_4_ETMK2_151_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_151_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_150		(BIT22)
	#define		ECM_ECMETMK2_4_ETMK2_150_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_150_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_149		(BIT21)
	#define		ECM_ECMETMK2_4_ETMK2_149_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_149_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_148		(BIT20)
	#define		ECM_ECMETMK2_4_ETMK2_148_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_148_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_147		(BIT19)
	#define		ECM_ECMETMK2_4_ETMK2_147_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_147_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_146		(BIT18)
	#define		ECM_ECMETMK2_4_ETMK2_146_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_146_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_145		(BIT17)
	#define		ECM_ECMETMK2_4_ETMK2_145_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_145_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_144		(BIT16)
	#define		ECM_ECMETMK2_4_ETMK2_144_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_144_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_143		(BIT15)
	#define		ECM_ECMETMK2_4_ETMK2_143_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_143_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_142		(BIT14)
	#define		ECM_ECMETMK2_4_ETMK2_142_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_142_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_141		(BIT13)
	#define		ECM_ECMETMK2_4_ETMK2_141_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_141_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_140		(BIT12)
	#define		ECM_ECMETMK2_4_ETMK2_140_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_140_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_139		(BIT11)
	#define		ECM_ECMETMK2_4_ETMK2_139_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_139_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_138		(BIT10)
	#define		ECM_ECMETMK2_4_ETMK2_138_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_138_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_137		(BIT9)
	#define		ECM_ECMETMK2_4_ETMK2_137_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_137_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_136		(BIT8)
	#define		ECM_ECMETMK2_4_ETMK2_136_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_136_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_135		(BIT7)
	#define		ECM_ECMETMK2_4_ETMK2_135_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_135_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_134		(BIT6)
	#define		ECM_ECMETMK2_4_ETMK2_134_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_134_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_133		(BIT5)
	#define		ECM_ECMETMK2_4_ETMK2_133_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_133_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_132		(BIT4)
	#define		ECM_ECMETMK2_4_ETMK2_132_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_132_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_131		(BIT3)
	#define		ECM_ECMETMK2_4_ETMK2_131_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_131_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_130		(BIT2)
	#define		ECM_ECMETMK2_4_ETMK2_130_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_130_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_129		(BIT1)
	#define		ECM_ECMETMK2_4_ETMK2_129_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_129_MASK		(1)
#define		ECM_ECMETMK2_4_ETMK2_128		(BIT0)
	#define		ECM_ECMETMK2_4_ETMK2_128_NOMASK	(0)
	#define		ECM_ECMETMK2_4_ETMK2_128_MASK		(1)

/* ECMETMK2_5 */
#define		ECM_ECMETMK2_5_ETMK2_191		(BIT31)
	#define		ECM_ECMETMK2_5_ETMK2_191_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_191_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_190		(BIT30)
	#define		ECM_ECMETMK2_5_ETMK2_190_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_190_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_189		(BIT29)
	#define		ECM_ECMETMK2_5_ETMK2_189_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_189_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_188		(BIT28)
	#define		ECM_ECMETMK2_5_ETMK2_188_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_188_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_187		(BIT27)
	#define		ECM_ECMETMK2_5_ETMK2_187_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_187_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_186		(BIT26)
	#define		ECM_ECMETMK2_5_ETMK2_186_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_186_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_185		(BIT25)
	#define		ECM_ECMETMK2_5_ETMK2_185_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_185_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_184		(BIT24)
	#define		ECM_ECMETMK2_5_ETMK2_184_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_184_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_183		(BIT23)
	#define		ECM_ECMETMK2_5_ETMK2_183_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_183_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_182		(BIT22)
	#define		ECM_ECMETMK2_5_ETMK2_182_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_182_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_181		(BIT21)
	#define		ECM_ECMETMK2_5_ETMK2_181_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_181_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_180		(BIT20)
	#define		ECM_ECMETMK2_5_ETMK2_180_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_180_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_179		(BIT19)
	#define		ECM_ECMETMK2_5_ETMK2_179_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_179_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_178		(BIT18)
	#define		ECM_ECMETMK2_5_ETMK2_178_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_178_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_177		(BIT17)
	#define		ECM_ECMETMK2_5_ETMK2_177_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_177_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_176		(BIT16)
	#define		ECM_ECMETMK2_5_ETMK2_176_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_176_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_175		(BIT15)
	#define		ECM_ECMETMK2_5_ETMK2_175_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_175_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_174		(BIT14)
	#define		ECM_ECMETMK2_5_ETMK2_174_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_174_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_173		(BIT13)
	#define		ECM_ECMETMK2_5_ETMK2_173_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_173_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_172		(BIT12)
	#define		ECM_ECMETMK2_5_ETMK2_172_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_172_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_171		(BIT11)
	#define		ECM_ECMETMK2_5_ETMK2_171_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_171_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_170		(BIT10)
	#define		ECM_ECMETMK2_5_ETMK2_170_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_170_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_169		(BIT9)
	#define		ECM_ECMETMK2_5_ETMK2_169_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_169_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_168		(BIT8)
	#define		ECM_ECMETMK2_5_ETMK2_168_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_168_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_167		(BIT7)
	#define		ECM_ECMETMK2_5_ETMK2_167_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_167_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_166		(BIT6)
	#define		ECM_ECMETMK2_5_ETMK2_166_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_166_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_165		(BIT5)
	#define		ECM_ECMETMK2_5_ETMK2_165_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_165_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_164		(BIT4)
	#define		ECM_ECMETMK2_5_ETMK2_164_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_164_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_163		(BIT3)
	#define		ECM_ECMETMK2_5_ETMK2_163_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_163_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_162		(BIT2)
	#define		ECM_ECMETMK2_5_ETMK2_162_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_162_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_161		(BIT1)
	#define		ECM_ECMETMK2_5_ETMK2_161_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_161_MASK		(1)
#define		ECM_ECMETMK2_5_ETMK2_160		(BIT0)
	#define		ECM_ECMETMK2_5_ETMK2_160_NOMASK	(0)
	#define		ECM_ECMETMK2_5_ETMK2_160_MASK		(1)

/* ECMETMK2_6 */
#define		ECM_ECMETMK2_6_ETMK2_223		(BIT31)
	#define		ECM_ECMETMK2_6_ETMK2_223_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_223_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_222		(BIT30)
	#define		ECM_ECMETMK2_6_ETMK2_222_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_222_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_221		(BIT29)
	#define		ECM_ECMETMK2_6_ETMK2_221_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_221_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_220		(BIT28)
	#define		ECM_ECMETMK2_6_ETMK2_220_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_220_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_219		(BIT27)
	#define		ECM_ECMETMK2_6_ETMK2_219_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_219_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_218		(BIT26)
	#define		ECM_ECMETMK2_6_ETMK2_218_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_218_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_217		(BIT25)
	#define		ECM_ECMETMK2_6_ETMK2_217_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_217_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_216		(BIT24)
	#define		ECM_ECMETMK2_6_ETMK2_216_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_216_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_215		(BIT23)
	#define		ECM_ECMETMK2_6_ETMK2_215_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_215_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_214		(BIT22)
	#define		ECM_ECMETMK2_6_ETMK2_214_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_214_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_213		(BIT21)
	#define		ECM_ECMETMK2_6_ETMK2_213_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_213_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_212		(BIT20)
	#define		ECM_ECMETMK2_6_ETMK2_212_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_212_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_211		(BIT19)
	#define		ECM_ECMETMK2_6_ETMK2_211_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_211_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_210		(BIT18)
	#define		ECM_ECMETMK2_6_ETMK2_210_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_210_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_209		(BIT17)
	#define		ECM_ECMETMK2_6_ETMK2_209_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_209_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_208		(BIT16)
	#define		ECM_ECMETMK2_6_ETMK2_208_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_208_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_207		(BIT15)
	#define		ECM_ECMETMK2_6_ETMK2_207_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_207_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_206		(BIT14)
	#define		ECM_ECMETMK2_6_ETMK2_206_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_206_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_205		(BIT13)
	#define		ECM_ECMETMK2_6_ETMK2_205_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_205_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_204		(BIT12)
	#define		ECM_ECMETMK2_6_ETMK2_204_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_204_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_203		(BIT11)
	#define		ECM_ECMETMK2_6_ETMK2_203_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_203_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_202		(BIT10)
	#define		ECM_ECMETMK2_6_ETMK2_202_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_202_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_201		(BIT9)
	#define		ECM_ECMETMK2_6_ETMK2_201_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_201_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_200		(BIT8)
	#define		ECM_ECMETMK2_6_ETMK2_200_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_200_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_199		(BIT7)
	#define		ECM_ECMETMK2_6_ETMK2_199_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_199_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_198		(BIT6)
	#define		ECM_ECMETMK2_6_ETMK2_198_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_198_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_197		(BIT5)
	#define		ECM_ECMETMK2_6_ETMK2_197_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_197_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_196		(BIT4)
	#define		ECM_ECMETMK2_6_ETMK2_196_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_196_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_195		(BIT3)
	#define		ECM_ECMETMK2_6_ETMK2_195_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_195_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_194		(BIT2)
	#define		ECM_ECMETMK2_6_ETMK2_194_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_194_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_193		(BIT1)
	#define		ECM_ECMETMK2_6_ETMK2_193_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_193_MASK		(1)
#define		ECM_ECMETMK2_6_ETMK2_192		(BIT0)
	#define		ECM_ECMETMK2_6_ETMK2_192_NOMASK	(0)
	#define		ECM_ECMETMK2_6_ETMK2_192_MASK		(1)

/* ECMETMK2_7 */
#define		ECM_ECMETMK2_7_ETMK2_255		(BIT31)
	#define		ECM_ECMETMK2_7_ETMK2_255_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_255_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_254		(BIT30)
	#define		ECM_ECMETMK2_7_ETMK2_254_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_254_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_253		(BIT29)
	#define		ECM_ECMETMK2_7_ETMK2_253_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_253_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_252		(BIT28)
	#define		ECM_ECMETMK2_7_ETMK2_252_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_252_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_251		(BIT27)
	#define		ECM_ECMETMK2_7_ETMK2_251_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_251_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_250		(BIT26)
	#define		ECM_ECMETMK2_7_ETMK2_250_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_250_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_249		(BIT25)
	#define		ECM_ECMETMK2_7_ETMK2_249_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_249_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_248		(BIT24)
	#define		ECM_ECMETMK2_7_ETMK2_248_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_248_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_247		(BIT23)
	#define		ECM_ECMETMK2_7_ETMK2_247_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_247_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_246		(BIT22)
	#define		ECM_ECMETMK2_7_ETMK2_246_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_246_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_245		(BIT21)
	#define		ECM_ECMETMK2_7_ETMK2_245_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_245_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_244		(BIT20)
	#define		ECM_ECMETMK2_7_ETMK2_244_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_244_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_243		(BIT19)
	#define		ECM_ECMETMK2_7_ETMK2_243_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_243_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_242		(BIT18)
	#define		ECM_ECMETMK2_7_ETMK2_242_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_242_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_241		(BIT17)
	#define		ECM_ECMETMK2_7_ETMK2_241_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_241_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_240		(BIT16)
	#define		ECM_ECMETMK2_7_ETMK2_240_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_240_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_239		(BIT15)
	#define		ECM_ECMETMK2_7_ETMK2_239_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_239_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_238		(BIT14)
	#define		ECM_ECMETMK2_7_ETMK2_238_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_238_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_237		(BIT13)
	#define		ECM_ECMETMK2_7_ETMK2_237_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_237_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_236		(BIT12)
	#define		ECM_ECMETMK2_7_ETMK2_236_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_236_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_235		(BIT11)
	#define		ECM_ECMETMK2_7_ETMK2_235_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_235_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_234		(BIT10)
	#define		ECM_ECMETMK2_7_ETMK2_234_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_234_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_233		(BIT9)
	#define		ECM_ECMETMK2_7_ETMK2_233_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_233_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_232		(BIT8)
	#define		ECM_ECMETMK2_7_ETMK2_232_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_232_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_231		(BIT7)
	#define		ECM_ECMETMK2_7_ETMK2_231_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_231_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_230		(BIT6)
	#define		ECM_ECMETMK2_7_ETMK2_230_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_230_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_229		(BIT5)
	#define		ECM_ECMETMK2_7_ETMK2_229_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_229_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_228		(BIT4)
	#define		ECM_ECMETMK2_7_ETMK2_228_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_228_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_227		(BIT3)
	#define		ECM_ECMETMK2_7_ETMK2_227_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_227_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_226		(BIT2)
	#define		ECM_ECMETMK2_7_ETMK2_226_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_226_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_225		(BIT1)
	#define		ECM_ECMETMK2_7_ETMK2_225_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_225_MASK		(1)
#define		ECM_ECMETMK2_7_ETMK2_224		(BIT0)
	#define		ECM_ECMETMK2_7_ETMK2_224_NOMASK	(0)
	#define		ECM_ECMETMK2_7_ETMK2_224_MASK		(1)

/* ECMETMK2_8 */
#define		ECM_ECMETMK2_8_ETMK2_287		(BIT31)
	#define		ECM_ECMETMK2_8_ETMK2_287_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_287_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_286		(BIT30)
	#define		ECM_ECMETMK2_8_ETMK2_286_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_286_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_285		(BIT29)
	#define		ECM_ECMETMK2_8_ETMK2_285_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_285_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_284		(BIT28)
	#define		ECM_ECMETMK2_8_ETMK2_284_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_284_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_283		(BIT27)
	#define		ECM_ECMETMK2_8_ETMK2_283_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_283_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_282		(BIT26)
	#define		ECM_ECMETMK2_8_ETMK2_282_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_282_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_281		(BIT25)
	#define		ECM_ECMETMK2_8_ETMK2_281_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_281_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_280		(BIT24)
	#define		ECM_ECMETMK2_8_ETMK2_280_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_280_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_279		(BIT23)
	#define		ECM_ECMETMK2_8_ETMK2_279_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_279_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_278		(BIT22)
	#define		ECM_ECMETMK2_8_ETMK2_278_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_278_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_277		(BIT21)
	#define		ECM_ECMETMK2_8_ETMK2_277_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_277_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_276		(BIT20)
	#define		ECM_ECMETMK2_8_ETMK2_276_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_276_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_275		(BIT19)
	#define		ECM_ECMETMK2_8_ETMK2_275_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_275_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_274		(BIT18)
	#define		ECM_ECMETMK2_8_ETMK2_274_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_274_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_273		(BIT17)
	#define		ECM_ECMETMK2_8_ETMK2_273_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_273_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_272		(BIT16)
	#define		ECM_ECMETMK2_8_ETMK2_272_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_272_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_271		(BIT15)
	#define		ECM_ECMETMK2_8_ETMK2_271_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_271_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_270		(BIT14)
	#define		ECM_ECMETMK2_8_ETMK2_270_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_270_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_269		(BIT13)
	#define		ECM_ECMETMK2_8_ETMK2_269_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_269_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_268		(BIT12)
	#define		ECM_ECMETMK2_8_ETMK2_268_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_268_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_267		(BIT11)
	#define		ECM_ECMETMK2_8_ETMK2_267_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_267_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_266		(BIT10)
	#define		ECM_ECMETMK2_8_ETMK2_266_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_266_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_265		(BIT9)
	#define		ECM_ECMETMK2_8_ETMK2_265_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_265_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_264		(BIT8)
	#define		ECM_ECMETMK2_8_ETMK2_264_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_264_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_263		(BIT7)
	#define		ECM_ECMETMK2_8_ETMK2_263_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_263_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_262		(BIT6)
	#define		ECM_ECMETMK2_8_ETMK2_262_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_262_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_261		(BIT5)
	#define		ECM_ECMETMK2_8_ETMK2_261_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_261_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_260		(BIT4)
	#define		ECM_ECMETMK2_8_ETMK2_260_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_260_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_259		(BIT3)
	#define		ECM_ECMETMK2_8_ETMK2_259_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_259_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_258		(BIT2)
	#define		ECM_ECMETMK2_8_ETMK2_258_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_258_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_257		(BIT1)
	#define		ECM_ECMETMK2_8_ETMK2_257_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_257_MASK		(1)
#define		ECM_ECMETMK2_8_ETMK2_256		(BIT0)
	#define		ECM_ECMETMK2_8_ETMK2_256_NOMASK	(0)
	#define		ECM_ECMETMK2_8_ETMK2_256_MASK		(1)

/* ECMETMK2_9 */
#define		ECM_ECMETMK2_9_ETMK2_319		(BIT31)
	#define		ECM_ECMETMK2_9_ETMK2_319_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_319_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_318		(BIT30)
	#define		ECM_ECMETMK2_9_ETMK2_318_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_318_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_317		(BIT29)
	#define		ECM_ECMETMK2_9_ETMK2_317_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_317_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_316		(BIT28)
	#define		ECM_ECMETMK2_9_ETMK2_316_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_316_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_315		(BIT27)
	#define		ECM_ECMETMK2_9_ETMK2_315_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_315_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_314		(BIT26)
	#define		ECM_ECMETMK2_9_ETMK2_314_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_314_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_313		(BIT25)
	#define		ECM_ECMETMK2_9_ETMK2_313_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_313_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_312		(BIT24)
	#define		ECM_ECMETMK2_9_ETMK2_312_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_312_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_311		(BIT23)
	#define		ECM_ECMETMK2_9_ETMK2_311_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_311_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_310		(BIT22)
	#define		ECM_ECMETMK2_9_ETMK2_310_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_310_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_309		(BIT21)
	#define		ECM_ECMETMK2_9_ETMK2_309_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_309_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_308		(BIT20)
	#define		ECM_ECMETMK2_9_ETMK2_308_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_308_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_307		(BIT19)
	#define		ECM_ECMETMK2_9_ETMK2_307_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_307_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_306		(BIT18)
	#define		ECM_ECMETMK2_9_ETMK2_306_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_306_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_305		(BIT17)
	#define		ECM_ECMETMK2_9_ETMK2_305_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_305_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_304		(BIT16)
	#define		ECM_ECMETMK2_9_ETMK2_304_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_304_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_303		(BIT15)
	#define		ECM_ECMETMK2_9_ETMK2_303_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_303_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_302		(BIT14)
	#define		ECM_ECMETMK2_9_ETMK2_302_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_302_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_301		(BIT13)
	#define		ECM_ECMETMK2_9_ETMK2_301_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_301_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_300		(BIT12)
	#define		ECM_ECMETMK2_9_ETMK2_300_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_300_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_299		(BIT11)
	#define		ECM_ECMETMK2_9_ETMK2_299_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_299_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_298		(BIT10)
	#define		ECM_ECMETMK2_9_ETMK2_298_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_298_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_297		(BIT9)
	#define		ECM_ECMETMK2_9_ETMK2_297_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_297_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_296		(BIT8)
	#define		ECM_ECMETMK2_9_ETMK2_296_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_296_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_295		(BIT7)
	#define		ECM_ECMETMK2_9_ETMK2_295_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_295_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_294		(BIT6)
	#define		ECM_ECMETMK2_9_ETMK2_294_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_294_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_293		(BIT5)
	#define		ECM_ECMETMK2_9_ETMK2_293_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_293_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_292		(BIT4)
	#define		ECM_ECMETMK2_9_ETMK2_292_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_292_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_291		(BIT3)
	#define		ECM_ECMETMK2_9_ETMK2_291_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_291_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_290		(BIT2)
	#define		ECM_ECMETMK2_9_ETMK2_290_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_290_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_289		(BIT1)
	#define		ECM_ECMETMK2_9_ETMK2_289_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_289_MASK		(1)
#define		ECM_ECMETMK2_9_ETMK2_288		(BIT0)
	#define		ECM_ECMETMK2_9_ETMK2_288_NOMASK	(0)
	#define		ECM_ECMETMK2_9_ETMK2_288_MASK		(1)

/* ECMETMK2_10 */
#define		ECM_ECMETMK2_10_ETMK2_351		(BIT31)
	#define		ECM_ECMETMK2_10_ETMK2_351_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_351_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_350		(BIT30)
	#define		ECM_ECMETMK2_10_ETMK2_350_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_350_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_349		(BIT29)
	#define		ECM_ECMETMK2_10_ETMK2_349_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_349_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_348		(BIT28)
	#define		ECM_ECMETMK2_10_ETMK2_348_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_348_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_347		(BIT27)
	#define		ECM_ECMETMK2_10_ETMK2_347_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_347_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_346		(BIT26)
	#define		ECM_ECMETMK2_10_ETMK2_346_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_346_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_345		(BIT25)
	#define		ECM_ECMETMK2_10_ETMK2_345_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_345_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_344		(BIT24)
	#define		ECM_ECMETMK2_10_ETMK2_344_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_344_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_343		(BIT23)
	#define		ECM_ECMETMK2_10_ETMK2_343_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_343_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_342		(BIT22)
	#define		ECM_ECMETMK2_10_ETMK2_342_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_342_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_341		(BIT21)
	#define		ECM_ECMETMK2_10_ETMK2_341_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_341_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_340		(BIT20)
	#define		ECM_ECMETMK2_10_ETMK2_340_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_340_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_339		(BIT19)
	#define		ECM_ECMETMK2_10_ETMK2_339_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_339_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_338		(BIT18)
	#define		ECM_ECMETMK2_10_ETMK2_338_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_338_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_337		(BIT17)
	#define		ECM_ECMETMK2_10_ETMK2_337_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_337_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_336		(BIT16)
	#define		ECM_ECMETMK2_10_ETMK2_336_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_336_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_335		(BIT15)
	#define		ECM_ECMETMK2_10_ETMK2_335_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_335_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_334		(BIT14)
	#define		ECM_ECMETMK2_10_ETMK2_334_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_334_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_333		(BIT13)
	#define		ECM_ECMETMK2_10_ETMK2_333_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_333_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_332		(BIT12)
	#define		ECM_ECMETMK2_10_ETMK2_332_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_332_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_331		(BIT11)
	#define		ECM_ECMETMK2_10_ETMK2_331_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_331_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_330		(BIT10)
	#define		ECM_ECMETMK2_10_ETMK2_330_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_330_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_329		(BIT9)
	#define		ECM_ECMETMK2_10_ETMK2_329_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_329_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_328		(BIT8)
	#define		ECM_ECMETMK2_10_ETMK2_328_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_328_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_327		(BIT7)
	#define		ECM_ECMETMK2_10_ETMK2_327_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_327_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_326		(BIT6)
	#define		ECM_ECMETMK2_10_ETMK2_326_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_326_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_325		(BIT5)
	#define		ECM_ECMETMK2_10_ETMK2_325_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_325_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_324		(BIT4)
	#define		ECM_ECMETMK2_10_ETMK2_324_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_324_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_323		(BIT3)
	#define		ECM_ECMETMK2_10_ETMK2_323_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_323_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_322		(BIT2)
	#define		ECM_ECMETMK2_10_ETMK2_322_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_322_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_321		(BIT1)
	#define		ECM_ECMETMK2_10_ETMK2_321_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_321_MASK		(1)
#define		ECM_ECMETMK2_10_ETMK2_320		(BIT0)
	#define		ECM_ECMETMK2_10_ETMK2_320_NOMASK	(0)
	#define		ECM_ECMETMK2_10_ETMK2_320_MASK		(1)

/* ECMETMK3_0 */
#define		ECM_ECMETMK3_0_ETMK3_031		(BIT31)
	#define		ECM_ECMETMK3_0_ETMK3_031_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_031_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_030		(BIT30)
	#define		ECM_ECMETMK3_0_ETMK3_030_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_030_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_029		(BIT29)
	#define		ECM_ECMETMK3_0_ETMK3_029_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_029_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_028		(BIT28)
	#define		ECM_ECMETMK3_0_ETMK3_028_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_028_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_027		(BIT27)
	#define		ECM_ECMETMK3_0_ETMK3_027_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_027_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_026		(BIT26)
	#define		ECM_ECMETMK3_0_ETMK3_026_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_026_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_025		(BIT25)
	#define		ECM_ECMETMK3_0_ETMK3_025_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_025_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_024		(BIT24)
	#define		ECM_ECMETMK3_0_ETMK3_024_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_024_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_023		(BIT23)
	#define		ECM_ECMETMK3_0_ETMK3_023_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_023_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_022		(BIT22)
	#define		ECM_ECMETMK3_0_ETMK3_022_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_022_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_021		(BIT21)
	#define		ECM_ECMETMK3_0_ETMK3_021_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_021_MASK		(1)
#define		ECM_ECMETMK3_0_ETMK3_020		(BIT20)
	#define		ECM_ECMETMK3_0_ETMK3_020_NOMASK	(0)
	#define		ECM_ECMETMK3_0_ETMK3_020_MASK		(1)

/* ECMETMK3_1 */
#define		ECM_ECMETMK3_1_ETMK3_063		(BIT31)
	#define		ECM_ECMETMK3_1_ETMK3_063_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_063_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_062		(BIT30)
	#define		ECM_ECMETMK3_1_ETMK3_062_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_062_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_061		(BIT29)
	#define		ECM_ECMETMK3_1_ETMK3_061_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_061_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_060		(BIT28)
	#define		ECM_ECMETMK3_1_ETMK3_060_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_060_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_059		(BIT27)
	#define		ECM_ECMETMK3_1_ETMK3_059_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_059_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_058		(BIT26)
	#define		ECM_ECMETMK3_1_ETMK3_058_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_058_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_057		(BIT25)
	#define		ECM_ECMETMK3_1_ETMK3_057_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_057_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_056		(BIT24)
	#define		ECM_ECMETMK3_1_ETMK3_056_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_056_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_055		(BIT23)
	#define		ECM_ECMETMK3_1_ETMK3_055_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_055_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_054		(BIT22)
	#define		ECM_ECMETMK3_1_ETMK3_054_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_054_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_053		(BIT21)
	#define		ECM_ECMETMK3_1_ETMK3_053_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_053_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_052		(BIT20)
	#define		ECM_ECMETMK3_1_ETMK3_052_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_052_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_051		(BIT19)
	#define		ECM_ECMETMK3_1_ETMK3_051_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_051_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_050		(BIT18)
	#define		ECM_ECMETMK3_1_ETMK3_050_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_050_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_049		(BIT17)
	#define		ECM_ECMETMK3_1_ETMK3_049_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_049_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_048		(BIT16)
	#define		ECM_ECMETMK3_1_ETMK3_048_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_048_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_047		(BIT15)
	#define		ECM_ECMETMK3_1_ETMK3_047_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_047_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_046		(BIT14)
	#define		ECM_ECMETMK3_1_ETMK3_046_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_046_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_045		(BIT13)
	#define		ECM_ECMETMK3_1_ETMK3_045_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_045_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_044		(BIT12)
	#define		ECM_ECMETMK3_1_ETMK3_044_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_044_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_043		(BIT11)
	#define		ECM_ECMETMK3_1_ETMK3_043_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_043_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_042		(BIT10)
	#define		ECM_ECMETMK3_1_ETMK3_042_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_042_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_041		(BIT9)
	#define		ECM_ECMETMK3_1_ETMK3_041_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_041_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_040		(BIT8)
	#define		ECM_ECMETMK3_1_ETMK3_040_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_040_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_039		(BIT7)
	#define		ECM_ECMETMK3_1_ETMK3_039_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_039_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_038		(BIT6)
	#define		ECM_ECMETMK3_1_ETMK3_038_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_038_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_037		(BIT5)
	#define		ECM_ECMETMK3_1_ETMK3_037_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_037_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_036		(BIT4)
	#define		ECM_ECMETMK3_1_ETMK3_036_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_036_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_035		(BIT3)
	#define		ECM_ECMETMK3_1_ETMK3_035_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_035_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_034		(BIT2)
	#define		ECM_ECMETMK3_1_ETMK3_034_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_034_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_033		(BIT1)
	#define		ECM_ECMETMK3_1_ETMK3_033_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_033_MASK		(1)
#define		ECM_ECMETMK3_1_ETMK3_032		(BIT0)
	#define		ECM_ECMETMK3_1_ETMK3_032_NOMASK	(0)
	#define		ECM_ECMETMK3_1_ETMK3_032_MASK		(1)

/* ECMETMK3_2 */
#define		ECM_ECMETMK3_2_ETMK3_095		(BIT31)
	#define		ECM_ECMETMK3_2_ETMK3_095_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_095_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_094		(BIT30)
	#define		ECM_ECMETMK3_2_ETMK3_094_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_094_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_093		(BIT29)
	#define		ECM_ECMETMK3_2_ETMK3_093_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_093_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_092		(BIT28)
	#define		ECM_ECMETMK3_2_ETMK3_092_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_092_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_091		(BIT27)
	#define		ECM_ECMETMK3_2_ETMK3_091_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_091_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_090		(BIT26)
	#define		ECM_ECMETMK3_2_ETMK3_090_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_090_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_089		(BIT25)
	#define		ECM_ECMETMK3_2_ETMK3_089_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_089_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_088		(BIT24)
	#define		ECM_ECMETMK3_2_ETMK3_088_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_088_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_087		(BIT23)
	#define		ECM_ECMETMK3_2_ETMK3_087_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_087_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_086		(BIT22)
	#define		ECM_ECMETMK3_2_ETMK3_086_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_086_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_085		(BIT21)
	#define		ECM_ECMETMK3_2_ETMK3_085_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_085_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_084		(BIT20)
	#define		ECM_ECMETMK3_2_ETMK3_084_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_084_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_083		(BIT19)
	#define		ECM_ECMETMK3_2_ETMK3_083_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_083_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_082		(BIT18)
	#define		ECM_ECMETMK3_2_ETMK3_082_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_082_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_081		(BIT17)
	#define		ECM_ECMETMK3_2_ETMK3_081_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_081_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_080		(BIT16)
	#define		ECM_ECMETMK3_2_ETMK3_080_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_080_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_079		(BIT15)
	#define		ECM_ECMETMK3_2_ETMK3_079_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_079_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_078		(BIT14)
	#define		ECM_ECMETMK3_2_ETMK3_078_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_078_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_077		(BIT13)
	#define		ECM_ECMETMK3_2_ETMK3_077_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_077_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_076		(BIT12)
	#define		ECM_ECMETMK3_2_ETMK3_076_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_076_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_075		(BIT11)
	#define		ECM_ECMETMK3_2_ETMK3_075_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_075_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_074		(BIT10)
	#define		ECM_ECMETMK3_2_ETMK3_074_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_074_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_073		(BIT9)
	#define		ECM_ECMETMK3_2_ETMK3_073_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_073_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_072		(BIT8)
	#define		ECM_ECMETMK3_2_ETMK3_072_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_072_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_071		(BIT7)
	#define		ECM_ECMETMK3_2_ETMK3_071_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_071_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_070		(BIT6)
	#define		ECM_ECMETMK3_2_ETMK3_070_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_070_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_069		(BIT5)
	#define		ECM_ECMETMK3_2_ETMK3_069_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_069_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_068		(BIT4)
	#define		ECM_ECMETMK3_2_ETMK3_068_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_068_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_067		(BIT3)
	#define		ECM_ECMETMK3_2_ETMK3_067_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_067_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_066		(BIT2)
	#define		ECM_ECMETMK3_2_ETMK3_066_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_066_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_065		(BIT1)
	#define		ECM_ECMETMK3_2_ETMK3_065_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_065_MASK		(1)
#define		ECM_ECMETMK3_2_ETMK3_064		(BIT0)
	#define		ECM_ECMETMK3_2_ETMK3_064_NOMASK	(0)
	#define		ECM_ECMETMK3_2_ETMK3_064_MASK		(1)

/* ECMETMK3_3 */
#define		ECM_ECMETMK3_3_ETMK3_127		(BIT31)
	#define		ECM_ECMETMK3_3_ETMK3_127_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_127_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_126		(BIT30)
	#define		ECM_ECMETMK3_3_ETMK3_126_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_126_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_125		(BIT29)
	#define		ECM_ECMETMK3_3_ETMK3_125_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_125_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_124		(BIT28)
	#define		ECM_ECMETMK3_3_ETMK3_124_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_124_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_123		(BIT27)
	#define		ECM_ECMETMK3_3_ETMK3_123_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_123_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_122		(BIT26)
	#define		ECM_ECMETMK3_3_ETMK3_122_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_122_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_121		(BIT25)
	#define		ECM_ECMETMK3_3_ETMK3_121_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_121_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_120		(BIT24)
	#define		ECM_ECMETMK3_3_ETMK3_120_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_120_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_119		(BIT23)
	#define		ECM_ECMETMK3_3_ETMK3_119_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_119_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_118		(BIT22)
	#define		ECM_ECMETMK3_3_ETMK3_118_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_118_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_117		(BIT21)
	#define		ECM_ECMETMK3_3_ETMK3_117_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_117_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_116		(BIT20)
	#define		ECM_ECMETMK3_3_ETMK3_116_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_116_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_115		(BIT19)
	#define		ECM_ECMETMK3_3_ETMK3_115_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_115_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_114		(BIT18)
	#define		ECM_ECMETMK3_3_ETMK3_114_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_114_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_113		(BIT17)
	#define		ECM_ECMETMK3_3_ETMK3_113_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_113_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_112		(BIT16)
	#define		ECM_ECMETMK3_3_ETMK3_112_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_112_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_111		(BIT15)
	#define		ECM_ECMETMK3_3_ETMK3_111_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_111_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_110		(BIT14)
	#define		ECM_ECMETMK3_3_ETMK3_110_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_110_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_109		(BIT13)
	#define		ECM_ECMETMK3_3_ETMK3_109_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_109_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_108		(BIT12)
	#define		ECM_ECMETMK3_3_ETMK3_108_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_108_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_107		(BIT11)
	#define		ECM_ECMETMK3_3_ETMK3_107_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_107_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_106		(BIT10)
	#define		ECM_ECMETMK3_3_ETMK3_106_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_106_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_105		(BIT9)
	#define		ECM_ECMETMK3_3_ETMK3_105_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_105_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_104		(BIT8)
	#define		ECM_ECMETMK3_3_ETMK3_104_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_104_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_103		(BIT7)
	#define		ECM_ECMETMK3_3_ETMK3_103_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_103_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_102		(BIT6)
	#define		ECM_ECMETMK3_3_ETMK3_102_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_102_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_101		(BIT5)
	#define		ECM_ECMETMK3_3_ETMK3_101_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_101_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_100		(BIT4)
	#define		ECM_ECMETMK3_3_ETMK3_100_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_100_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_099		(BIT3)
	#define		ECM_ECMETMK3_3_ETMK3_099_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_099_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_098		(BIT2)
	#define		ECM_ECMETMK3_3_ETMK3_098_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_098_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_097		(BIT1)
	#define		ECM_ECMETMK3_3_ETMK3_097_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_097_MASK		(1)
#define		ECM_ECMETMK3_3_ETMK3_096		(BIT0)
	#define		ECM_ECMETMK3_3_ETMK3_096_NOMASK	(0)
	#define		ECM_ECMETMK3_3_ETMK3_096_MASK		(1)

/* ECMETMK3_4 */
#define		ECM_ECMETMK3_4_ETMK3_159		(BIT31)
	#define		ECM_ECMETMK3_4_ETMK3_159_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_159_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_158		(BIT30)
	#define		ECM_ECMETMK3_4_ETMK3_158_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_158_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_157		(BIT29)
	#define		ECM_ECMETMK3_4_ETMK3_157_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_157_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_156		(BIT28)
	#define		ECM_ECMETMK3_4_ETMK3_156_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_156_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_155		(BIT27)
	#define		ECM_ECMETMK3_4_ETMK3_155_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_155_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_154		(BIT26)
	#define		ECM_ECMETMK3_4_ETMK3_154_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_154_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_153		(BIT25)
	#define		ECM_ECMETMK3_4_ETMK3_153_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_153_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_152		(BIT24)
	#define		ECM_ECMETMK3_4_ETMK3_152_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_152_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_151		(BIT23)
	#define		ECM_ECMETMK3_4_ETMK3_151_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_151_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_150		(BIT22)
	#define		ECM_ECMETMK3_4_ETMK3_150_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_150_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_149		(BIT21)
	#define		ECM_ECMETMK3_4_ETMK3_149_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_149_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_148		(BIT20)
	#define		ECM_ECMETMK3_4_ETMK3_148_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_148_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_147		(BIT19)
	#define		ECM_ECMETMK3_4_ETMK3_147_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_147_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_146		(BIT18)
	#define		ECM_ECMETMK3_4_ETMK3_146_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_146_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_145		(BIT17)
	#define		ECM_ECMETMK3_4_ETMK3_145_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_145_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_144		(BIT16)
	#define		ECM_ECMETMK3_4_ETMK3_144_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_144_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_143		(BIT15)
	#define		ECM_ECMETMK3_4_ETMK3_143_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_143_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_142		(BIT14)
	#define		ECM_ECMETMK3_4_ETMK3_142_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_142_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_141		(BIT13)
	#define		ECM_ECMETMK3_4_ETMK3_141_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_141_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_140		(BIT12)
	#define		ECM_ECMETMK3_4_ETMK3_140_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_140_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_139		(BIT11)
	#define		ECM_ECMETMK3_4_ETMK3_139_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_139_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_138		(BIT10)
	#define		ECM_ECMETMK3_4_ETMK3_138_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_138_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_137		(BIT9)
	#define		ECM_ECMETMK3_4_ETMK3_137_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_137_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_136		(BIT8)
	#define		ECM_ECMETMK3_4_ETMK3_136_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_136_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_135		(BIT7)
	#define		ECM_ECMETMK3_4_ETMK3_135_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_135_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_134		(BIT6)
	#define		ECM_ECMETMK3_4_ETMK3_134_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_134_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_133		(BIT5)
	#define		ECM_ECMETMK3_4_ETMK3_133_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_133_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_132		(BIT4)
	#define		ECM_ECMETMK3_4_ETMK3_132_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_132_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_131		(BIT3)
	#define		ECM_ECMETMK3_4_ETMK3_131_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_131_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_130		(BIT2)
	#define		ECM_ECMETMK3_4_ETMK3_130_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_130_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_129		(BIT1)
	#define		ECM_ECMETMK3_4_ETMK3_129_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_129_MASK		(1)
#define		ECM_ECMETMK3_4_ETMK3_128		(BIT0)
	#define		ECM_ECMETMK3_4_ETMK3_128_NOMASK	(0)
	#define		ECM_ECMETMK3_4_ETMK3_128_MASK		(1)

/* ECMETMK3_5 */
#define		ECM_ECMETMK3_5_ETMK3_191		(BIT31)
	#define		ECM_ECMETMK3_5_ETMK3_191_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_191_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_190		(BIT30)
	#define		ECM_ECMETMK3_5_ETMK3_190_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_190_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_189		(BIT29)
	#define		ECM_ECMETMK3_5_ETMK3_189_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_189_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_188		(BIT28)
	#define		ECM_ECMETMK3_5_ETMK3_188_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_188_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_187		(BIT27)
	#define		ECM_ECMETMK3_5_ETMK3_187_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_187_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_186		(BIT26)
	#define		ECM_ECMETMK3_5_ETMK3_186_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_186_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_185		(BIT25)
	#define		ECM_ECMETMK3_5_ETMK3_185_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_185_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_184		(BIT24)
	#define		ECM_ECMETMK3_5_ETMK3_184_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_184_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_183		(BIT23)
	#define		ECM_ECMETMK3_5_ETMK3_183_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_183_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_182		(BIT22)
	#define		ECM_ECMETMK3_5_ETMK3_182_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_182_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_181		(BIT21)
	#define		ECM_ECMETMK3_5_ETMK3_181_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_181_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_180		(BIT20)
	#define		ECM_ECMETMK3_5_ETMK3_180_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_180_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_179		(BIT19)
	#define		ECM_ECMETMK3_5_ETMK3_179_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_179_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_178		(BIT18)
	#define		ECM_ECMETMK3_5_ETMK3_178_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_178_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_177		(BIT17)
	#define		ECM_ECMETMK3_5_ETMK3_177_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_177_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_176		(BIT16)
	#define		ECM_ECMETMK3_5_ETMK3_176_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_176_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_175		(BIT15)
	#define		ECM_ECMETMK3_5_ETMK3_175_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_175_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_174		(BIT14)
	#define		ECM_ECMETMK3_5_ETMK3_174_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_174_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_173		(BIT13)
	#define		ECM_ECMETMK3_5_ETMK3_173_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_173_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_172		(BIT12)
	#define		ECM_ECMETMK3_5_ETMK3_172_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_172_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_171		(BIT11)
	#define		ECM_ECMETMK3_5_ETMK3_171_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_171_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_170		(BIT10)
	#define		ECM_ECMETMK3_5_ETMK3_170_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_170_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_169		(BIT9)
	#define		ECM_ECMETMK3_5_ETMK3_169_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_169_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_168		(BIT8)
	#define		ECM_ECMETMK3_5_ETMK3_168_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_168_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_167		(BIT7)
	#define		ECM_ECMETMK3_5_ETMK3_167_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_167_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_166		(BIT6)
	#define		ECM_ECMETMK3_5_ETMK3_166_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_166_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_165		(BIT5)
	#define		ECM_ECMETMK3_5_ETMK3_165_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_165_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_164		(BIT4)
	#define		ECM_ECMETMK3_5_ETMK3_164_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_164_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_163		(BIT3)
	#define		ECM_ECMETMK3_5_ETMK3_163_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_163_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_162		(BIT2)
	#define		ECM_ECMETMK3_5_ETMK3_162_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_162_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_161		(BIT1)
	#define		ECM_ECMETMK3_5_ETMK3_161_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_161_MASK		(1)
#define		ECM_ECMETMK3_5_ETMK3_160		(BIT0)
	#define		ECM_ECMETMK3_5_ETMK3_160_NOMASK	(0)
	#define		ECM_ECMETMK3_5_ETMK3_160_MASK		(1)

/* ECMETMK3_6 */
#define		ECM_ECMETMK3_6_ETMK3_223		(BIT31)
	#define		ECM_ECMETMK3_6_ETMK3_223_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_223_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_222		(BIT30)
	#define		ECM_ECMETMK3_6_ETMK3_222_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_222_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_221		(BIT29)
	#define		ECM_ECMETMK3_6_ETMK3_221_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_221_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_220		(BIT28)
	#define		ECM_ECMETMK3_6_ETMK3_220_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_220_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_219		(BIT27)
	#define		ECM_ECMETMK3_6_ETMK3_219_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_219_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_218		(BIT26)
	#define		ECM_ECMETMK3_6_ETMK3_218_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_218_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_217		(BIT25)
	#define		ECM_ECMETMK3_6_ETMK3_217_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_217_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_216		(BIT24)
	#define		ECM_ECMETMK3_6_ETMK3_216_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_216_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_215		(BIT23)
	#define		ECM_ECMETMK3_6_ETMK3_215_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_215_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_214		(BIT22)
	#define		ECM_ECMETMK3_6_ETMK3_214_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_214_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_213		(BIT21)
	#define		ECM_ECMETMK3_6_ETMK3_213_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_213_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_212		(BIT20)
	#define		ECM_ECMETMK3_6_ETMK3_212_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_212_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_211		(BIT19)
	#define		ECM_ECMETMK3_6_ETMK3_211_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_211_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_210		(BIT18)
	#define		ECM_ECMETMK3_6_ETMK3_210_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_210_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_209		(BIT17)
	#define		ECM_ECMETMK3_6_ETMK3_209_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_209_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_208		(BIT16)
	#define		ECM_ECMETMK3_6_ETMK3_208_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_208_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_207		(BIT15)
	#define		ECM_ECMETMK3_6_ETMK3_207_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_207_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_206		(BIT14)
	#define		ECM_ECMETMK3_6_ETMK3_206_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_206_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_205		(BIT13)
	#define		ECM_ECMETMK3_6_ETMK3_205_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_205_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_204		(BIT12)
	#define		ECM_ECMETMK3_6_ETMK3_204_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_204_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_203		(BIT11)
	#define		ECM_ECMETMK3_6_ETMK3_203_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_203_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_202		(BIT10)
	#define		ECM_ECMETMK3_6_ETMK3_202_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_202_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_201		(BIT9)
	#define		ECM_ECMETMK3_6_ETMK3_201_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_201_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_200		(BIT8)
	#define		ECM_ECMETMK3_6_ETMK3_200_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_200_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_199		(BIT7)
	#define		ECM_ECMETMK3_6_ETMK3_199_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_199_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_198		(BIT6)
	#define		ECM_ECMETMK3_6_ETMK3_198_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_198_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_197		(BIT5)
	#define		ECM_ECMETMK3_6_ETMK3_197_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_197_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_196		(BIT4)
	#define		ECM_ECMETMK3_6_ETMK3_196_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_196_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_195		(BIT3)
	#define		ECM_ECMETMK3_6_ETMK3_195_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_195_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_194		(BIT2)
	#define		ECM_ECMETMK3_6_ETMK3_194_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_194_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_193		(BIT1)
	#define		ECM_ECMETMK3_6_ETMK3_193_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_193_MASK		(1)
#define		ECM_ECMETMK3_6_ETMK3_192		(BIT0)
	#define		ECM_ECMETMK3_6_ETMK3_192_NOMASK	(0)
	#define		ECM_ECMETMK3_6_ETMK3_192_MASK		(1)

/* ECMETMK3_7 */
#define		ECM_ECMETMK3_7_ETMK3_255		(BIT31)
	#define		ECM_ECMETMK3_7_ETMK3_255_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_255_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_254		(BIT30)
	#define		ECM_ECMETMK3_7_ETMK3_254_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_254_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_253		(BIT29)
	#define		ECM_ECMETMK3_7_ETMK3_253_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_253_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_252		(BIT28)
	#define		ECM_ECMETMK3_7_ETMK3_252_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_252_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_251		(BIT27)
	#define		ECM_ECMETMK3_7_ETMK3_251_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_251_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_250		(BIT26)
	#define		ECM_ECMETMK3_7_ETMK3_250_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_250_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_249		(BIT25)
	#define		ECM_ECMETMK3_7_ETMK3_249_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_249_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_248		(BIT24)
	#define		ECM_ECMETMK3_7_ETMK3_248_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_248_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_247		(BIT23)
	#define		ECM_ECMETMK3_7_ETMK3_247_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_247_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_246		(BIT22)
	#define		ECM_ECMETMK3_7_ETMK3_246_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_246_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_245		(BIT21)
	#define		ECM_ECMETMK3_7_ETMK3_245_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_245_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_244		(BIT20)
	#define		ECM_ECMETMK3_7_ETMK3_244_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_244_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_243		(BIT19)
	#define		ECM_ECMETMK3_7_ETMK3_243_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_243_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_242		(BIT18)
	#define		ECM_ECMETMK3_7_ETMK3_242_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_242_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_241		(BIT17)
	#define		ECM_ECMETMK3_7_ETMK3_241_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_241_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_240		(BIT16)
	#define		ECM_ECMETMK3_7_ETMK3_240_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_240_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_239		(BIT15)
	#define		ECM_ECMETMK3_7_ETMK3_239_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_239_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_238		(BIT14)
	#define		ECM_ECMETMK3_7_ETMK3_238_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_238_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_237		(BIT13)
	#define		ECM_ECMETMK3_7_ETMK3_237_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_237_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_236		(BIT12)
	#define		ECM_ECMETMK3_7_ETMK3_236_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_236_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_235		(BIT11)
	#define		ECM_ECMETMK3_7_ETMK3_235_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_235_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_234		(BIT10)
	#define		ECM_ECMETMK3_7_ETMK3_234_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_234_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_233		(BIT9)
	#define		ECM_ECMETMK3_7_ETMK3_233_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_233_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_232		(BIT8)
	#define		ECM_ECMETMK3_7_ETMK3_232_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_232_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_231		(BIT7)
	#define		ECM_ECMETMK3_7_ETMK3_231_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_231_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_230		(BIT6)
	#define		ECM_ECMETMK3_7_ETMK3_230_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_230_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_229		(BIT5)
	#define		ECM_ECMETMK3_7_ETMK3_229_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_229_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_228		(BIT4)
	#define		ECM_ECMETMK3_7_ETMK3_228_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_228_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_227		(BIT3)
	#define		ECM_ECMETMK3_7_ETMK3_227_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_227_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_226		(BIT2)
	#define		ECM_ECMETMK3_7_ETMK3_226_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_226_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_225		(BIT1)
	#define		ECM_ECMETMK3_7_ETMK3_225_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_225_MASK		(1)
#define		ECM_ECMETMK3_7_ETMK3_224		(BIT0)
	#define		ECM_ECMETMK3_7_ETMK3_224_NOMASK	(0)
	#define		ECM_ECMETMK3_7_ETMK3_224_MASK		(1)

/* ECMETMK3_8 */
#define		ECM_ECMETMK3_8_ETMK3_287		(BIT31)
	#define		ECM_ECMETMK3_8_ETMK3_287_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_287_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_286		(BIT30)
	#define		ECM_ECMETMK3_8_ETMK3_286_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_286_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_285		(BIT29)
	#define		ECM_ECMETMK3_8_ETMK3_285_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_285_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_284		(BIT28)
	#define		ECM_ECMETMK3_8_ETMK3_284_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_284_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_283		(BIT27)
	#define		ECM_ECMETMK3_8_ETMK3_283_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_283_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_282		(BIT26)
	#define		ECM_ECMETMK3_8_ETMK3_282_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_282_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_281		(BIT25)
	#define		ECM_ECMETMK3_8_ETMK3_281_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_281_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_280		(BIT24)
	#define		ECM_ECMETMK3_8_ETMK3_280_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_280_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_279		(BIT23)
	#define		ECM_ECMETMK3_8_ETMK3_279_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_279_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_278		(BIT22)
	#define		ECM_ECMETMK3_8_ETMK3_278_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_278_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_277		(BIT21)
	#define		ECM_ECMETMK3_8_ETMK3_277_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_277_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_276		(BIT20)
	#define		ECM_ECMETMK3_8_ETMK3_276_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_276_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_275		(BIT19)
	#define		ECM_ECMETMK3_8_ETMK3_275_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_275_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_274		(BIT18)
	#define		ECM_ECMETMK3_8_ETMK3_274_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_274_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_273		(BIT17)
	#define		ECM_ECMETMK3_8_ETMK3_273_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_273_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_272		(BIT16)
	#define		ECM_ECMETMK3_8_ETMK3_272_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_272_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_271		(BIT15)
	#define		ECM_ECMETMK3_8_ETMK3_271_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_271_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_270		(BIT14)
	#define		ECM_ECMETMK3_8_ETMK3_270_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_270_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_269		(BIT13)
	#define		ECM_ECMETMK3_8_ETMK3_269_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_269_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_268		(BIT12)
	#define		ECM_ECMETMK3_8_ETMK3_268_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_268_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_267		(BIT11)
	#define		ECM_ECMETMK3_8_ETMK3_267_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_267_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_266		(BIT10)
	#define		ECM_ECMETMK3_8_ETMK3_266_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_266_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_265		(BIT9)
	#define		ECM_ECMETMK3_8_ETMK3_265_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_265_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_264		(BIT8)
	#define		ECM_ECMETMK3_8_ETMK3_264_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_264_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_263		(BIT7)
	#define		ECM_ECMETMK3_8_ETMK3_263_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_263_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_262		(BIT6)
	#define		ECM_ECMETMK3_8_ETMK3_262_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_262_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_261		(BIT5)
	#define		ECM_ECMETMK3_8_ETMK3_261_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_261_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_260		(BIT4)
	#define		ECM_ECMETMK3_8_ETMK3_260_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_260_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_259		(BIT3)
	#define		ECM_ECMETMK3_8_ETMK3_259_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_259_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_258		(BIT2)
	#define		ECM_ECMETMK3_8_ETMK3_258_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_258_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_257		(BIT1)
	#define		ECM_ECMETMK3_8_ETMK3_257_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_257_MASK		(1)
#define		ECM_ECMETMK3_8_ETMK3_256		(BIT0)
	#define		ECM_ECMETMK3_8_ETMK3_256_NOMASK	(0)
	#define		ECM_ECMETMK3_8_ETMK3_256_MASK		(1)

/* ECMETMK3_9 */
#define		ECM_ECMETMK3_9_ETMK3_319		(BIT31)
	#define		ECM_ECMETMK3_9_ETMK3_319_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_319_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_318		(BIT30)
	#define		ECM_ECMETMK3_9_ETMK3_318_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_318_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_317		(BIT29)
	#define		ECM_ECMETMK3_9_ETMK3_317_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_317_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_316		(BIT28)
	#define		ECM_ECMETMK3_9_ETMK3_316_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_316_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_315		(BIT27)
	#define		ECM_ECMETMK3_9_ETMK3_315_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_315_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_314		(BIT26)
	#define		ECM_ECMETMK3_9_ETMK3_314_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_314_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_313		(BIT25)
	#define		ECM_ECMETMK3_9_ETMK3_313_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_313_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_312		(BIT24)
	#define		ECM_ECMETMK3_9_ETMK3_312_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_312_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_311		(BIT23)
	#define		ECM_ECMETMK3_9_ETMK3_311_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_311_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_310		(BIT22)
	#define		ECM_ECMETMK3_9_ETMK3_310_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_310_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_309		(BIT21)
	#define		ECM_ECMETMK3_9_ETMK3_309_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_309_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_308		(BIT20)
	#define		ECM_ECMETMK3_9_ETMK3_308_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_308_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_307		(BIT19)
	#define		ECM_ECMETMK3_9_ETMK3_307_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_307_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_306		(BIT18)
	#define		ECM_ECMETMK3_9_ETMK3_306_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_306_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_305		(BIT17)
	#define		ECM_ECMETMK3_9_ETMK3_305_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_305_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_304		(BIT16)
	#define		ECM_ECMETMK3_9_ETMK3_304_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_304_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_303		(BIT15)
	#define		ECM_ECMETMK3_9_ETMK3_303_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_303_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_302		(BIT14)
	#define		ECM_ECMETMK3_9_ETMK3_302_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_302_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_301		(BIT13)
	#define		ECM_ECMETMK3_9_ETMK3_301_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_301_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_300		(BIT12)
	#define		ECM_ECMETMK3_9_ETMK3_300_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_300_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_299		(BIT11)
	#define		ECM_ECMETMK3_9_ETMK3_299_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_299_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_298		(BIT10)
	#define		ECM_ECMETMK3_9_ETMK3_298_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_298_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_297		(BIT9)
	#define		ECM_ECMETMK3_9_ETMK3_297_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_297_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_296		(BIT8)
	#define		ECM_ECMETMK3_9_ETMK3_296_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_296_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_295		(BIT7)
	#define		ECM_ECMETMK3_9_ETMK3_295_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_295_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_294		(BIT6)
	#define		ECM_ECMETMK3_9_ETMK3_294_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_294_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_293		(BIT5)
	#define		ECM_ECMETMK3_9_ETMK3_293_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_293_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_292		(BIT4)
	#define		ECM_ECMETMK3_9_ETMK3_292_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_292_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_291		(BIT3)
	#define		ECM_ECMETMK3_9_ETMK3_291_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_291_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_290		(BIT2)
	#define		ECM_ECMETMK3_9_ETMK3_290_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_290_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_289		(BIT1)
	#define		ECM_ECMETMK3_9_ETMK3_289_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_289_MASK		(1)
#define		ECM_ECMETMK3_9_ETMK3_288		(BIT0)
	#define		ECM_ECMETMK3_9_ETMK3_288_NOMASK	(0)
	#define		ECM_ECMETMK3_9_ETMK3_288_MASK		(1)

/* ECMETMK3_10 */
#define		ECM_ECMETMK3_10_ETMK3_351		(BIT31)
	#define		ECM_ECMETMK3_10_ETMK3_351_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_351_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_350		(BIT30)
	#define		ECM_ECMETMK3_10_ETMK3_350_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_350_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_349		(BIT29)
	#define		ECM_ECMETMK3_10_ETMK3_349_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_349_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_348		(BIT28)
	#define		ECM_ECMETMK3_10_ETMK3_348_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_348_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_347		(BIT27)
	#define		ECM_ECMETMK3_10_ETMK3_347_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_347_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_346		(BIT26)
	#define		ECM_ECMETMK3_10_ETMK3_346_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_346_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_345		(BIT25)
	#define		ECM_ECMETMK3_10_ETMK3_345_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_345_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_344		(BIT24)
	#define		ECM_ECMETMK3_10_ETMK3_344_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_344_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_343		(BIT23)
	#define		ECM_ECMETMK3_10_ETMK3_343_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_343_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_342		(BIT22)
	#define		ECM_ECMETMK3_10_ETMK3_342_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_342_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_341		(BIT21)
	#define		ECM_ECMETMK3_10_ETMK3_341_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_341_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_340		(BIT20)
	#define		ECM_ECMETMK3_10_ETMK3_340_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_340_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_339		(BIT19)
	#define		ECM_ECMETMK3_10_ETMK3_339_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_339_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_338		(BIT18)
	#define		ECM_ECMETMK3_10_ETMK3_338_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_338_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_337		(BIT17)
	#define		ECM_ECMETMK3_10_ETMK3_337_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_337_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_336		(BIT16)
	#define		ECM_ECMETMK3_10_ETMK3_336_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_336_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_335		(BIT15)
	#define		ECM_ECMETMK3_10_ETMK3_335_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_335_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_334		(BIT14)
	#define		ECM_ECMETMK3_10_ETMK3_334_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_334_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_333		(BIT13)
	#define		ECM_ECMETMK3_10_ETMK3_333_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_333_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_332		(BIT12)
	#define		ECM_ECMETMK3_10_ETMK3_332_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_332_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_331		(BIT11)
	#define		ECM_ECMETMK3_10_ETMK3_331_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_331_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_330		(BIT10)
	#define		ECM_ECMETMK3_10_ETMK3_330_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_330_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_329		(BIT9)
	#define		ECM_ECMETMK3_10_ETMK3_329_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_329_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_328		(BIT8)
	#define		ECM_ECMETMK3_10_ETMK3_328_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_328_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_327		(BIT7)
	#define		ECM_ECMETMK3_10_ETMK3_327_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_327_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_326		(BIT6)
	#define		ECM_ECMETMK3_10_ETMK3_326_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_326_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_325		(BIT5)
	#define		ECM_ECMETMK3_10_ETMK3_325_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_325_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_324		(BIT4)
	#define		ECM_ECMETMK3_10_ETMK3_324_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_324_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_323		(BIT3)
	#define		ECM_ECMETMK3_10_ETMK3_323_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_323_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_322		(BIT2)
	#define		ECM_ECMETMK3_10_ETMK3_322_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_322_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_321		(BIT1)
	#define		ECM_ECMETMK3_10_ETMK3_321_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_321_MASK		(1)
#define		ECM_ECMETMK3_10_ETMK3_320		(BIT0)
	#define		ECM_ECMETMK3_10_ETMK3_320_NOMASK	(0)
	#define		ECM_ECMETMK3_10_ETMK3_320_MASK		(1)


/* ECMESSTC0 */
#define		ECM_ECMESSTC0_CLSSE031		(BIT31)
	#define		ECM_ECMESSTC0_CLSSE031_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE031_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE030		(BIT30)
	#define		ECM_ECMESSTC0_CLSSE030_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE030_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE029		(BIT29)
	#define		ECM_ECMESSTC0_CLSSE029_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE029_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE028		(BIT28)
	#define		ECM_ECMESSTC0_CLSSE028_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE028_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE027		(BIT27)
	#define		ECM_ECMESSTC0_CLSSE027_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE027_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE026		(BIT26)
	#define		ECM_ECMESSTC0_CLSSE026_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE026_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE025		(BIT25)
	#define		ECM_ECMESSTC0_CLSSE025_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE025_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE024		(BIT24)
	#define		ECM_ECMESSTC0_CLSSE024_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE024_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE023		(BIT23)
	#define		ECM_ECMESSTC0_CLSSE023_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE023_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE022		(BIT22)
	#define		ECM_ECMESSTC0_CLSSE022_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE022_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE021		(BIT21)
	#define		ECM_ECMESSTC0_CLSSE021_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE021_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE020		(BIT20)
	#define		ECM_ECMESSTC0_CLSSE020_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE020_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE019		(BIT19)
	#define		ECM_ECMESSTC0_CLSSE019_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE019_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE018		(BIT18)
	#define		ECM_ECMESSTC0_CLSSE018_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE018_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE017		(BIT17)
	#define		ECM_ECMESSTC0_CLSSE017_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE017_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE016		(BIT16)
	#define		ECM_ECMESSTC0_CLSSE016_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE016_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE015		(BIT15)
	#define		ECM_ECMESSTC0_CLSSE015_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE015_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE014		(BIT14)
	#define		ECM_ECMESSTC0_CLSSE014_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE014_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE013		(BIT13)
	#define		ECM_ECMESSTC0_CLSSE013_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE013_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE012		(BIT12)
	#define		ECM_ECMESSTC0_CLSSE012_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE012_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE011		(BIT11)
	#define		ECM_ECMESSTC0_CLSSE011_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE011_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE010		(BIT10)
	#define		ECM_ECMESSTC0_CLSSE010_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE010_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE009		(BIT9)
	#define		ECM_ECMESSTC0_CLSSE009_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE009_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE008		(BIT8)
	#define		ECM_ECMESSTC0_CLSSE008_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE008_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE007		(BIT7)
	#define		ECM_ECMESSTC0_CLSSE007_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE007_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE006		(BIT6)
	#define		ECM_ECMESSTC0_CLSSE006_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE006_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE005		(BIT5)
	#define		ECM_ECMESSTC0_CLSSE005_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE005_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE004		(BIT4)
	#define		ECM_ECMESSTC0_CLSSE004_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE004_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE003		(BIT3)
	#define		ECM_ECMESSTC0_CLSSE003_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE003_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE002		(BIT2)
	#define		ECM_ECMESSTC0_CLSSE002_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE002_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE001		(BIT1)
	#define		ECM_ECMESSTC0_CLSSE001_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE001_CLR		(1)
#define		ECM_ECMESSTC0_CLSSE000		(BIT0)
	#define		ECM_ECMESSTC0_CLSSE000_NOCLR	(0)
	#define		ECM_ECMESSTC0_CLSSE000_CLR		(1)

/* ECMESSTC1 */
#define		ECM_ECMESSTC1_CLSSE063		(BIT31)
	#define		ECM_ECMESSTC1_CLSSE063_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE063_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE062		(BIT30)
	#define		ECM_ECMESSTC1_CLSSE062_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE062_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE061		(BIT29)
	#define		ECM_ECMESSTC1_CLSSE061_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE061_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE060		(BIT28)
	#define		ECM_ECMESSTC1_CLSSE060_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE060_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE059		(BIT27)
	#define		ECM_ECMESSTC1_CLSSE059_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE059_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE058		(BIT26)
	#define		ECM_ECMESSTC1_CLSSE058_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE058_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE057		(BIT25)
	#define		ECM_ECMESSTC1_CLSSE057_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE057_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE056		(BIT24)
	#define		ECM_ECMESSTC1_CLSSE056_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE056_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE055		(BIT23)
	#define		ECM_ECMESSTC1_CLSSE055_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE055_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE054		(BIT22)
	#define		ECM_ECMESSTC1_CLSSE054_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE054_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE053		(BIT21)
	#define		ECM_ECMESSTC1_CLSSE053_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE053_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE052		(BIT20)
	#define		ECM_ECMESSTC1_CLSSE052_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE052_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE051		(BIT19)
	#define		ECM_ECMESSTC1_CLSSE051_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE051_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE050		(BIT18)
	#define		ECM_ECMESSTC1_CLSSE050_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE050_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE049		(BIT17)
	#define		ECM_ECMESSTC1_CLSSE049_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE049_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE048		(BIT16)
	#define		ECM_ECMESSTC1_CLSSE048_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE048_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE047		(BIT15)
	#define		ECM_ECMESSTC1_CLSSE047_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE047_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE046		(BIT14)
	#define		ECM_ECMESSTC1_CLSSE046_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE046_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE045		(BIT13)
	#define		ECM_ECMESSTC1_CLSSE045_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE045_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE044		(BIT12)
	#define		ECM_ECMESSTC1_CLSSE044_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE044_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE043		(BIT11)
	#define		ECM_ECMESSTC1_CLSSE043_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE043_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE042		(BIT10)
	#define		ECM_ECMESSTC1_CLSSE042_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE042_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE041		(BIT9)
	#define		ECM_ECMESSTC1_CLSSE041_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE041_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE040		(BIT8)
	#define		ECM_ECMESSTC1_CLSSE040_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE040_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE039		(BIT7)
	#define		ECM_ECMESSTC1_CLSSE039_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE039_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE038		(BIT6)
	#define		ECM_ECMESSTC1_CLSSE038_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE038_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE037		(BIT5)
	#define		ECM_ECMESSTC1_CLSSE037_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE037_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE036		(BIT4)
	#define		ECM_ECMESSTC1_CLSSE036_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE036_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE035		(BIT3)
	#define		ECM_ECMESSTC1_CLSSE035_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE035_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE034		(BIT2)
	#define		ECM_ECMESSTC1_CLSSE034_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE034_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE033		(BIT1)
	#define		ECM_ECMESSTC1_CLSSE033_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE033_CLR		(1)
#define		ECM_ECMESSTC1_CLSSE032		(BIT0)
	#define		ECM_ECMESSTC1_CLSSE032_NOCLR	(0)
	#define		ECM_ECMESSTC1_CLSSE032_CLR		(1)

/* ECMESSTC2 */
#define		ECM_ECMESSTC2_CLSSE095		(BIT31)
	#define		ECM_ECMESSTC2_CLSSE095_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE095_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE094		(BIT30)
	#define		ECM_ECMESSTC2_CLSSE094_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE094_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE093		(BIT29)
	#define		ECM_ECMESSTC2_CLSSE093_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE093_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE092		(BIT28)
	#define		ECM_ECMESSTC2_CLSSE092_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE092_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE091		(BIT27)
	#define		ECM_ECMESSTC2_CLSSE091_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE091_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE090		(BIT26)
	#define		ECM_ECMESSTC2_CLSSE090_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE090_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE089		(BIT25)
	#define		ECM_ECMESSTC2_CLSSE089_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE089_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE088		(BIT24)
	#define		ECM_ECMESSTC2_CLSSE088_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE088_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE087		(BIT23)
	#define		ECM_ECMESSTC2_CLSSE087_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE087_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE086		(BIT22)
	#define		ECM_ECMESSTC2_CLSSE086_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE086_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE085		(BIT21)
	#define		ECM_ECMESSTC2_CLSSE085_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE085_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE084		(BIT20)
	#define		ECM_ECMESSTC2_CLSSE084_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE084_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE083		(BIT19)
	#define		ECM_ECMESSTC2_CLSSE083_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE083_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE082		(BIT18)
	#define		ECM_ECMESSTC2_CLSSE082_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE082_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE081		(BIT17)
	#define		ECM_ECMESSTC2_CLSSE081_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE081_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE080		(BIT16)
	#define		ECM_ECMESSTC2_CLSSE080_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE080_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE079		(BIT15)
	#define		ECM_ECMESSTC2_CLSSE079_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE079_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE078		(BIT14)
	#define		ECM_ECMESSTC2_CLSSE078_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE078_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE077		(BIT13)
	#define		ECM_ECMESSTC2_CLSSE077_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE077_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE076		(BIT12)
	#define		ECM_ECMESSTC2_CLSSE076_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE076_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE075		(BIT11)
	#define		ECM_ECMESSTC2_CLSSE075_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE075_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE074		(BIT10)
	#define		ECM_ECMESSTC2_CLSSE074_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE074_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE073		(BIT9)
	#define		ECM_ECMESSTC2_CLSSE073_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE073_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE072		(BIT8)
	#define		ECM_ECMESSTC2_CLSSE072_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE072_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE071		(BIT7)
	#define		ECM_ECMESSTC2_CLSSE071_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE071_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE070		(BIT6)
	#define		ECM_ECMESSTC2_CLSSE070_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE070_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE069		(BIT5)
	#define		ECM_ECMESSTC2_CLSSE069_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE069_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE068		(BIT4)
	#define		ECM_ECMESSTC2_CLSSE068_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE068_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE067		(BIT3)
	#define		ECM_ECMESSTC2_CLSSE067_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE067_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE066		(BIT2)
	#define		ECM_ECMESSTC2_CLSSE066_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE066_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE065		(BIT1)
	#define		ECM_ECMESSTC2_CLSSE065_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE065_CLR		(1)
#define		ECM_ECMESSTC2_CLSSE064		(BIT0)
	#define		ECM_ECMESSTC2_CLSSE064_NOCLR	(0)
	#define		ECM_ECMESSTC2_CLSSE064_CLR		(1)

/* ECMESSTC3 */
#define		ECM_ECMESSTC3_CLSSE127		(BIT31)
	#define		ECM_ECMESSTC3_CLSSE127_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE127_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE126		(BIT30)
	#define		ECM_ECMESSTC3_CLSSE126_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE126_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE125		(BIT29)
	#define		ECM_ECMESSTC3_CLSSE125_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE125_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE124		(BIT28)
	#define		ECM_ECMESSTC3_CLSSE124_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE124_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE123		(BIT27)
	#define		ECM_ECMESSTC3_CLSSE123_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE123_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE122		(BIT26)
	#define		ECM_ECMESSTC3_CLSSE122_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE122_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE121		(BIT25)
	#define		ECM_ECMESSTC3_CLSSE121_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE121_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE120		(BIT24)
	#define		ECM_ECMESSTC3_CLSSE120_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE120_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE119		(BIT23)
	#define		ECM_ECMESSTC3_CLSSE119_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE119_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE118		(BIT22)
	#define		ECM_ECMESSTC3_CLSSE118_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE118_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE117		(BIT21)
	#define		ECM_ECMESSTC3_CLSSE117_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE117_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE116		(BIT20)
	#define		ECM_ECMESSTC3_CLSSE116_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE116_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE115		(BIT19)
	#define		ECM_ECMESSTC3_CLSSE115_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE115_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE114		(BIT18)
	#define		ECM_ECMESSTC3_CLSSE114_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE114_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE113		(BIT17)
	#define		ECM_ECMESSTC3_CLSSE113_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE113_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE112		(BIT16)
	#define		ECM_ECMESSTC3_CLSSE112_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE112_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE111		(BIT15)
	#define		ECM_ECMESSTC3_CLSSE111_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE111_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE110		(BIT14)
	#define		ECM_ECMESSTC3_CLSSE110_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE110_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE109		(BIT13)
	#define		ECM_ECMESSTC3_CLSSE109_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE109_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE108		(BIT12)
	#define		ECM_ECMESSTC3_CLSSE108_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE108_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE107		(BIT11)
	#define		ECM_ECMESSTC3_CLSSE107_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE107_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE106		(BIT10)
	#define		ECM_ECMESSTC3_CLSSE106_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE106_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE105		(BIT9)
	#define		ECM_ECMESSTC3_CLSSE105_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE105_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE104		(BIT8)
	#define		ECM_ECMESSTC3_CLSSE104_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE104_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE103		(BIT7)
	#define		ECM_ECMESSTC3_CLSSE103_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE103_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE102		(BIT6)
	#define		ECM_ECMESSTC3_CLSSE102_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE102_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE101		(BIT5)
	#define		ECM_ECMESSTC3_CLSSE101_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE101_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE100		(BIT4)
	#define		ECM_ECMESSTC3_CLSSE100_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE100_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE099		(BIT3)
	#define		ECM_ECMESSTC3_CLSSE099_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE099_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE098		(BIT2)
	#define		ECM_ECMESSTC3_CLSSE098_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE098_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE097		(BIT1)
	#define		ECM_ECMESSTC3_CLSSE097_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE097_CLR		(1)
#define		ECM_ECMESSTC3_CLSSE096		(BIT0)
	#define		ECM_ECMESSTC3_CLSSE096_NOCLR	(0)
	#define		ECM_ECMESSTC3_CLSSE096_CLR		(1)

/* ECMESSTC4 */
#define		ECM_ECMESSTC4_CLSSE159		(BIT31)
	#define		ECM_ECMESSTC4_CLSSE159_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE159_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE158		(BIT30)
	#define		ECM_ECMESSTC4_CLSSE158_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE158_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE157		(BIT29)
	#define		ECM_ECMESSTC4_CLSSE157_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE157_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE156		(BIT28)
	#define		ECM_ECMESSTC4_CLSSE156_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE156_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE155		(BIT27)
	#define		ECM_ECMESSTC4_CLSSE155_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE155_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE154		(BIT26)
	#define		ECM_ECMESSTC4_CLSSE154_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE154_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE153		(BIT25)
	#define		ECM_ECMESSTC4_CLSSE153_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE153_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE152		(BIT24)
	#define		ECM_ECMESSTC4_CLSSE152_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE152_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE151		(BIT23)
	#define		ECM_ECMESSTC4_CLSSE151_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE151_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE150		(BIT22)
	#define		ECM_ECMESSTC4_CLSSE150_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE150_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE149		(BIT21)
	#define		ECM_ECMESSTC4_CLSSE149_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE149_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE148		(BIT20)
	#define		ECM_ECMESSTC4_CLSSE148_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE148_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE147		(BIT19)
	#define		ECM_ECMESSTC4_CLSSE147_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE147_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE146		(BIT18)
	#define		ECM_ECMESSTC4_CLSSE146_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE146_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE145		(BIT17)
	#define		ECM_ECMESSTC4_CLSSE145_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE145_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE144		(BIT16)
	#define		ECM_ECMESSTC4_CLSSE144_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE144_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE143		(BIT15)
	#define		ECM_ECMESSTC4_CLSSE143_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE143_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE142		(BIT14)
	#define		ECM_ECMESSTC4_CLSSE142_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE142_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE141		(BIT13)
	#define		ECM_ECMESSTC4_CLSSE141_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE141_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE140		(BIT12)
	#define		ECM_ECMESSTC4_CLSSE140_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE140_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE139		(BIT11)
	#define		ECM_ECMESSTC4_CLSSE139_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE139_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE138		(BIT10)
	#define		ECM_ECMESSTC4_CLSSE138_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE138_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE137		(BIT9)
	#define		ECM_ECMESSTC4_CLSSE137_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE137_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE136		(BIT8)
	#define		ECM_ECMESSTC4_CLSSE136_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE136_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE135		(BIT7)
	#define		ECM_ECMESSTC4_CLSSE135_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE135_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE134		(BIT6)
	#define		ECM_ECMESSTC4_CLSSE134_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE134_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE133		(BIT5)
	#define		ECM_ECMESSTC4_CLSSE133_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE133_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE132		(BIT4)
	#define		ECM_ECMESSTC4_CLSSE132_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE132_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE131		(BIT3)
	#define		ECM_ECMESSTC4_CLSSE131_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE131_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE130		(BIT2)
	#define		ECM_ECMESSTC4_CLSSE130_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE130_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE129		(BIT1)
	#define		ECM_ECMESSTC4_CLSSE129_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE129_CLR		(1)
#define		ECM_ECMESSTC4_CLSSE128		(BIT0)
	#define		ECM_ECMESSTC4_CLSSE128_NOCLR	(0)
	#define		ECM_ECMESSTC4_CLSSE128_CLR		(1)

/* ECMESSTC5 */
#define		ECM_ECMESSTC5_CLSSE191		(BIT31)
	#define		ECM_ECMESSTC5_CLSSE191_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE191_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE190		(BIT30)
	#define		ECM_ECMESSTC5_CLSSE190_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE190_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE189		(BIT29)
	#define		ECM_ECMESSTC5_CLSSE189_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE189_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE188		(BIT28)
	#define		ECM_ECMESSTC5_CLSSE188_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE188_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE187		(BIT27)
	#define		ECM_ECMESSTC5_CLSSE187_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE187_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE186		(BIT26)
	#define		ECM_ECMESSTC5_CLSSE186_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE186_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE185		(BIT25)
	#define		ECM_ECMESSTC5_CLSSE185_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE185_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE184		(BIT24)
	#define		ECM_ECMESSTC5_CLSSE184_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE184_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE183		(BIT23)
	#define		ECM_ECMESSTC5_CLSSE183_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE183_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE182		(BIT22)
	#define		ECM_ECMESSTC5_CLSSE182_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE182_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE181		(BIT21)
	#define		ECM_ECMESSTC5_CLSSE181_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE181_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE180		(BIT20)
	#define		ECM_ECMESSTC5_CLSSE180_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE180_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE179		(BIT19)
	#define		ECM_ECMESSTC5_CLSSE179_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE179_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE178		(BIT18)
	#define		ECM_ECMESSTC5_CLSSE178_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE178_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE177		(BIT17)
	#define		ECM_ECMESSTC5_CLSSE177_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE177_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE176		(BIT16)
	#define		ECM_ECMESSTC5_CLSSE176_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE176_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE175		(BIT15)
	#define		ECM_ECMESSTC5_CLSSE175_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE175_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE174		(BIT14)
	#define		ECM_ECMESSTC5_CLSSE174_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE174_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE173		(BIT13)
	#define		ECM_ECMESSTC5_CLSSE173_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE173_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE172		(BIT12)
	#define		ECM_ECMESSTC5_CLSSE172_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE172_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE171		(BIT11)
	#define		ECM_ECMESSTC5_CLSSE171_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE171_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE170		(BIT10)
	#define		ECM_ECMESSTC5_CLSSE170_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE170_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE169		(BIT9)
	#define		ECM_ECMESSTC5_CLSSE169_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE169_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE168		(BIT8)
	#define		ECM_ECMESSTC5_CLSSE168_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE168_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE167		(BIT7)
	#define		ECM_ECMESSTC5_CLSSE167_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE167_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE166		(BIT6)
	#define		ECM_ECMESSTC5_CLSSE166_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE166_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE165		(BIT5)
	#define		ECM_ECMESSTC5_CLSSE165_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE165_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE164		(BIT4)
	#define		ECM_ECMESSTC5_CLSSE164_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE164_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE163		(BIT3)
	#define		ECM_ECMESSTC5_CLSSE163_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE163_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE162		(BIT2)
	#define		ECM_ECMESSTC5_CLSSE162_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE162_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE161		(BIT1)
	#define		ECM_ECMESSTC5_CLSSE161_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE161_CLR		(1)
#define		ECM_ECMESSTC5_CLSSE160		(BIT0)
	#define		ECM_ECMESSTC5_CLSSE160_NOCLR	(0)
	#define		ECM_ECMESSTC5_CLSSE160_CLR		(1)

/* ECMESSTC6 */
#define		ECM_ECMESSTC6_CLSSE223		(BIT31)
	#define		ECM_ECMESSTC6_CLSSE223_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE223_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE222		(BIT30)
	#define		ECM_ECMESSTC6_CLSSE222_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE222_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE221		(BIT29)
	#define		ECM_ECMESSTC6_CLSSE221_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE221_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE220		(BIT28)
	#define		ECM_ECMESSTC6_CLSSE220_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE220_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE219		(BIT27)
	#define		ECM_ECMESSTC6_CLSSE219_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE219_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE218		(BIT26)
	#define		ECM_ECMESSTC6_CLSSE218_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE218_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE217		(BIT25)
	#define		ECM_ECMESSTC6_CLSSE217_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE217_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE216		(BIT24)
	#define		ECM_ECMESSTC6_CLSSE216_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE216_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE215		(BIT23)
	#define		ECM_ECMESSTC6_CLSSE215_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE215_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE214		(BIT22)
	#define		ECM_ECMESSTC6_CLSSE214_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE214_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE213		(BIT21)
	#define		ECM_ECMESSTC6_CLSSE213_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE213_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE212		(BIT20)
	#define		ECM_ECMESSTC6_CLSSE212_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE212_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE211		(BIT19)
	#define		ECM_ECMESSTC6_CLSSE211_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE211_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE210		(BIT18)
	#define		ECM_ECMESSTC6_CLSSE210_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE210_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE209		(BIT17)
	#define		ECM_ECMESSTC6_CLSSE209_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE209_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE208		(BIT16)
	#define		ECM_ECMESSTC6_CLSSE208_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE208_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE207		(BIT15)
	#define		ECM_ECMESSTC6_CLSSE207_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE207_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE206		(BIT14)
	#define		ECM_ECMESSTC6_CLSSE206_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE206_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE205		(BIT13)
	#define		ECM_ECMESSTC6_CLSSE205_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE205_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE204		(BIT12)
	#define		ECM_ECMESSTC6_CLSSE204_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE204_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE203		(BIT11)
	#define		ECM_ECMESSTC6_CLSSE203_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE203_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE202		(BIT10)
	#define		ECM_ECMESSTC6_CLSSE202_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE202_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE201		(BIT9)
	#define		ECM_ECMESSTC6_CLSSE201_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE201_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE200		(BIT8)
	#define		ECM_ECMESSTC6_CLSSE200_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE200_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE199		(BIT7)
	#define		ECM_ECMESSTC6_CLSSE199_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE199_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE198		(BIT6)
	#define		ECM_ECMESSTC6_CLSSE198_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE198_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE197		(BIT5)
	#define		ECM_ECMESSTC6_CLSSE197_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE197_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE196		(BIT4)
	#define		ECM_ECMESSTC6_CLSSE196_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE196_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE195		(BIT3)
	#define		ECM_ECMESSTC6_CLSSE195_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE195_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE194		(BIT2)
	#define		ECM_ECMESSTC6_CLSSE194_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE194_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE193		(BIT1)
	#define		ECM_ECMESSTC6_CLSSE193_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE193_CLR		(1)
#define		ECM_ECMESSTC6_CLSSE192		(BIT0)
	#define		ECM_ECMESSTC6_CLSSE192_NOCLR	(0)
	#define		ECM_ECMESSTC6_CLSSE192_CLR		(1)

/* ECMESSTC7 */
#define		ECM_ECMESSTC7_CLSSE255		(BIT31)
	#define		ECM_ECMESSTC7_CLSSE255_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE255_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE254		(BIT30)
	#define		ECM_ECMESSTC7_CLSSE254_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE254_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE253		(BIT29)
	#define		ECM_ECMESSTC7_CLSSE253_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE253_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE252		(BIT28)
	#define		ECM_ECMESSTC7_CLSSE252_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE252_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE251		(BIT27)
	#define		ECM_ECMESSTC7_CLSSE251_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE251_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE250		(BIT26)
	#define		ECM_ECMESSTC7_CLSSE250_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE250_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE249		(BIT25)
	#define		ECM_ECMESSTC7_CLSSE249_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE249_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE248		(BIT24)
	#define		ECM_ECMESSTC7_CLSSE248_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE248_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE247		(BIT23)
	#define		ECM_ECMESSTC7_CLSSE247_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE247_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE246		(BIT22)
	#define		ECM_ECMESSTC7_CLSSE246_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE246_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE245		(BIT21)
	#define		ECM_ECMESSTC7_CLSSE245_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE245_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE244		(BIT20)
	#define		ECM_ECMESSTC7_CLSSE244_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE244_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE243		(BIT19)
	#define		ECM_ECMESSTC7_CLSSE243_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE243_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE242		(BIT18)
	#define		ECM_ECMESSTC7_CLSSE242_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE242_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE241		(BIT17)
	#define		ECM_ECMESSTC7_CLSSE241_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE241_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE240		(BIT16)
	#define		ECM_ECMESSTC7_CLSSE240_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE240_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE239		(BIT15)
	#define		ECM_ECMESSTC7_CLSSE239_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE239_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE238		(BIT14)
	#define		ECM_ECMESSTC7_CLSSE238_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE238_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE237		(BIT13)
	#define		ECM_ECMESSTC7_CLSSE237_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE237_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE236		(BIT12)
	#define		ECM_ECMESSTC7_CLSSE236_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE236_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE235		(BIT11)
	#define		ECM_ECMESSTC7_CLSSE235_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE235_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE234		(BIT10)
	#define		ECM_ECMESSTC7_CLSSE234_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE234_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE233		(BIT9)
	#define		ECM_ECMESSTC7_CLSSE233_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE233_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE232		(BIT8)
	#define		ECM_ECMESSTC7_CLSSE232_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE232_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE231		(BIT7)
	#define		ECM_ECMESSTC7_CLSSE231_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE231_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE230		(BIT6)
	#define		ECM_ECMESSTC7_CLSSE230_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE230_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE229		(BIT5)
	#define		ECM_ECMESSTC7_CLSSE229_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE229_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE228		(BIT4)
	#define		ECM_ECMESSTC7_CLSSE228_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE228_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE227		(BIT3)
	#define		ECM_ECMESSTC7_CLSSE227_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE227_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE226		(BIT2)
	#define		ECM_ECMESSTC7_CLSSE226_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE226_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE225		(BIT1)
	#define		ECM_ECMESSTC7_CLSSE225_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE225_CLR		(1)
#define		ECM_ECMESSTC7_CLSSE224		(BIT0)
	#define		ECM_ECMESSTC7_CLSSE224_NOCLR	(0)
	#define		ECM_ECMESSTC7_CLSSE224_CLR		(1)

/* ECMESSTC8 */
#define		ECM_ECMESSTC8_CLSSE287		(BIT31)
	#define		ECM_ECMESSTC8_CLSSE287_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE287_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE286		(BIT30)
	#define		ECM_ECMESSTC8_CLSSE286_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE286_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE285		(BIT29)
	#define		ECM_ECMESSTC8_CLSSE285_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE285_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE284		(BIT28)
	#define		ECM_ECMESSTC8_CLSSE284_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE284_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE283		(BIT27)
	#define		ECM_ECMESSTC8_CLSSE283_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE283_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE282		(BIT26)
	#define		ECM_ECMESSTC8_CLSSE282_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE282_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE281		(BIT25)
	#define		ECM_ECMESSTC8_CLSSE281_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE281_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE280		(BIT24)
	#define		ECM_ECMESSTC8_CLSSE280_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE280_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE279		(BIT23)
	#define		ECM_ECMESSTC8_CLSSE279_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE279_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE278		(BIT22)
	#define		ECM_ECMESSTC8_CLSSE278_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE278_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE277		(BIT21)
	#define		ECM_ECMESSTC8_CLSSE277_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE277_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE276		(BIT20)
	#define		ECM_ECMESSTC8_CLSSE276_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE276_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE275		(BIT19)
	#define		ECM_ECMESSTC8_CLSSE275_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE275_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE274		(BIT18)
	#define		ECM_ECMESSTC8_CLSSE274_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE274_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE273		(BIT17)
	#define		ECM_ECMESSTC8_CLSSE273_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE273_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE272		(BIT16)
	#define		ECM_ECMESSTC8_CLSSE272_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE272_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE271		(BIT15)
	#define		ECM_ECMESSTC8_CLSSE271_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE271_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE270		(BIT14)
	#define		ECM_ECMESSTC8_CLSSE270_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE270_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE269		(BIT13)
	#define		ECM_ECMESSTC8_CLSSE269_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE269_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE268		(BIT12)
	#define		ECM_ECMESSTC8_CLSSE268_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE268_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE267		(BIT11)
	#define		ECM_ECMESSTC8_CLSSE267_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE267_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE266		(BIT10)
	#define		ECM_ECMESSTC8_CLSSE266_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE266_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE265		(BIT9)
	#define		ECM_ECMESSTC8_CLSSE265_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE265_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE264		(BIT8)
	#define		ECM_ECMESSTC8_CLSSE264_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE264_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE263		(BIT7)
	#define		ECM_ECMESSTC8_CLSSE263_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE263_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE262		(BIT6)
	#define		ECM_ECMESSTC8_CLSSE262_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE262_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE261		(BIT5)
	#define		ECM_ECMESSTC8_CLSSE261_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE261_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE260		(BIT4)
	#define		ECM_ECMESSTC8_CLSSE260_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE260_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE259		(BIT3)
	#define		ECM_ECMESSTC8_CLSSE259_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE259_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE258		(BIT2)
	#define		ECM_ECMESSTC8_CLSSE258_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE258_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE257		(BIT1)
	#define		ECM_ECMESSTC8_CLSSE257_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE257_CLR		(1)
#define		ECM_ECMESSTC8_CLSSE256		(BIT0)
	#define		ECM_ECMESSTC8_CLSSE256_NOCLR	(0)
	#define		ECM_ECMESSTC8_CLSSE256_CLR		(1)

/* ECMESSTC9 */
#define		ECM_ECMESSTC9_CLSSE319		(BIT31)
	#define		ECM_ECMESSTC9_CLSSE319_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE319_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE318		(BIT30)
	#define		ECM_ECMESSTC9_CLSSE318_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE318_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE317		(BIT29)
	#define		ECM_ECMESSTC9_CLSSE317_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE317_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE316		(BIT28)
	#define		ECM_ECMESSTC9_CLSSE316_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE316_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE315		(BIT27)
	#define		ECM_ECMESSTC9_CLSSE315_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE315_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE314		(BIT26)
	#define		ECM_ECMESSTC9_CLSSE314_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE314_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE313		(BIT25)
	#define		ECM_ECMESSTC9_CLSSE313_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE313_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE312		(BIT24)
	#define		ECM_ECMESSTC9_CLSSE312_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE312_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE311		(BIT23)
	#define		ECM_ECMESSTC9_CLSSE311_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE311_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE310		(BIT22)
	#define		ECM_ECMESSTC9_CLSSE310_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE310_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE309		(BIT21)
	#define		ECM_ECMESSTC9_CLSSE309_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE309_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE308		(BIT20)
	#define		ECM_ECMESSTC9_CLSSE308_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE308_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE307		(BIT19)
	#define		ECM_ECMESSTC9_CLSSE307_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE307_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE306		(BIT18)
	#define		ECM_ECMESSTC9_CLSSE306_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE306_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE305		(BIT17)
	#define		ECM_ECMESSTC9_CLSSE305_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE305_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE304		(BIT16)
	#define		ECM_ECMESSTC9_CLSSE304_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE304_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE303		(BIT15)
	#define		ECM_ECMESSTC9_CLSSE303_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE303_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE302		(BIT14)
	#define		ECM_ECMESSTC9_CLSSE302_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE302_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE301		(BIT13)
	#define		ECM_ECMESSTC9_CLSSE301_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE301_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE300		(BIT12)
	#define		ECM_ECMESSTC9_CLSSE300_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE300_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE299		(BIT11)
	#define		ECM_ECMESSTC9_CLSSE299_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE299_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE298		(BIT10)
	#define		ECM_ECMESSTC9_CLSSE298_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE298_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE297		(BIT9)
	#define		ECM_ECMESSTC9_CLSSE297_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE297_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE296		(BIT8)
	#define		ECM_ECMESSTC9_CLSSE296_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE296_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE295		(BIT7)
	#define		ECM_ECMESSTC9_CLSSE295_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE295_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE294		(BIT6)
	#define		ECM_ECMESSTC9_CLSSE294_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE294_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE293		(BIT5)
	#define		ECM_ECMESSTC9_CLSSE293_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE293_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE292		(BIT4)
	#define		ECM_ECMESSTC9_CLSSE292_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE292_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE291		(BIT3)
	#define		ECM_ECMESSTC9_CLSSE291_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE291_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE290		(BIT2)
	#define		ECM_ECMESSTC9_CLSSE290_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE290_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE289		(BIT1)
	#define		ECM_ECMESSTC9_CLSSE289_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE289_CLR		(1)
#define		ECM_ECMESSTC9_CLSSE288		(BIT0)
	#define		ECM_ECMESSTC9_CLSSE288_NOCLR	(0)
	#define		ECM_ECMESSTC9_CLSSE288_CLR		(1)

/* ECMESSTC10 */
#define		ECM_ECMESSTC10_CLSSE351		(BIT31)
	#define		ECM_ECMESSTC10_CLSSE351_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE351_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE350		(BIT30)
	#define		ECM_ECMESSTC10_CLSSE350_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE350_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE349		(BIT29)
	#define		ECM_ECMESSTC10_CLSSE349_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE349_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE348		(BIT28)
	#define		ECM_ECMESSTC10_CLSSE348_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE348_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE347		(BIT27)
	#define		ECM_ECMESSTC10_CLSSE347_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE347_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE346		(BIT26)
	#define		ECM_ECMESSTC10_CLSSE346_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE346_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE345		(BIT25)
	#define		ECM_ECMESSTC10_CLSSE345_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE345_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE344		(BIT24)
	#define		ECM_ECMESSTC10_CLSSE344_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE344_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE343		(BIT23)
	#define		ECM_ECMESSTC10_CLSSE343_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE343_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE342		(BIT22)
	#define		ECM_ECMESSTC10_CLSSE342_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE342_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE341		(BIT21)
	#define		ECM_ECMESSTC10_CLSSE341_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE341_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE340		(BIT20)
	#define		ECM_ECMESSTC10_CLSSE340_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE340_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE339		(BIT19)
	#define		ECM_ECMESSTC10_CLSSE339_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE339_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE338		(BIT18)
	#define		ECM_ECMESSTC10_CLSSE338_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE338_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE337		(BIT17)
	#define		ECM_ECMESSTC10_CLSSE337_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE337_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE336		(BIT16)
	#define		ECM_ECMESSTC10_CLSSE336_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE336_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE335		(BIT15)
	#define		ECM_ECMESSTC10_CLSSE335_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE335_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE334		(BIT14)
	#define		ECM_ECMESSTC10_CLSSE334_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE334_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE333		(BIT13)
	#define		ECM_ECMESSTC10_CLSSE333_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE333_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE332		(BIT12)
	#define		ECM_ECMESSTC10_CLSSE332_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE332_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE331		(BIT11)
	#define		ECM_ECMESSTC10_CLSSE331_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE331_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE330		(BIT10)
	#define		ECM_ECMESSTC10_CLSSE330_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE330_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE329		(BIT9)
	#define		ECM_ECMESSTC10_CLSSE329_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE329_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE328		(BIT8)
	#define		ECM_ECMESSTC10_CLSSE328_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE328_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE327		(BIT7)
	#define		ECM_ECMESSTC10_CLSSE327_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE327_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE326		(BIT6)
	#define		ECM_ECMESSTC10_CLSSE326_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE326_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE325		(BIT5)
	#define		ECM_ECMESSTC10_CLSSE325_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE325_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE324		(BIT4)
	#define		ECM_ECMESSTC10_CLSSE324_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE324_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE323		(BIT3)
	#define		ECM_ECMESSTC10_CLSSE323_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE323_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE322		(BIT2)
	#define		ECM_ECMESSTC10_CLSSE322_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE322_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE321		(BIT1)
	#define		ECM_ECMESSTC10_CLSSE321_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE321_CLR		(1)
#define		ECM_ECMESSTC10_CLSSE320		(BIT0)
	#define		ECM_ECMESSTC10_CLSSE320_NOCLR	(0)
	#define		ECM_ECMESSTC10_CLSSE320_CLR		(1)

/* ECMKCPROT */
#define		ECM_ECMKCPROT_KCPROT				(BIT31 + BIT30 + BIT29 + BIT28 + BIT27 + BIT26 + BIT25 + BIT24 + BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1)
#define		ECM_ECMKCPROT_KCE					(BIT0)
	#define		ECM_ECMKCPROT_KCE_DISABLE		(0xA5A5A500U)
	#define		ECM_ECMKCPROT_KCE_ENABLE		(0xA5A5A501U)

/* ECMPE0 */
#define		ECM_ECMPE0_PE031		(BIT31)
	#define		ECM_ECMPE0_PE031_NOERROR	(0)
	#define		ECM_ECMPE0_PE031_ERROR		(1)
#define		ECM_ECMPE0_PE030		(BIT30)
	#define		ECM_ECMPE0_PE030_NOERROR	(0)
	#define		ECM_ECMPE0_PE030_ERROR		(1)
#define		ECM_ECMPE0_PE029		(BIT29)
	#define		ECM_ECMPE0_PE029_NOERROR	(0)
	#define		ECM_ECMPE0_PE029_ERROR		(1)
#define		ECM_ECMPE0_PE028		(BIT28)
	#define		ECM_ECMPE0_PE028_NOERROR	(0)
	#define		ECM_ECMPE0_PE028_ERROR		(1)
#define		ECM_ECMPE0_PE027		(BIT27)
	#define		ECM_ECMPE0_PE027_NOERROR	(0)
	#define		ECM_ECMPE0_PE027_ERROR		(1)
#define		ECM_ECMPE0_PE026		(BIT26)
	#define		ECM_ECMPE0_PE026_NOERROR	(0)
	#define		ECM_ECMPE0_PE026_ERROR		(1)
#define		ECM_ECMPE0_PE025		(BIT25)
	#define		ECM_ECMPE0_PE025_NOERROR	(0)
	#define		ECM_ECMPE0_PE025_ERROR		(1)
#define		ECM_ECMPE0_PE024		(BIT24)
	#define		ECM_ECMPE0_PE024_NOERROR	(0)
	#define		ECM_ECMPE0_PE024_ERROR		(1)
#define		ECM_ECMPE0_PE023		(BIT23)
	#define		ECM_ECMPE0_PE023_NOERROR	(0)
	#define		ECM_ECMPE0_PE023_ERROR		(1)
#define		ECM_ECMPE0_PE022		(BIT22)
	#define		ECM_ECMPE0_PE022_NOERROR	(0)
	#define		ECM_ECMPE0_PE022_ERROR		(1)
#define		ECM_ECMPE0_PE021		(BIT21)
	#define		ECM_ECMPE0_PE021_NOERROR	(0)
	#define		ECM_ECMPE0_PE021_ERROR		(1)
#define		ECM_ECMPE0_PE020		(BIT20)
	#define		ECM_ECMPE0_PE020_NOERROR	(0)
	#define		ECM_ECMPE0_PE020_ERROR		(1)
#define		ECM_ECMPE0_PE019		(BIT19)
	#define		ECM_ECMPE0_PE019_NOERROR	(0)
	#define		ECM_ECMPE0_PE019_ERROR		(1)
#define		ECM_ECMPE0_PE018		(BIT18)
	#define		ECM_ECMPE0_PE018_NOERROR	(0)
	#define		ECM_ECMPE0_PE018_ERROR		(1)
#define		ECM_ECMPE0_PE017		(BIT17)
	#define		ECM_ECMPE0_PE017_NOERROR	(0)
	#define		ECM_ECMPE0_PE017_ERROR		(1)
#define		ECM_ECMPE0_PE016		(BIT16)
	#define		ECM_ECMPE0_PE016_NOERROR	(0)
	#define		ECM_ECMPE0_PE016_ERROR		(1)
#define		ECM_ECMPE0_PE015		(BIT15)
	#define		ECM_ECMPE0_PE015_NOERROR	(0)
	#define		ECM_ECMPE0_PE015_ERROR		(1)
#define		ECM_ECMPE0_PE014		(BIT14)
	#define		ECM_ECMPE0_PE014_NOERROR	(0)
	#define		ECM_ECMPE0_PE014_ERROR		(1)
#define		ECM_ECMPE0_PE013		(BIT13)
	#define		ECM_ECMPE0_PE013_NOERROR	(0)
	#define		ECM_ECMPE0_PE013_ERROR		(1)
#define		ECM_ECMPE0_PE012		(BIT12)
	#define		ECM_ECMPE0_PE012_NOERROR	(0)
	#define		ECM_ECMPE0_PE012_ERROR		(1)
#define		ECM_ECMPE0_PE011		(BIT11)
	#define		ECM_ECMPE0_PE011_NOERROR	(0)
	#define		ECM_ECMPE0_PE011_ERROR		(1)
#define		ECM_ECMPE0_PE010		(BIT10)
	#define		ECM_ECMPE0_PE010_NOERROR	(0)
	#define		ECM_ECMPE0_PE010_ERROR		(1)
#define		ECM_ECMPE0_PE009		(BIT9)
	#define		ECM_ECMPE0_PE009_NOERROR	(0)
	#define		ECM_ECMPE0_PE009_ERROR		(1)
#define		ECM_ECMPE0_PE008		(BIT8)
	#define		ECM_ECMPE0_PE008_NOERROR	(0)
	#define		ECM_ECMPE0_PE008_ERROR		(1)
#define		ECM_ECMPE0_PE007		(BIT7)
	#define		ECM_ECMPE0_PE007_NOERROR	(0)
	#define		ECM_ECMPE0_PE007_ERROR		(1)
#define		ECM_ECMPE0_PE006		(BIT6)
	#define		ECM_ECMPE0_PE006_NOERROR	(0)
	#define		ECM_ECMPE0_PE006_ERROR		(1)
#define		ECM_ECMPE0_PE005		(BIT5)
	#define		ECM_ECMPE0_PE005_NOERROR	(0)
	#define		ECM_ECMPE0_PE005_ERROR		(1)
#define		ECM_ECMPE0_PE004		(BIT4)
	#define		ECM_ECMPE0_PE004_NOERROR	(0)
	#define		ECM_ECMPE0_PE004_ERROR		(1)
#define		ECM_ECMPE0_PE003		(BIT3)
	#define		ECM_ECMPE0_PE003_NOERROR	(0)
	#define		ECM_ECMPE0_PE003_ERROR		(1)
#define		ECM_ECMPE0_PE002		(BIT2)
	#define		ECM_ECMPE0_PE002_NOERROR	(0)
	#define		ECM_ECMPE0_PE002_ERROR		(1)
#define		ECM_ECMPE0_PE001		(BIT1)
	#define		ECM_ECMPE0_PE001_NOERROR	(0)
	#define		ECM_ECMPE0_PE001_ERROR		(1)
#define		ECM_ECMPE0_PE000		(BIT0)
	#define		ECM_ECMPE0_PE000_NOERROR	(0)
	#define		ECM_ECMPE0_PE000_ERROR		(1)

/* ECMPE1 */
#define		ECM_ECMPE1_PE063		(BIT31)
	#define		ECM_ECMPE1_PE063_NOERROR	(0)
	#define		ECM_ECMPE1_PE063_ERROR		(1)
#define		ECM_ECMPE1_PE062		(BIT30)
	#define		ECM_ECMPE1_PE062_NOERROR	(0)
	#define		ECM_ECMPE1_PE062_ERROR		(1)
#define		ECM_ECMPE1_PE061		(BIT29)
	#define		ECM_ECMPE1_PE061_NOERROR	(0)
	#define		ECM_ECMPE1_PE061_ERROR		(1)
#define		ECM_ECMPE1_PE060		(BIT28)
	#define		ECM_ECMPE1_PE060_NOERROR	(0)
	#define		ECM_ECMPE1_PE060_ERROR		(1)
#define		ECM_ECMPE1_PE059		(BIT27)
	#define		ECM_ECMPE1_PE059_NOERROR	(0)
	#define		ECM_ECMPE1_PE059_ERROR		(1)
#define		ECM_ECMPE1_PE058		(BIT26)
	#define		ECM_ECMPE1_PE058_NOERROR	(0)
	#define		ECM_ECMPE1_PE058_ERROR		(1)
#define		ECM_ECMPE1_PE057		(BIT25)
	#define		ECM_ECMPE1_PE057_NOERROR	(0)
	#define		ECM_ECMPE1_PE057_ERROR		(1)
#define		ECM_ECMPE1_PE056		(BIT24)
	#define		ECM_ECMPE1_PE056_NOERROR	(0)
	#define		ECM_ECMPE1_PE056_ERROR		(1)
#define		ECM_ECMPE1_PE055		(BIT23)
	#define		ECM_ECMPE1_PE055_NOERROR	(0)
	#define		ECM_ECMPE1_PE055_ERROR		(1)
#define		ECM_ECMPE1_PE054		(BIT22)
	#define		ECM_ECMPE1_PE054_NOERROR	(0)
	#define		ECM_ECMPE1_PE054_ERROR		(1)
#define		ECM_ECMPE1_PE053		(BIT21)
	#define		ECM_ECMPE1_PE053_NOERROR	(0)
	#define		ECM_ECMPE1_PE053_ERROR		(1)
#define		ECM_ECMPE1_PE052		(BIT20)
	#define		ECM_ECMPE1_PE052_NOERROR	(0)
	#define		ECM_ECMPE1_PE052_ERROR		(1)
#define		ECM_ECMPE1_PE051		(BIT19)
	#define		ECM_ECMPE1_PE051_NOERROR	(0)
	#define		ECM_ECMPE1_PE051_ERROR		(1)
#define		ECM_ECMPE1_PE050		(BIT18)
	#define		ECM_ECMPE1_PE050_NOERROR	(0)
	#define		ECM_ECMPE1_PE050_ERROR		(1)
#define		ECM_ECMPE1_PE049		(BIT17)
	#define		ECM_ECMPE1_PE049_NOERROR	(0)
	#define		ECM_ECMPE1_PE049_ERROR		(1)
#define		ECM_ECMPE1_PE048		(BIT16)
	#define		ECM_ECMPE1_PE048_NOERROR	(0)
	#define		ECM_ECMPE1_PE048_ERROR		(1)
#define		ECM_ECMPE1_PE047		(BIT15)
	#define		ECM_ECMPE1_PE047_NOERROR	(0)
	#define		ECM_ECMPE1_PE047_ERROR		(1)
#define		ECM_ECMPE1_PE046		(BIT14)
	#define		ECM_ECMPE1_PE046_NOERROR	(0)
	#define		ECM_ECMPE1_PE046_ERROR		(1)
#define		ECM_ECMPE1_PE045		(BIT13)
	#define		ECM_ECMPE1_PE045_NOERROR	(0)
	#define		ECM_ECMPE1_PE045_ERROR		(1)
#define		ECM_ECMPE1_PE044		(BIT12)
	#define		ECM_ECMPE1_PE044_NOERROR	(0)
	#define		ECM_ECMPE1_PE044_ERROR		(1)
#define		ECM_ECMPE1_PE043		(BIT11)
	#define		ECM_ECMPE1_PE043_NOERROR	(0)
	#define		ECM_ECMPE1_PE043_ERROR		(1)
#define		ECM_ECMPE1_PE042		(BIT10)
	#define		ECM_ECMPE1_PE042_NOERROR	(0)
	#define		ECM_ECMPE1_PE042_ERROR		(1)
#define		ECM_ECMPE1_PE041		(BIT9)
	#define		ECM_ECMPE1_PE041_NOERROR	(0)
	#define		ECM_ECMPE1_PE041_ERROR		(1)
#define		ECM_ECMPE1_PE040		(BIT8)
	#define		ECM_ECMPE1_PE040_NOERROR	(0)
	#define		ECM_ECMPE1_PE040_ERROR		(1)
#define		ECM_ECMPE1_PE039		(BIT7)
	#define		ECM_ECMPE1_PE039_NOERROR	(0)
	#define		ECM_ECMPE1_PE039_ERROR		(1)
#define		ECM_ECMPE1_PE038		(BIT6)
	#define		ECM_ECMPE1_PE038_NOERROR	(0)
	#define		ECM_ECMPE1_PE038_ERROR		(1)
#define		ECM_ECMPE1_PE037		(BIT5)
	#define		ECM_ECMPE1_PE037_NOERROR	(0)
	#define		ECM_ECMPE1_PE037_ERROR		(1)
#define		ECM_ECMPE1_PE036		(BIT4)
	#define		ECM_ECMPE1_PE036_NOERROR	(0)
	#define		ECM_ECMPE1_PE036_ERROR		(1)
#define		ECM_ECMPE1_PE035		(BIT3)
	#define		ECM_ECMPE1_PE035_NOERROR	(0)
	#define		ECM_ECMPE1_PE035_ERROR		(1)
#define		ECM_ECMPE1_PE034		(BIT2)
	#define		ECM_ECMPE1_PE034_NOERROR	(0)
	#define		ECM_ECMPE1_PE034_ERROR		(1)
#define		ECM_ECMPE1_PE033		(BIT1)
	#define		ECM_ECMPE1_PE033_NOERROR	(0)
	#define		ECM_ECMPE1_PE033_ERROR		(1)
#define		ECM_ECMPE1_PE032		(BIT0)
	#define		ECM_ECMPE1_PE032_NOERROR	(0)
	#define		ECM_ECMPE1_PE032_ERROR		(1)

/* ECMPE2 */
#define		ECM_ECMPE2_PE095		(BIT31)
	#define		ECM_ECMPE2_PE095_NOERROR	(0)
	#define		ECM_ECMPE2_PE095_ERROR		(1)
#define		ECM_ECMPE2_PE094		(BIT30)
	#define		ECM_ECMPE2_PE094_NOERROR	(0)
	#define		ECM_ECMPE2_PE094_ERROR		(1)
#define		ECM_ECMPE2_PE093		(BIT29)
	#define		ECM_ECMPE2_PE093_NOERROR	(0)
	#define		ECM_ECMPE2_PE093_ERROR		(1)
#define		ECM_ECMPE2_PE092		(BIT28)
	#define		ECM_ECMPE2_PE092_NOERROR	(0)
	#define		ECM_ECMPE2_PE092_ERROR		(1)
#define		ECM_ECMPE2_PE091		(BIT27)
	#define		ECM_ECMPE2_PE091_NOERROR	(0)
	#define		ECM_ECMPE2_PE091_ERROR		(1)
#define		ECM_ECMPE2_PE090		(BIT26)
	#define		ECM_ECMPE2_PE090_NOERROR	(0)
	#define		ECM_ECMPE2_PE090_ERROR		(1)
#define		ECM_ECMPE2_PE089		(BIT25)
	#define		ECM_ECMPE2_PE089_NOERROR	(0)
	#define		ECM_ECMPE2_PE089_ERROR		(1)
#define		ECM_ECMPE2_PE088		(BIT24)
	#define		ECM_ECMPE2_PE088_NOERROR	(0)
	#define		ECM_ECMPE2_PE088_ERROR		(1)
#define		ECM_ECMPE2_PE087		(BIT23)
	#define		ECM_ECMPE2_PE087_NOERROR	(0)
	#define		ECM_ECMPE2_PE087_ERROR		(1)
#define		ECM_ECMPE2_PE086		(BIT22)
	#define		ECM_ECMPE2_PE086_NOERROR	(0)
	#define		ECM_ECMPE2_PE086_ERROR		(1)
#define		ECM_ECMPE2_PE085		(BIT21)
	#define		ECM_ECMPE2_PE085_NOERROR	(0)
	#define		ECM_ECMPE2_PE085_ERROR		(1)
#define		ECM_ECMPE2_PE084		(BIT20)
	#define		ECM_ECMPE2_PE084_NOERROR	(0)
	#define		ECM_ECMPE2_PE084_ERROR		(1)
#define		ECM_ECMPE2_PE083		(BIT19)
	#define		ECM_ECMPE2_PE083_NOERROR	(0)
	#define		ECM_ECMPE2_PE083_ERROR		(1)
#define		ECM_ECMPE2_PE082		(BIT18)
	#define		ECM_ECMPE2_PE082_NOERROR	(0)
	#define		ECM_ECMPE2_PE082_ERROR		(1)
#define		ECM_ECMPE2_PE081		(BIT17)
	#define		ECM_ECMPE2_PE081_NOERROR	(0)
	#define		ECM_ECMPE2_PE081_ERROR		(1)
#define		ECM_ECMPE2_PE080		(BIT16)
	#define		ECM_ECMPE2_PE080_NOERROR	(0)
	#define		ECM_ECMPE2_PE080_ERROR		(1)
#define		ECM_ECMPE2_PE079		(BIT15)
	#define		ECM_ECMPE2_PE079_NOERROR	(0)
	#define		ECM_ECMPE2_PE079_ERROR		(1)
#define		ECM_ECMPE2_PE078		(BIT14)
	#define		ECM_ECMPE2_PE078_NOERROR	(0)
	#define		ECM_ECMPE2_PE078_ERROR		(1)
#define		ECM_ECMPE2_PE077		(BIT13)
	#define		ECM_ECMPE2_PE077_NOERROR	(0)
	#define		ECM_ECMPE2_PE077_ERROR		(1)
#define		ECM_ECMPE2_PE076		(BIT12)
	#define		ECM_ECMPE2_PE076_NOERROR	(0)
	#define		ECM_ECMPE2_PE076_ERROR		(1)
#define		ECM_ECMPE2_PE075		(BIT11)
	#define		ECM_ECMPE2_PE075_NOERROR	(0)
	#define		ECM_ECMPE2_PE075_ERROR		(1)
#define		ECM_ECMPE2_PE074		(BIT10)
	#define		ECM_ECMPE2_PE074_NOERROR	(0)
	#define		ECM_ECMPE2_PE074_ERROR		(1)
#define		ECM_ECMPE2_PE073		(BIT9)
	#define		ECM_ECMPE2_PE073_NOERROR	(0)
	#define		ECM_ECMPE2_PE073_ERROR		(1)
#define		ECM_ECMPE2_PE072		(BIT8)
	#define		ECM_ECMPE2_PE072_NOERROR	(0)
	#define		ECM_ECMPE2_PE072_ERROR		(1)
#define		ECM_ECMPE2_PE071		(BIT7)
	#define		ECM_ECMPE2_PE071_NOERROR	(0)
	#define		ECM_ECMPE2_PE071_ERROR		(1)
#define		ECM_ECMPE2_PE070		(BIT6)
	#define		ECM_ECMPE2_PE070_NOERROR	(0)
	#define		ECM_ECMPE2_PE070_ERROR		(1)
#define		ECM_ECMPE2_PE069		(BIT5)
	#define		ECM_ECMPE2_PE069_NOERROR	(0)
	#define		ECM_ECMPE2_PE069_ERROR		(1)
#define		ECM_ECMPE2_PE068		(BIT4)
	#define		ECM_ECMPE2_PE068_NOERROR	(0)
	#define		ECM_ECMPE2_PE068_ERROR		(1)
#define		ECM_ECMPE2_PE067		(BIT3)
	#define		ECM_ECMPE2_PE067_NOERROR	(0)
	#define		ECM_ECMPE2_PE067_ERROR		(1)
#define		ECM_ECMPE2_PE066		(BIT2)
	#define		ECM_ECMPE2_PE066_NOERROR	(0)
	#define		ECM_ECMPE2_PE066_ERROR		(1)
#define		ECM_ECMPE2_PE065		(BIT1)
	#define		ECM_ECMPE2_PE065_NOERROR	(0)
	#define		ECM_ECMPE2_PE065_ERROR		(1)
#define		ECM_ECMPE2_PE064		(BIT0)
	#define		ECM_ECMPE2_PE064_NOERROR	(0)
	#define		ECM_ECMPE2_PE064_ERROR		(1)

/* ECMPE3 */
#define		ECM_ECMPE3_PE127		(BIT31)
	#define		ECM_ECMPE3_PE127_NOERROR	(0)
	#define		ECM_ECMPE3_PE127_ERROR		(1)
#define		ECM_ECMPE3_PE126		(BIT30)
	#define		ECM_ECMPE3_PE126_NOERROR	(0)
	#define		ECM_ECMPE3_PE126_ERROR		(1)
#define		ECM_ECMPE3_PE125		(BIT29)
	#define		ECM_ECMPE3_PE125_NOERROR	(0)
	#define		ECM_ECMPE3_PE125_ERROR		(1)
#define		ECM_ECMPE3_PE124		(BIT28)
	#define		ECM_ECMPE3_PE124_NOERROR	(0)
	#define		ECM_ECMPE3_PE124_ERROR		(1)
#define		ECM_ECMPE3_PE123		(BIT27)
	#define		ECM_ECMPE3_PE123_NOERROR	(0)
	#define		ECM_ECMPE3_PE123_ERROR		(1)
#define		ECM_ECMPE3_PE122		(BIT26)
	#define		ECM_ECMPE3_PE122_NOERROR	(0)
	#define		ECM_ECMPE3_PE122_ERROR		(1)
#define		ECM_ECMPE3_PE121		(BIT25)
	#define		ECM_ECMPE3_PE121_NOERROR	(0)
	#define		ECM_ECMPE3_PE121_ERROR		(1)
#define		ECM_ECMPE3_PE120		(BIT24)
	#define		ECM_ECMPE3_PE120_NOERROR	(0)
	#define		ECM_ECMPE3_PE120_ERROR		(1)
#define		ECM_ECMPE3_PE119		(BIT23)
	#define		ECM_ECMPE3_PE119_NOERROR	(0)
	#define		ECM_ECMPE3_PE119_ERROR		(1)
#define		ECM_ECMPE3_PE118		(BIT22)
	#define		ECM_ECMPE3_PE118_NOERROR	(0)
	#define		ECM_ECMPE3_PE118_ERROR		(1)
#define		ECM_ECMPE3_PE117		(BIT21)
	#define		ECM_ECMPE3_PE117_NOERROR	(0)
	#define		ECM_ECMPE3_PE117_ERROR		(1)
#define		ECM_ECMPE3_PE116		(BIT20)
	#define		ECM_ECMPE3_PE116_NOERROR	(0)
	#define		ECM_ECMPE3_PE116_ERROR		(1)
#define		ECM_ECMPE3_PE115		(BIT19)
	#define		ECM_ECMPE3_PE115_NOERROR	(0)
	#define		ECM_ECMPE3_PE115_ERROR		(1)
#define		ECM_ECMPE3_PE114		(BIT18)
	#define		ECM_ECMPE3_PE114_NOERROR	(0)
	#define		ECM_ECMPE3_PE114_ERROR		(1)
#define		ECM_ECMPE3_PE113		(BIT17)
	#define		ECM_ECMPE3_PE113_NOERROR	(0)
	#define		ECM_ECMPE3_PE113_ERROR		(1)
#define		ECM_ECMPE3_PE112		(BIT16)
	#define		ECM_ECMPE3_PE112_NOERROR	(0)
	#define		ECM_ECMPE3_PE112_ERROR		(1)
#define		ECM_ECMPE3_PE111		(BIT15)
	#define		ECM_ECMPE3_PE111_NOERROR	(0)
	#define		ECM_ECMPE3_PE111_ERROR		(1)
#define		ECM_ECMPE3_PE110		(BIT14)
	#define		ECM_ECMPE3_PE110_NOERROR	(0)
	#define		ECM_ECMPE3_PE110_ERROR		(1)
#define		ECM_ECMPE3_PE109		(BIT13)
	#define		ECM_ECMPE3_PE109_NOERROR	(0)
	#define		ECM_ECMPE3_PE109_ERROR		(1)
#define		ECM_ECMPE3_PE108		(BIT12)
	#define		ECM_ECMPE3_PE108_NOERROR	(0)
	#define		ECM_ECMPE3_PE108_ERROR		(1)
#define		ECM_ECMPE3_PE107		(BIT11)
	#define		ECM_ECMPE3_PE107_NOERROR	(0)
	#define		ECM_ECMPE3_PE107_ERROR		(1)
#define		ECM_ECMPE3_PE106		(BIT10)
	#define		ECM_ECMPE3_PE106_NOERROR	(0)
	#define		ECM_ECMPE3_PE106_ERROR		(1)
#define		ECM_ECMPE3_PE105		(BIT9)
	#define		ECM_ECMPE3_PE105_NOERROR	(0)
	#define		ECM_ECMPE3_PE105_ERROR		(1)
#define		ECM_ECMPE3_PE104		(BIT8)
	#define		ECM_ECMPE3_PE104_NOERROR	(0)
	#define		ECM_ECMPE3_PE104_ERROR		(1)
#define		ECM_ECMPE3_PE103		(BIT7)
	#define		ECM_ECMPE3_PE103_NOERROR	(0)
	#define		ECM_ECMPE3_PE103_ERROR		(1)
#define		ECM_ECMPE3_PE102		(BIT6)
	#define		ECM_ECMPE3_PE102_NOERROR	(0)
	#define		ECM_ECMPE3_PE102_ERROR		(1)
#define		ECM_ECMPE3_PE101		(BIT5)
	#define		ECM_ECMPE3_PE101_NOERROR	(0)
	#define		ECM_ECMPE3_PE101_ERROR		(1)
#define		ECM_ECMPE3_PE100		(BIT4)
	#define		ECM_ECMPE3_PE100_NOERROR	(0)
	#define		ECM_ECMPE3_PE100_ERROR		(1)
#define		ECM_ECMPE3_PE099		(BIT3)
	#define		ECM_ECMPE3_PE099_NOERROR	(0)
	#define		ECM_ECMPE3_PE099_ERROR		(1)
#define		ECM_ECMPE3_PE098		(BIT2)
	#define		ECM_ECMPE3_PE098_NOERROR	(0)
	#define		ECM_ECMPE3_PE098_ERROR		(1)
#define		ECM_ECMPE3_PE097		(BIT1)
	#define		ECM_ECMPE3_PE097_NOERROR	(0)
	#define		ECM_ECMPE3_PE097_ERROR		(1)
#define		ECM_ECMPE3_PE096		(BIT0)
	#define		ECM_ECMPE3_PE096_NOERROR	(0)
	#define		ECM_ECMPE3_PE096_ERROR		(1)

/* ECMPE4 */
#define		ECM_ECMPE4_PE159		(BIT31)
	#define		ECM_ECMPE4_PE159_NOERROR	(0)
	#define		ECM_ECMPE4_PE159_ERROR		(1)
#define		ECM_ECMPE4_PE158		(BIT30)
	#define		ECM_ECMPE4_PE158_NOERROR	(0)
	#define		ECM_ECMPE4_PE158_ERROR		(1)
#define		ECM_ECMPE4_PE157		(BIT29)
	#define		ECM_ECMPE4_PE157_NOERROR	(0)
	#define		ECM_ECMPE4_PE157_ERROR		(1)
#define		ECM_ECMPE4_PE156		(BIT28)
	#define		ECM_ECMPE4_PE156_NOERROR	(0)
	#define		ECM_ECMPE4_PE156_ERROR		(1)
#define		ECM_ECMPE4_PE155		(BIT27)
	#define		ECM_ECMPE4_PE155_NOERROR	(0)
	#define		ECM_ECMPE4_PE155_ERROR		(1)
#define		ECM_ECMPE4_PE154		(BIT26)
	#define		ECM_ECMPE4_PE154_NOERROR	(0)
	#define		ECM_ECMPE4_PE154_ERROR		(1)
#define		ECM_ECMPE4_PE153		(BIT25)
	#define		ECM_ECMPE4_PE153_NOERROR	(0)
	#define		ECM_ECMPE4_PE153_ERROR		(1)
#define		ECM_ECMPE4_PE152		(BIT24)
	#define		ECM_ECMPE4_PE152_NOERROR	(0)
	#define		ECM_ECMPE4_PE152_ERROR		(1)
#define		ECM_ECMPE4_PE151		(BIT23)
	#define		ECM_ECMPE4_PE151_NOERROR	(0)
	#define		ECM_ECMPE4_PE151_ERROR		(1)
#define		ECM_ECMPE4_PE150		(BIT22)
	#define		ECM_ECMPE4_PE150_NOERROR	(0)
	#define		ECM_ECMPE4_PE150_ERROR		(1)
#define		ECM_ECMPE4_PE149		(BIT21)
	#define		ECM_ECMPE4_PE149_NOERROR	(0)
	#define		ECM_ECMPE4_PE149_ERROR		(1)
#define		ECM_ECMPE4_PE148		(BIT20)
	#define		ECM_ECMPE4_PE148_NOERROR	(0)
	#define		ECM_ECMPE4_PE148_ERROR		(1)
#define		ECM_ECMPE4_PE147		(BIT19)
	#define		ECM_ECMPE4_PE147_NOERROR	(0)
	#define		ECM_ECMPE4_PE147_ERROR		(1)
#define		ECM_ECMPE4_PE146		(BIT18)
	#define		ECM_ECMPE4_PE146_NOERROR	(0)
	#define		ECM_ECMPE4_PE146_ERROR		(1)
#define		ECM_ECMPE4_PE145		(BIT17)
	#define		ECM_ECMPE4_PE145_NOERROR	(0)
	#define		ECM_ECMPE4_PE145_ERROR		(1)
#define		ECM_ECMPE4_PE144		(BIT16)
	#define		ECM_ECMPE4_PE144_NOERROR	(0)
	#define		ECM_ECMPE4_PE144_ERROR		(1)
#define		ECM_ECMPE4_PE143		(BIT15)
	#define		ECM_ECMPE4_PE143_NOERROR	(0)
	#define		ECM_ECMPE4_PE143_ERROR		(1)
#define		ECM_ECMPE4_PE142		(BIT14)
	#define		ECM_ECMPE4_PE142_NOERROR	(0)
	#define		ECM_ECMPE4_PE142_ERROR		(1)
#define		ECM_ECMPE4_PE141		(BIT13)
	#define		ECM_ECMPE4_PE141_NOERROR	(0)
	#define		ECM_ECMPE4_PE141_ERROR		(1)
#define		ECM_ECMPE4_PE140		(BIT12)
	#define		ECM_ECMPE4_PE140_NOERROR	(0)
	#define		ECM_ECMPE4_PE140_ERROR		(1)
#define		ECM_ECMPE4_PE139		(BIT11)
	#define		ECM_ECMPE4_PE139_NOERROR	(0)
	#define		ECM_ECMPE4_PE139_ERROR		(1)
#define		ECM_ECMPE4_PE138		(BIT10)
	#define		ECM_ECMPE4_PE138_NOERROR	(0)
	#define		ECM_ECMPE4_PE138_ERROR		(1)
#define		ECM_ECMPE4_PE137		(BIT9)
	#define		ECM_ECMPE4_PE137_NOERROR	(0)
	#define		ECM_ECMPE4_PE137_ERROR		(1)
#define		ECM_ECMPE4_PE136		(BIT8)
	#define		ECM_ECMPE4_PE136_NOERROR	(0)
	#define		ECM_ECMPE4_PE136_ERROR		(1)
#define		ECM_ECMPE4_PE135		(BIT7)
	#define		ECM_ECMPE4_PE135_NOERROR	(0)
	#define		ECM_ECMPE4_PE135_ERROR		(1)
#define		ECM_ECMPE4_PE134		(BIT6)
	#define		ECM_ECMPE4_PE134_NOERROR	(0)
	#define		ECM_ECMPE4_PE134_ERROR		(1)
#define		ECM_ECMPE4_PE133		(BIT5)
	#define		ECM_ECMPE4_PE133_NOERROR	(0)
	#define		ECM_ECMPE4_PE133_ERROR		(1)
#define		ECM_ECMPE4_PE132		(BIT4)
	#define		ECM_ECMPE4_PE132_NOERROR	(0)
	#define		ECM_ECMPE4_PE132_ERROR		(1)
#define		ECM_ECMPE4_PE131		(BIT3)
	#define		ECM_ECMPE4_PE131_NOERROR	(0)
	#define		ECM_ECMPE4_PE131_ERROR		(1)
#define		ECM_ECMPE4_PE130		(BIT2)
	#define		ECM_ECMPE4_PE130_NOERROR	(0)
	#define		ECM_ECMPE4_PE130_ERROR		(1)
#define		ECM_ECMPE4_PE129		(BIT1)
	#define		ECM_ECMPE4_PE129_NOERROR	(0)
	#define		ECM_ECMPE4_PE129_ERROR		(1)
#define		ECM_ECMPE4_PE128		(BIT0)
	#define		ECM_ECMPE4_PE128_NOERROR	(0)
	#define		ECM_ECMPE4_PE128_ERROR		(1)

/* ECMPE5 */
#define		ECM_ECMPE5_PE191		(BIT31)
	#define		ECM_ECMPE5_PE191_NOERROR	(0)
	#define		ECM_ECMPE5_PE191_ERROR		(1)
#define		ECM_ECMPE5_PE190		(BIT30)
	#define		ECM_ECMPE5_PE190_NOERROR	(0)
	#define		ECM_ECMPE5_PE190_ERROR		(1)
#define		ECM_ECMPE5_PE189		(BIT29)
	#define		ECM_ECMPE5_PE189_NOERROR	(0)
	#define		ECM_ECMPE5_PE189_ERROR		(1)
#define		ECM_ECMPE5_PE188		(BIT28)
	#define		ECM_ECMPE5_PE188_NOERROR	(0)
	#define		ECM_ECMPE5_PE188_ERROR		(1)
#define		ECM_ECMPE5_PE187		(BIT27)
	#define		ECM_ECMPE5_PE187_NOERROR	(0)
	#define		ECM_ECMPE5_PE187_ERROR		(1)
#define		ECM_ECMPE5_PE186		(BIT26)
	#define		ECM_ECMPE5_PE186_NOERROR	(0)
	#define		ECM_ECMPE5_PE186_ERROR		(1)
#define		ECM_ECMPE5_PE185		(BIT25)
	#define		ECM_ECMPE5_PE185_NOERROR	(0)
	#define		ECM_ECMPE5_PE185_ERROR		(1)
#define		ECM_ECMPE5_PE184		(BIT24)
	#define		ECM_ECMPE5_PE184_NOERROR	(0)
	#define		ECM_ECMPE5_PE184_ERROR		(1)
#define		ECM_ECMPE5_PE183		(BIT23)
	#define		ECM_ECMPE5_PE183_NOERROR	(0)
	#define		ECM_ECMPE5_PE183_ERROR		(1)
#define		ECM_ECMPE5_PE182		(BIT22)
	#define		ECM_ECMPE5_PE182_NOERROR	(0)
	#define		ECM_ECMPE5_PE182_ERROR		(1)
#define		ECM_ECMPE5_PE181		(BIT21)
	#define		ECM_ECMPE5_PE181_NOERROR	(0)
	#define		ECM_ECMPE5_PE181_ERROR		(1)
#define		ECM_ECMPE5_PE180		(BIT20)
	#define		ECM_ECMPE5_PE180_NOERROR	(0)
	#define		ECM_ECMPE5_PE180_ERROR		(1)
#define		ECM_ECMPE5_PE179		(BIT19)
	#define		ECM_ECMPE5_PE179_NOERROR	(0)
	#define		ECM_ECMPE5_PE179_ERROR		(1)
#define		ECM_ECMPE5_PE178		(BIT18)
	#define		ECM_ECMPE5_PE178_NOERROR	(0)
	#define		ECM_ECMPE5_PE178_ERROR		(1)
#define		ECM_ECMPE5_PE177		(BIT17)
	#define		ECM_ECMPE5_PE177_NOERROR	(0)
	#define		ECM_ECMPE5_PE177_ERROR		(1)
#define		ECM_ECMPE5_PE176		(BIT16)
	#define		ECM_ECMPE5_PE176_NOERROR	(0)
	#define		ECM_ECMPE5_PE176_ERROR		(1)
#define		ECM_ECMPE5_PE175		(BIT15)
	#define		ECM_ECMPE5_PE175_NOERROR	(0)
	#define		ECM_ECMPE5_PE175_ERROR		(1)
#define		ECM_ECMPE5_PE174		(BIT14)
	#define		ECM_ECMPE5_PE174_NOERROR	(0)
	#define		ECM_ECMPE5_PE174_ERROR		(1)
#define		ECM_ECMPE5_PE173		(BIT13)
	#define		ECM_ECMPE5_PE173_NOERROR	(0)
	#define		ECM_ECMPE5_PE173_ERROR		(1)
#define		ECM_ECMPE5_PE172		(BIT12)
	#define		ECM_ECMPE5_PE172_NOERROR	(0)
	#define		ECM_ECMPE5_PE172_ERROR		(1)
#define		ECM_ECMPE5_PE171		(BIT11)
	#define		ECM_ECMPE5_PE171_NOERROR	(0)
	#define		ECM_ECMPE5_PE171_ERROR		(1)
#define		ECM_ECMPE5_PE170		(BIT10)
	#define		ECM_ECMPE5_PE170_NOERROR	(0)
	#define		ECM_ECMPE5_PE170_ERROR		(1)
#define		ECM_ECMPE5_PE169		(BIT9)
	#define		ECM_ECMPE5_PE169_NOERROR	(0)
	#define		ECM_ECMPE5_PE169_ERROR		(1)
#define		ECM_ECMPE5_PE168		(BIT8)
	#define		ECM_ECMPE5_PE168_NOERROR	(0)
	#define		ECM_ECMPE5_PE168_ERROR		(1)
#define		ECM_ECMPE5_PE167		(BIT7)
	#define		ECM_ECMPE5_PE167_NOERROR	(0)
	#define		ECM_ECMPE5_PE167_ERROR		(1)
#define		ECM_ECMPE5_PE166		(BIT6)
	#define		ECM_ECMPE5_PE166_NOERROR	(0)
	#define		ECM_ECMPE5_PE166_ERROR		(1)
#define		ECM_ECMPE5_PE165		(BIT5)
	#define		ECM_ECMPE5_PE165_NOERROR	(0)
	#define		ECM_ECMPE5_PE165_ERROR		(1)
#define		ECM_ECMPE5_PE164		(BIT4)
	#define		ECM_ECMPE5_PE164_NOERROR	(0)
	#define		ECM_ECMPE5_PE164_ERROR		(1)
#define		ECM_ECMPE5_PE163		(BIT3)
	#define		ECM_ECMPE5_PE163_NOERROR	(0)
	#define		ECM_ECMPE5_PE163_ERROR		(1)
#define		ECM_ECMPE5_PE162		(BIT2)
	#define		ECM_ECMPE5_PE162_NOERROR	(0)
	#define		ECM_ECMPE5_PE162_ERROR		(1)
#define		ECM_ECMPE5_PE161		(BIT1)
	#define		ECM_ECMPE5_PE161_NOERROR	(0)
	#define		ECM_ECMPE5_PE161_ERROR		(1)
#define		ECM_ECMPE5_PE160		(BIT0)
	#define		ECM_ECMPE5_PE160_NOERROR	(0)
	#define		ECM_ECMPE5_PE160_ERROR		(1)

/* ECMPE6 */
#define		ECM_ECMPE6_PE223		(BIT31)
	#define		ECM_ECMPE6_PE223_NOERROR	(0)
	#define		ECM_ECMPE6_PE223_ERROR		(1)
#define		ECM_ECMPE6_PE222		(BIT30)
	#define		ECM_ECMPE6_PE222_NOERROR	(0)
	#define		ECM_ECMPE6_PE222_ERROR		(1)
#define		ECM_ECMPE6_PE221		(BIT29)
	#define		ECM_ECMPE6_PE221_NOERROR	(0)
	#define		ECM_ECMPE6_PE221_ERROR		(1)
#define		ECM_ECMPE6_PE220		(BIT28)
	#define		ECM_ECMPE6_PE220_NOERROR	(0)
	#define		ECM_ECMPE6_PE220_ERROR		(1)
#define		ECM_ECMPE6_PE219		(BIT27)
	#define		ECM_ECMPE6_PE219_NOERROR	(0)
	#define		ECM_ECMPE6_PE219_ERROR		(1)
#define		ECM_ECMPE6_PE218		(BIT26)
	#define		ECM_ECMPE6_PE218_NOERROR	(0)
	#define		ECM_ECMPE6_PE218_ERROR		(1)
#define		ECM_ECMPE6_PE217		(BIT25)
	#define		ECM_ECMPE6_PE217_NOERROR	(0)
	#define		ECM_ECMPE6_PE217_ERROR		(1)
#define		ECM_ECMPE6_PE216		(BIT24)
	#define		ECM_ECMPE6_PE216_NOERROR	(0)
	#define		ECM_ECMPE6_PE216_ERROR		(1)
#define		ECM_ECMPE6_PE215		(BIT23)
	#define		ECM_ECMPE6_PE215_NOERROR	(0)
	#define		ECM_ECMPE6_PE215_ERROR		(1)
#define		ECM_ECMPE6_PE214		(BIT22)
	#define		ECM_ECMPE6_PE214_NOERROR	(0)
	#define		ECM_ECMPE6_PE214_ERROR		(1)
#define		ECM_ECMPE6_PE213		(BIT21)
	#define		ECM_ECMPE6_PE213_NOERROR	(0)
	#define		ECM_ECMPE6_PE213_ERROR		(1)
#define		ECM_ECMPE6_PE212		(BIT20)
	#define		ECM_ECMPE6_PE212_NOERROR	(0)
	#define		ECM_ECMPE6_PE212_ERROR		(1)
#define		ECM_ECMPE6_PE211		(BIT19)
	#define		ECM_ECMPE6_PE211_NOERROR	(0)
	#define		ECM_ECMPE6_PE211_ERROR		(1)
#define		ECM_ECMPE6_PE210		(BIT18)
	#define		ECM_ECMPE6_PE210_NOERROR	(0)
	#define		ECM_ECMPE6_PE210_ERROR		(1)
#define		ECM_ECMPE6_PE209		(BIT17)
	#define		ECM_ECMPE6_PE209_NOERROR	(0)
	#define		ECM_ECMPE6_PE209_ERROR		(1)
#define		ECM_ECMPE6_PE208		(BIT16)
	#define		ECM_ECMPE6_PE208_NOERROR	(0)
	#define		ECM_ECMPE6_PE208_ERROR		(1)
#define		ECM_ECMPE6_PE207		(BIT15)
	#define		ECM_ECMPE6_PE207_NOERROR	(0)
	#define		ECM_ECMPE6_PE207_ERROR		(1)
#define		ECM_ECMPE6_PE206		(BIT14)
	#define		ECM_ECMPE6_PE206_NOERROR	(0)
	#define		ECM_ECMPE6_PE206_ERROR		(1)
#define		ECM_ECMPE6_PE205		(BIT13)
	#define		ECM_ECMPE6_PE205_NOERROR	(0)
	#define		ECM_ECMPE6_PE205_ERROR		(1)
#define		ECM_ECMPE6_PE204		(BIT12)
	#define		ECM_ECMPE6_PE204_NOERROR	(0)
	#define		ECM_ECMPE6_PE204_ERROR		(1)
#define		ECM_ECMPE6_PE203		(BIT11)
	#define		ECM_ECMPE6_PE203_NOERROR	(0)
	#define		ECM_ECMPE6_PE203_ERROR		(1)
#define		ECM_ECMPE6_PE202		(BIT10)
	#define		ECM_ECMPE6_PE202_NOERROR	(0)
	#define		ECM_ECMPE6_PE202_ERROR		(1)
#define		ECM_ECMPE6_PE201		(BIT9)
	#define		ECM_ECMPE6_PE201_NOERROR	(0)
	#define		ECM_ECMPE6_PE201_ERROR		(1)
#define		ECM_ECMPE6_PE200		(BIT8)
	#define		ECM_ECMPE6_PE200_NOERROR	(0)
	#define		ECM_ECMPE6_PE200_ERROR		(1)
#define		ECM_ECMPE6_PE199		(BIT7)
	#define		ECM_ECMPE6_PE199_NOERROR	(0)
	#define		ECM_ECMPE6_PE199_ERROR		(1)
#define		ECM_ECMPE6_PE198		(BIT6)
	#define		ECM_ECMPE6_PE198_NOERROR	(0)
	#define		ECM_ECMPE6_PE198_ERROR		(1)
#define		ECM_ECMPE6_PE197		(BIT5)
	#define		ECM_ECMPE6_PE197_NOERROR	(0)
	#define		ECM_ECMPE6_PE197_ERROR		(1)
#define		ECM_ECMPE6_PE196		(BIT4)
	#define		ECM_ECMPE6_PE196_NOERROR	(0)
	#define		ECM_ECMPE6_PE196_ERROR		(1)
#define		ECM_ECMPE6_PE195		(BIT3)
	#define		ECM_ECMPE6_PE195_NOERROR	(0)
	#define		ECM_ECMPE6_PE195_ERROR		(1)
#define		ECM_ECMPE6_PE194		(BIT2)
	#define		ECM_ECMPE6_PE194_NOERROR	(0)
	#define		ECM_ECMPE6_PE194_ERROR		(1)
#define		ECM_ECMPE6_PE193		(BIT1)
	#define		ECM_ECMPE6_PE193_NOERROR	(0)
	#define		ECM_ECMPE6_PE193_ERROR		(1)
#define		ECM_ECMPE6_PE192		(BIT0)
	#define		ECM_ECMPE6_PE192_NOERROR	(0)
	#define		ECM_ECMPE6_PE192_ERROR		(1)

/* ECMPE7 */
#define		ECM_ECMPE7_PE255		(BIT31)
	#define		ECM_ECMPE7_PE255_NOERROR	(0)
	#define		ECM_ECMPE7_PE255_ERROR		(1)
#define		ECM_ECMPE7_PE254		(BIT30)
	#define		ECM_ECMPE7_PE254_NOERROR	(0)
	#define		ECM_ECMPE7_PE254_ERROR		(1)
#define		ECM_ECMPE7_PE253		(BIT29)
	#define		ECM_ECMPE7_PE253_NOERROR	(0)
	#define		ECM_ECMPE7_PE253_ERROR		(1)
#define		ECM_ECMPE7_PE252		(BIT28)
	#define		ECM_ECMPE7_PE252_NOERROR	(0)
	#define		ECM_ECMPE7_PE252_ERROR		(1)
#define		ECM_ECMPE7_PE251		(BIT27)
	#define		ECM_ECMPE7_PE251_NOERROR	(0)
	#define		ECM_ECMPE7_PE251_ERROR		(1)
#define		ECM_ECMPE7_PE250		(BIT26)
	#define		ECM_ECMPE7_PE250_NOERROR	(0)
	#define		ECM_ECMPE7_PE250_ERROR		(1)
#define		ECM_ECMPE7_PE249		(BIT25)
	#define		ECM_ECMPE7_PE249_NOERROR	(0)
	#define		ECM_ECMPE7_PE249_ERROR		(1)
#define		ECM_ECMPE7_PE248		(BIT24)
	#define		ECM_ECMPE7_PE248_NOERROR	(0)
	#define		ECM_ECMPE7_PE248_ERROR		(1)
#define		ECM_ECMPE7_PE247		(BIT23)
	#define		ECM_ECMPE7_PE247_NOERROR	(0)
	#define		ECM_ECMPE7_PE247_ERROR		(1)
#define		ECM_ECMPE7_PE246		(BIT22)
	#define		ECM_ECMPE7_PE246_NOERROR	(0)
	#define		ECM_ECMPE7_PE246_ERROR		(1)
#define		ECM_ECMPE7_PE245		(BIT21)
	#define		ECM_ECMPE7_PE245_NOERROR	(0)
	#define		ECM_ECMPE7_PE245_ERROR		(1)
#define		ECM_ECMPE7_PE244		(BIT20)
	#define		ECM_ECMPE7_PE244_NOERROR	(0)
	#define		ECM_ECMPE7_PE244_ERROR		(1)
#define		ECM_ECMPE7_PE243		(BIT19)
	#define		ECM_ECMPE7_PE243_NOERROR	(0)
	#define		ECM_ECMPE7_PE243_ERROR		(1)
#define		ECM_ECMPE7_PE242		(BIT18)
	#define		ECM_ECMPE7_PE242_NOERROR	(0)
	#define		ECM_ECMPE7_PE242_ERROR		(1)
#define		ECM_ECMPE7_PE241		(BIT17)
	#define		ECM_ECMPE7_PE241_NOERROR	(0)
	#define		ECM_ECMPE7_PE241_ERROR		(1)
#define		ECM_ECMPE7_PE240		(BIT16)
	#define		ECM_ECMPE7_PE240_NOERROR	(0)
	#define		ECM_ECMPE7_PE240_ERROR		(1)
#define		ECM_ECMPE7_PE239		(BIT15)
	#define		ECM_ECMPE7_PE239_NOERROR	(0)
	#define		ECM_ECMPE7_PE239_ERROR		(1)
#define		ECM_ECMPE7_PE238		(BIT14)
	#define		ECM_ECMPE7_PE238_NOERROR	(0)
	#define		ECM_ECMPE7_PE238_ERROR		(1)
#define		ECM_ECMPE7_PE237		(BIT13)
	#define		ECM_ECMPE7_PE237_NOERROR	(0)
	#define		ECM_ECMPE7_PE237_ERROR		(1)
#define		ECM_ECMPE7_PE236		(BIT12)
	#define		ECM_ECMPE7_PE236_NOERROR	(0)
	#define		ECM_ECMPE7_PE236_ERROR		(1)
#define		ECM_ECMPE7_PE235		(BIT11)
	#define		ECM_ECMPE7_PE235_NOERROR	(0)
	#define		ECM_ECMPE7_PE235_ERROR		(1)
#define		ECM_ECMPE7_PE234		(BIT10)
	#define		ECM_ECMPE7_PE234_NOERROR	(0)
	#define		ECM_ECMPE7_PE234_ERROR		(1)
#define		ECM_ECMPE7_PE233		(BIT9)
	#define		ECM_ECMPE7_PE233_NOERROR	(0)
	#define		ECM_ECMPE7_PE233_ERROR		(1)
#define		ECM_ECMPE7_PE232		(BIT8)
	#define		ECM_ECMPE7_PE232_NOERROR	(0)
	#define		ECM_ECMPE7_PE232_ERROR		(1)
#define		ECM_ECMPE7_PE231		(BIT7)
	#define		ECM_ECMPE7_PE231_NOERROR	(0)
	#define		ECM_ECMPE7_PE231_ERROR		(1)
#define		ECM_ECMPE7_PE230		(BIT6)
	#define		ECM_ECMPE7_PE230_NOERROR	(0)
	#define		ECM_ECMPE7_PE230_ERROR		(1)
#define		ECM_ECMPE7_PE229		(BIT5)
	#define		ECM_ECMPE7_PE229_NOERROR	(0)
	#define		ECM_ECMPE7_PE229_ERROR		(1)
#define		ECM_ECMPE7_PE228		(BIT4)
	#define		ECM_ECMPE7_PE228_NOERROR	(0)
	#define		ECM_ECMPE7_PE228_ERROR		(1)
#define		ECM_ECMPE7_PE227		(BIT3)
	#define		ECM_ECMPE7_PE227_NOERROR	(0)
	#define		ECM_ECMPE7_PE227_ERROR		(1)
#define		ECM_ECMPE7_PE226		(BIT2)
	#define		ECM_ECMPE7_PE226_NOERROR	(0)
	#define		ECM_ECMPE7_PE226_ERROR		(1)
#define		ECM_ECMPE7_PE225		(BIT1)
	#define		ECM_ECMPE7_PE225_NOERROR	(0)
	#define		ECM_ECMPE7_PE225_ERROR		(1)
#define		ECM_ECMPE7_PE224		(BIT0)
	#define		ECM_ECMPE7_PE224_NOERROR	(0)
	#define		ECM_ECMPE7_PE224_ERROR		(1)

/* ECMPE8 */
#define		ECM_ECMPE8_PE287		(BIT31)
	#define		ECM_ECMPE8_PE287_NOERROR	(0)
	#define		ECM_ECMPE8_PE287_ERROR		(1)
#define		ECM_ECMPE8_PE286		(BIT30)
	#define		ECM_ECMPE8_PE286_NOERROR	(0)
	#define		ECM_ECMPE8_PE286_ERROR		(1)
#define		ECM_ECMPE8_PE285		(BIT29)
	#define		ECM_ECMPE8_PE285_NOERROR	(0)
	#define		ECM_ECMPE8_PE285_ERROR		(1)
#define		ECM_ECMPE8_PE284		(BIT28)
	#define		ECM_ECMPE8_PE284_NOERROR	(0)
	#define		ECM_ECMPE8_PE284_ERROR		(1)
#define		ECM_ECMPE8_PE283		(BIT27)
	#define		ECM_ECMPE8_PE283_NOERROR	(0)
	#define		ECM_ECMPE8_PE283_ERROR		(1)
#define		ECM_ECMPE8_PE282		(BIT26)
	#define		ECM_ECMPE8_PE282_NOERROR	(0)
	#define		ECM_ECMPE8_PE282_ERROR		(1)
#define		ECM_ECMPE8_PE281		(BIT25)
	#define		ECM_ECMPE8_PE281_NOERROR	(0)
	#define		ECM_ECMPE8_PE281_ERROR		(1)
#define		ECM_ECMPE8_PE280		(BIT24)
	#define		ECM_ECMPE8_PE280_NOERROR	(0)
	#define		ECM_ECMPE8_PE280_ERROR		(1)
#define		ECM_ECMPE8_PE279		(BIT23)
	#define		ECM_ECMPE8_PE279_NOERROR	(0)
	#define		ECM_ECMPE8_PE279_ERROR		(1)
#define		ECM_ECMPE8_PE278		(BIT22)
	#define		ECM_ECMPE8_PE278_NOERROR	(0)
	#define		ECM_ECMPE8_PE278_ERROR		(1)
#define		ECM_ECMPE8_PE277		(BIT21)
	#define		ECM_ECMPE8_PE277_NOERROR	(0)
	#define		ECM_ECMPE8_PE277_ERROR		(1)
#define		ECM_ECMPE8_PE276		(BIT20)
	#define		ECM_ECMPE8_PE276_NOERROR	(0)
	#define		ECM_ECMPE8_PE276_ERROR		(1)
#define		ECM_ECMPE8_PE275		(BIT19)
	#define		ECM_ECMPE8_PE275_NOERROR	(0)
	#define		ECM_ECMPE8_PE275_ERROR		(1)
#define		ECM_ECMPE8_PE274		(BIT18)
	#define		ECM_ECMPE8_PE274_NOERROR	(0)
	#define		ECM_ECMPE8_PE274_ERROR		(1)
#define		ECM_ECMPE8_PE273		(BIT17)
	#define		ECM_ECMPE8_PE273_NOERROR	(0)
	#define		ECM_ECMPE8_PE273_ERROR		(1)
#define		ECM_ECMPE8_PE272		(BIT16)
	#define		ECM_ECMPE8_PE272_NOERROR	(0)
	#define		ECM_ECMPE8_PE272_ERROR		(1)
#define		ECM_ECMPE8_PE271		(BIT15)
	#define		ECM_ECMPE8_PE271_NOERROR	(0)
	#define		ECM_ECMPE8_PE271_ERROR		(1)
#define		ECM_ECMPE8_PE270		(BIT14)
	#define		ECM_ECMPE8_PE270_NOERROR	(0)
	#define		ECM_ECMPE8_PE270_ERROR		(1)
#define		ECM_ECMPE8_PE269		(BIT13)
	#define		ECM_ECMPE8_PE269_NOERROR	(0)
	#define		ECM_ECMPE8_PE269_ERROR		(1)
#define		ECM_ECMPE8_PE268		(BIT12)
	#define		ECM_ECMPE8_PE268_NOERROR	(0)
	#define		ECM_ECMPE8_PE268_ERROR		(1)
#define		ECM_ECMPE8_PE267		(BIT11)
	#define		ECM_ECMPE8_PE267_NOERROR	(0)
	#define		ECM_ECMPE8_PE267_ERROR		(1)
#define		ECM_ECMPE8_PE266		(BIT10)
	#define		ECM_ECMPE8_PE266_NOERROR	(0)
	#define		ECM_ECMPE8_PE266_ERROR		(1)
#define		ECM_ECMPE8_PE265		(BIT9)
	#define		ECM_ECMPE8_PE265_NOERROR	(0)
	#define		ECM_ECMPE8_PE265_ERROR		(1)
#define		ECM_ECMPE8_PE264		(BIT8)
	#define		ECM_ECMPE8_PE264_NOERROR	(0)
	#define		ECM_ECMPE8_PE264_ERROR		(1)
#define		ECM_ECMPE8_PE263		(BIT7)
	#define		ECM_ECMPE8_PE263_NOERROR	(0)
	#define		ECM_ECMPE8_PE263_ERROR		(1)
#define		ECM_ECMPE8_PE262		(BIT6)
	#define		ECM_ECMPE8_PE262_NOERROR	(0)
	#define		ECM_ECMPE8_PE262_ERROR		(1)
#define		ECM_ECMPE8_PE261		(BIT5)
	#define		ECM_ECMPE8_PE261_NOERROR	(0)
	#define		ECM_ECMPE8_PE261_ERROR		(1)
#define		ECM_ECMPE8_PE260		(BIT4)
	#define		ECM_ECMPE8_PE260_NOERROR	(0)
	#define		ECM_ECMPE8_PE260_ERROR		(1)
#define		ECM_ECMPE8_PE259		(BIT3)
	#define		ECM_ECMPE8_PE259_NOERROR	(0)
	#define		ECM_ECMPE8_PE259_ERROR		(1)
#define		ECM_ECMPE8_PE258		(BIT2)
	#define		ECM_ECMPE8_PE258_NOERROR	(0)
	#define		ECM_ECMPE8_PE258_ERROR		(1)
#define		ECM_ECMPE8_PE257		(BIT1)
	#define		ECM_ECMPE8_PE257_NOERROR	(0)
	#define		ECM_ECMPE8_PE257_ERROR		(1)
#define		ECM_ECMPE8_PE256		(BIT0)
	#define		ECM_ECMPE8_PE256_NOERROR	(0)
	#define		ECM_ECMPE8_PE256_ERROR		(1)

/* ECMPE9 */
#define		ECM_ECMPE9_PE319		(BIT31)
	#define		ECM_ECMPE9_PE319_NOERROR	(0)
	#define		ECM_ECMPE9_PE319_ERROR		(1)
#define		ECM_ECMPE9_PE318		(BIT30)
	#define		ECM_ECMPE9_PE318_NOERROR	(0)
	#define		ECM_ECMPE9_PE318_ERROR		(1)
#define		ECM_ECMPE9_PE317		(BIT29)
	#define		ECM_ECMPE9_PE317_NOERROR	(0)
	#define		ECM_ECMPE9_PE317_ERROR		(1)
#define		ECM_ECMPE9_PE316		(BIT28)
	#define		ECM_ECMPE9_PE316_NOERROR	(0)
	#define		ECM_ECMPE9_PE316_ERROR		(1)
#define		ECM_ECMPE9_PE315		(BIT27)
	#define		ECM_ECMPE9_PE315_NOERROR	(0)
	#define		ECM_ECMPE9_PE315_ERROR		(1)
#define		ECM_ECMPE9_PE314		(BIT26)
	#define		ECM_ECMPE9_PE314_NOERROR	(0)
	#define		ECM_ECMPE9_PE314_ERROR		(1)
#define		ECM_ECMPE9_PE313		(BIT25)
	#define		ECM_ECMPE9_PE313_NOERROR	(0)
	#define		ECM_ECMPE9_PE313_ERROR		(1)
#define		ECM_ECMPE9_PE312		(BIT24)
	#define		ECM_ECMPE9_PE312_NOERROR	(0)
	#define		ECM_ECMPE9_PE312_ERROR		(1)
#define		ECM_ECMPE9_PE311		(BIT23)
	#define		ECM_ECMPE9_PE311_NOERROR	(0)
	#define		ECM_ECMPE9_PE311_ERROR		(1)
#define		ECM_ECMPE9_PE310		(BIT22)
	#define		ECM_ECMPE9_PE310_NOERROR	(0)
	#define		ECM_ECMPE9_PE310_ERROR		(1)
#define		ECM_ECMPE9_PE309		(BIT21)
	#define		ECM_ECMPE9_PE309_NOERROR	(0)
	#define		ECM_ECMPE9_PE309_ERROR		(1)
#define		ECM_ECMPE9_PE308		(BIT20)
	#define		ECM_ECMPE9_PE308_NOERROR	(0)
	#define		ECM_ECMPE9_PE308_ERROR		(1)
#define		ECM_ECMPE9_PE307		(BIT19)
	#define		ECM_ECMPE9_PE307_NOERROR	(0)
	#define		ECM_ECMPE9_PE307_ERROR		(1)
#define		ECM_ECMPE9_PE306		(BIT18)
	#define		ECM_ECMPE9_PE306_NOERROR	(0)
	#define		ECM_ECMPE9_PE306_ERROR		(1)
#define		ECM_ECMPE9_PE305		(BIT17)
	#define		ECM_ECMPE9_PE305_NOERROR	(0)
	#define		ECM_ECMPE9_PE305_ERROR		(1)
#define		ECM_ECMPE9_PE304		(BIT16)
	#define		ECM_ECMPE9_PE304_NOERROR	(0)
	#define		ECM_ECMPE9_PE304_ERROR		(1)
#define		ECM_ECMPE9_PE303		(BIT15)
	#define		ECM_ECMPE9_PE303_NOERROR	(0)
	#define		ECM_ECMPE9_PE303_ERROR		(1)
#define		ECM_ECMPE9_PE302		(BIT14)
	#define		ECM_ECMPE9_PE302_NOERROR	(0)
	#define		ECM_ECMPE9_PE302_ERROR		(1)
#define		ECM_ECMPE9_PE301		(BIT13)
	#define		ECM_ECMPE9_PE301_NOERROR	(0)
	#define		ECM_ECMPE9_PE301_ERROR		(1)
#define		ECM_ECMPE9_PE300		(BIT12)
	#define		ECM_ECMPE9_PE300_NOERROR	(0)
	#define		ECM_ECMPE9_PE300_ERROR		(1)
#define		ECM_ECMPE9_PE299		(BIT11)
	#define		ECM_ECMPE9_PE299_NOERROR	(0)
	#define		ECM_ECMPE9_PE299_ERROR		(1)
#define		ECM_ECMPE9_PE298		(BIT10)
	#define		ECM_ECMPE9_PE298_NOERROR	(0)
	#define		ECM_ECMPE9_PE298_ERROR		(1)
#define		ECM_ECMPE9_PE297		(BIT9)
	#define		ECM_ECMPE9_PE297_NOERROR	(0)
	#define		ECM_ECMPE9_PE297_ERROR		(1)
#define		ECM_ECMPE9_PE296		(BIT8)
	#define		ECM_ECMPE9_PE296_NOERROR	(0)
	#define		ECM_ECMPE9_PE296_ERROR		(1)
#define		ECM_ECMPE9_PE295		(BIT7)
	#define		ECM_ECMPE9_PE295_NOERROR	(0)
	#define		ECM_ECMPE9_PE295_ERROR		(1)
#define		ECM_ECMPE9_PE294		(BIT6)
	#define		ECM_ECMPE9_PE294_NOERROR	(0)
	#define		ECM_ECMPE9_PE294_ERROR		(1)
#define		ECM_ECMPE9_PE293		(BIT5)
	#define		ECM_ECMPE9_PE293_NOERROR	(0)
	#define		ECM_ECMPE9_PE293_ERROR		(1)
#define		ECM_ECMPE9_PE292		(BIT4)
	#define		ECM_ECMPE9_PE292_NOERROR	(0)
	#define		ECM_ECMPE9_PE292_ERROR		(1)
#define		ECM_ECMPE9_PE291		(BIT3)
	#define		ECM_ECMPE9_PE291_NOERROR	(0)
	#define		ECM_ECMPE9_PE291_ERROR		(1)
#define		ECM_ECMPE9_PE290		(BIT2)
	#define		ECM_ECMPE9_PE290_NOERROR	(0)
	#define		ECM_ECMPE9_PE290_ERROR		(1)
#define		ECM_ECMPE9_PE289		(BIT1)
	#define		ECM_ECMPE9_PE289_NOERROR	(0)
	#define		ECM_ECMPE9_PE289_ERROR		(1)
#define		ECM_ECMPE9_PE288		(BIT0)
	#define		ECM_ECMPE9_PE288_NOERROR	(0)
	#define		ECM_ECMPE9_PE288_ERROR		(1)

/* ECMPE10 */
#define		ECM_ECMPE10_PE351		(BIT31)
	#define		ECM_ECMPE10_PE351_NOERROR	(0)
	#define		ECM_ECMPE10_PE351_ERROR		(1)
#define		ECM_ECMPE10_PE350		(BIT30)
	#define		ECM_ECMPE10_PE350_NOERROR	(0)
	#define		ECM_ECMPE10_PE350_ERROR		(1)
#define		ECM_ECMPE10_PE349		(BIT29)
	#define		ECM_ECMPE10_PE349_NOERROR	(0)
	#define		ECM_ECMPE10_PE349_ERROR		(1)
#define		ECM_ECMPE10_PE348		(BIT28)
	#define		ECM_ECMPE10_PE348_NOERROR	(0)
	#define		ECM_ECMPE10_PE348_ERROR		(1)
#define		ECM_ECMPE10_PE347		(BIT27)
	#define		ECM_ECMPE10_PE347_NOERROR	(0)
	#define		ECM_ECMPE10_PE347_ERROR		(1)
#define		ECM_ECMPE10_PE346		(BIT26)
	#define		ECM_ECMPE10_PE346_NOERROR	(0)
	#define		ECM_ECMPE10_PE346_ERROR		(1)
#define		ECM_ECMPE10_PE345		(BIT25)
	#define		ECM_ECMPE10_PE345_NOERROR	(0)
	#define		ECM_ECMPE10_PE345_ERROR		(1)
#define		ECM_ECMPE10_PE344		(BIT24)
	#define		ECM_ECMPE10_PE344_NOERROR	(0)
	#define		ECM_ECMPE10_PE344_ERROR		(1)
#define		ECM_ECMPE10_PE343		(BIT23)
	#define		ECM_ECMPE10_PE343_NOERROR	(0)
	#define		ECM_ECMPE10_PE343_ERROR		(1)
#define		ECM_ECMPE10_PE342		(BIT22)
	#define		ECM_ECMPE10_PE342_NOERROR	(0)
	#define		ECM_ECMPE10_PE342_ERROR		(1)
#define		ECM_ECMPE10_PE341		(BIT21)
	#define		ECM_ECMPE10_PE341_NOERROR	(0)
	#define		ECM_ECMPE10_PE341_ERROR		(1)
#define		ECM_ECMPE10_PE340		(BIT20)
	#define		ECM_ECMPE10_PE340_NOERROR	(0)
	#define		ECM_ECMPE10_PE340_ERROR		(1)
#define		ECM_ECMPE10_PE339		(BIT19)
	#define		ECM_ECMPE10_PE339_NOERROR	(0)
	#define		ECM_ECMPE10_PE339_ERROR		(1)
#define		ECM_ECMPE10_PE338		(BIT18)
	#define		ECM_ECMPE10_PE338_NOERROR	(0)
	#define		ECM_ECMPE10_PE338_ERROR		(1)
#define		ECM_ECMPE10_PE337		(BIT17)
	#define		ECM_ECMPE10_PE337_NOERROR	(0)
	#define		ECM_ECMPE10_PE337_ERROR		(1)
#define		ECM_ECMPE10_PE336		(BIT16)
	#define		ECM_ECMPE10_PE336_NOERROR	(0)
	#define		ECM_ECMPE10_PE336_ERROR		(1)
#define		ECM_ECMPE10_PE335		(BIT15)
	#define		ECM_ECMPE10_PE335_NOERROR	(0)
	#define		ECM_ECMPE10_PE335_ERROR		(1)
#define		ECM_ECMPE10_PE334		(BIT14)
	#define		ECM_ECMPE10_PE334_NOERROR	(0)
	#define		ECM_ECMPE10_PE334_ERROR		(1)
#define		ECM_ECMPE10_PE333		(BIT13)
	#define		ECM_ECMPE10_PE333_NOERROR	(0)
	#define		ECM_ECMPE10_PE333_ERROR		(1)
#define		ECM_ECMPE10_PE332		(BIT12)
	#define		ECM_ECMPE10_PE332_NOERROR	(0)
	#define		ECM_ECMPE10_PE332_ERROR		(1)
#define		ECM_ECMPE10_PE331		(BIT11)
	#define		ECM_ECMPE10_PE331_NOERROR	(0)
	#define		ECM_ECMPE10_PE331_ERROR		(1)
#define		ECM_ECMPE10_PE330		(BIT10)
	#define		ECM_ECMPE10_PE330_NOERROR	(0)
	#define		ECM_ECMPE10_PE330_ERROR		(1)
#define		ECM_ECMPE10_PE329		(BIT9)
	#define		ECM_ECMPE10_PE329_NOERROR	(0)
	#define		ECM_ECMPE10_PE329_ERROR		(1)
#define		ECM_ECMPE10_PE328		(BIT8)
	#define		ECM_ECMPE10_PE328_NOERROR	(0)
	#define		ECM_ECMPE10_PE328_ERROR		(1)
#define		ECM_ECMPE10_PE327		(BIT7)
	#define		ECM_ECMPE10_PE327_NOERROR	(0)
	#define		ECM_ECMPE10_PE327_ERROR		(1)
#define		ECM_ECMPE10_PE326		(BIT6)
	#define		ECM_ECMPE10_PE326_NOERROR	(0)
	#define		ECM_ECMPE10_PE326_ERROR		(1)
#define		ECM_ECMPE10_PE325		(BIT5)
	#define		ECM_ECMPE10_PE325_NOERROR	(0)
	#define		ECM_ECMPE10_PE325_ERROR		(1)
#define		ECM_ECMPE10_PE324		(BIT4)
	#define		ECM_ECMPE10_PE324_NOERROR	(0)
	#define		ECM_ECMPE10_PE324_ERROR		(1)
#define		ECM_ECMPE10_PE323		(BIT3)
	#define		ECM_ECMPE10_PE323_NOERROR	(0)
	#define		ECM_ECMPE10_PE323_ERROR		(1)
#define		ECM_ECMPE10_PE322		(BIT2)
	#define		ECM_ECMPE10_PE322_NOERROR	(0)
	#define		ECM_ECMPE10_PE322_ERROR		(1)
#define		ECM_ECMPE10_PE321		(BIT1)
	#define		ECM_ECMPE10_PE321_NOERROR	(0)
	#define		ECM_ECMPE10_PE321_ERROR		(1)
#define		ECM_ECMPE10_PE320		(BIT0)
	#define		ECM_ECMPE10_PE320_NOERROR	(0)
	#define		ECM_ECMPE10_PE320_ERROR		(1)

/* ECMDTMCTL */
#define		ECM_ECMDTMCTL_CNTCLK		(BIT4)
	#define		ECM_ECMDTMCTL_CNTCLK_STOP		(0)
	#define		ECM_ECMDTMCTL_CNTCLK_START		(1)
#define		ECM_ECMDTMCTL_ECMSTP		(BIT1)
	#define		ECM_ECMDTMCTL_ECMSTP_STOP		(1)
#define		ECM_ECMDTMCTL_ECMSTA		(BIT0)
	#define		ECM_ECMDTMCTL_ECMSTA_STOP		(0)
	#define		ECM_ECMDTMCTL_ECMSTA_START		(1)

/* ECMDTMR */
#define		ECM_ECMDTMR_DTMR			(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* ECMDTMCMP */
#define		ECM_ECMDTMCMP_CMPW			(BIT24)
	#define		ECM_ECMDTMCMP_CMPW_NOEXECUTE	(0)
	#define		ECM_ECMDTMCMP_CMPW_EXECUTE		(1)
#define		ECM_ECMDTMCMP_DTMCMP		(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)
#define		ECM_ECMDTMCMP_DTMCMP_0		(BIT0)

/* ECMDTMCFG0 */
#define		ECM_ECMDTMCFG0_DTME031		(BIT31)
	#define		ECM_ECMDTMCFG0_DTME031_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME031_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME030		(BIT30)
	#define		ECM_ECMDTMCFG0_DTME030_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME030_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME029		(BIT29)
	#define		ECM_ECMDTMCFG0_DTME029_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME029_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME028		(BIT28)
	#define		ECM_ECMDTMCFG0_DTME028_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME028_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME027		(BIT27)
	#define		ECM_ECMDTMCFG0_DTME027_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME027_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME026		(BIT26)
	#define		ECM_ECMDTMCFG0_DTME026_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME026_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME025		(BIT25)
	#define		ECM_ECMDTMCFG0_DTME025_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME025_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME024		(BIT24)
	#define		ECM_ECMDTMCFG0_DTME024_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME024_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME023		(BIT23)
	#define		ECM_ECMDTMCFG0_DTME023_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME023_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME022		(BIT22)
	#define		ECM_ECMDTMCFG0_DTME022_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME022_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME021		(BIT21)
	#define		ECM_ECMDTMCFG0_DTME021_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME021_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME020		(BIT20)
	#define		ECM_ECMDTMCFG0_DTME020_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME020_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME019		(BIT19)
	#define		ECM_ECMDTMCFG0_DTME019_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME019_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME018		(BIT18)
	#define		ECM_ECMDTMCFG0_DTME018_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME018_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME017		(BIT17)
	#define		ECM_ECMDTMCFG0_DTME017_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME017_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME016		(BIT16)
	#define		ECM_ECMDTMCFG0_DTME016_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME016_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME015		(BIT15)
	#define		ECM_ECMDTMCFG0_DTME015_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME015_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME014		(BIT14)
	#define		ECM_ECMDTMCFG0_DTME014_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME014_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME013		(BIT13)
	#define		ECM_ECMDTMCFG0_DTME013_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME013_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME012		(BIT12)
	#define		ECM_ECMDTMCFG0_DTME012_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME012_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME011		(BIT11)
	#define		ECM_ECMDTMCFG0_DTME011_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME011_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME010		(BIT10)
	#define		ECM_ECMDTMCFG0_DTME010_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME010_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME009		(BIT9)
	#define		ECM_ECMDTMCFG0_DTME009_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME009_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME008		(BIT8)
	#define		ECM_ECMDTMCFG0_DTME008_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME008_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME007		(BIT7)
	#define		ECM_ECMDTMCFG0_DTME007_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME007_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME006		(BIT6)
	#define		ECM_ECMDTMCFG0_DTME006_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME006_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME005		(BIT5)
	#define		ECM_ECMDTMCFG0_DTME005_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME005_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME004		(BIT4)
	#define		ECM_ECMDTMCFG0_DTME004_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME004_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME003		(BIT3)
	#define		ECM_ECMDTMCFG0_DTME003_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME003_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME002		(BIT2)
	#define		ECM_ECMDTMCFG0_DTME002_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME002_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME001		(BIT1)
	#define		ECM_ECMDTMCFG0_DTME001_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME001_ENABLE		(1)
#define		ECM_ECMDTMCFG0_DTME000		(BIT0)
	#define		ECM_ECMDTMCFG0_DTME000_DISABLE	(0)
	#define		ECM_ECMDTMCFG0_DTME000_ENABLE		(1)

/* ECMDTMCFG1 */
#define		ECM_ECMDTMCFG1_DTME063		(BIT31)
	#define		ECM_ECMDTMCFG1_DTME063_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME063_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME062		(BIT30)
	#define		ECM_ECMDTMCFG1_DTME062_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME062_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME061		(BIT29)
	#define		ECM_ECMDTMCFG1_DTME061_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME061_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME060		(BIT28)
	#define		ECM_ECMDTMCFG1_DTME060_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME060_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME059		(BIT27)
	#define		ECM_ECMDTMCFG1_DTME059_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME059_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME058		(BIT26)
	#define		ECM_ECMDTMCFG1_DTME058_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME058_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME057		(BIT25)
	#define		ECM_ECMDTMCFG1_DTME057_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME057_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME056		(BIT24)
	#define		ECM_ECMDTMCFG1_DTME056_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME056_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME055		(BIT23)
	#define		ECM_ECMDTMCFG1_DTME055_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME055_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME054		(BIT22)
	#define		ECM_ECMDTMCFG1_DTME054_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME054_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME053		(BIT21)
	#define		ECM_ECMDTMCFG1_DTME053_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME053_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME052		(BIT20)
	#define		ECM_ECMDTMCFG1_DTME052_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME052_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME051		(BIT19)
	#define		ECM_ECMDTMCFG1_DTME051_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME051_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME050		(BIT18)
	#define		ECM_ECMDTMCFG1_DTME050_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME050_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME049		(BIT17)
	#define		ECM_ECMDTMCFG1_DTME049_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME049_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME048		(BIT16)
	#define		ECM_ECMDTMCFG1_DTME048_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME048_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME047		(BIT15)
	#define		ECM_ECMDTMCFG1_DTME047_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME047_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME046		(BIT14)
	#define		ECM_ECMDTMCFG1_DTME046_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME046_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME045		(BIT13)
	#define		ECM_ECMDTMCFG1_DTME045_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME045_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME044		(BIT12)
	#define		ECM_ECMDTMCFG1_DTME044_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME044_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME043		(BIT11)
	#define		ECM_ECMDTMCFG1_DTME043_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME043_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME042		(BIT10)
	#define		ECM_ECMDTMCFG1_DTME042_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME042_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME041		(BIT9)
	#define		ECM_ECMDTMCFG1_DTME041_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME041_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME040		(BIT8)
	#define		ECM_ECMDTMCFG1_DTME040_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME040_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME039		(BIT7)
	#define		ECM_ECMDTMCFG1_DTME039_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME039_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME038		(BIT6)
	#define		ECM_ECMDTMCFG1_DTME038_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME038_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME037		(BIT5)
	#define		ECM_ECMDTMCFG1_DTME037_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME037_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME036		(BIT4)
	#define		ECM_ECMDTMCFG1_DTME036_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME036_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME035		(BIT3)
	#define		ECM_ECMDTMCFG1_DTME035_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME035_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME034		(BIT2)
	#define		ECM_ECMDTMCFG1_DTME034_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME034_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME033		(BIT1)
	#define		ECM_ECMDTMCFG1_DTME033_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME033_ENABLE		(1)
#define		ECM_ECMDTMCFG1_DTME032		(BIT0)
	#define		ECM_ECMDTMCFG1_DTME032_DISABLE	(0)
	#define		ECM_ECMDTMCFG1_DTME032_ENABLE		(1)

/* ECMDTMCFG2 */
#define		ECM_ECMDTMCFG2_DTME095		(BIT31)
	#define		ECM_ECMDTMCFG2_DTME095_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME095_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME094		(BIT30)
	#define		ECM_ECMDTMCFG2_DTME094_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME094_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME093		(BIT29)
	#define		ECM_ECMDTMCFG2_DTME093_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME093_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME092		(BIT28)
	#define		ECM_ECMDTMCFG2_DTME092_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME092_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME091		(BIT27)
	#define		ECM_ECMDTMCFG2_DTME091_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME091_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME090		(BIT26)
	#define		ECM_ECMDTMCFG2_DTME090_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME090_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME089		(BIT25)
	#define		ECM_ECMDTMCFG2_DTME089_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME089_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME088		(BIT24)
	#define		ECM_ECMDTMCFG2_DTME088_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME088_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME087		(BIT23)
	#define		ECM_ECMDTMCFG2_DTME087_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME087_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME086		(BIT22)
	#define		ECM_ECMDTMCFG2_DTME086_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME086_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME085		(BIT21)
	#define		ECM_ECMDTMCFG2_DTME085_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME085_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME084		(BIT20)
	#define		ECM_ECMDTMCFG2_DTME084_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME084_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME083		(BIT19)
	#define		ECM_ECMDTMCFG2_DTME083_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME083_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME082		(BIT18)
	#define		ECM_ECMDTMCFG2_DTME082_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME082_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME081		(BIT17)
	#define		ECM_ECMDTMCFG2_DTME081_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME081_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME080		(BIT16)
	#define		ECM_ECMDTMCFG2_DTME080_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME080_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME079		(BIT15)
	#define		ECM_ECMDTMCFG2_DTME079_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME079_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME078		(BIT14)
	#define		ECM_ECMDTMCFG2_DTME078_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME078_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME077		(BIT13)
	#define		ECM_ECMDTMCFG2_DTME077_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME077_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME076		(BIT12)
	#define		ECM_ECMDTMCFG2_DTME076_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME076_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME075		(BIT11)
	#define		ECM_ECMDTMCFG2_DTME075_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME075_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME074		(BIT10)
	#define		ECM_ECMDTMCFG2_DTME074_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME074_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME073		(BIT9)
	#define		ECM_ECMDTMCFG2_DTME073_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME073_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME072		(BIT8)
	#define		ECM_ECMDTMCFG2_DTME072_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME072_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME071		(BIT7)
	#define		ECM_ECMDTMCFG2_DTME071_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME071_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME070		(BIT6)
	#define		ECM_ECMDTMCFG2_DTME070_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME070_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME069		(BIT5)
	#define		ECM_ECMDTMCFG2_DTME069_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME069_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME068		(BIT4)
	#define		ECM_ECMDTMCFG2_DTME068_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME068_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME067		(BIT3)
	#define		ECM_ECMDTMCFG2_DTME067_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME067_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME066		(BIT2)
	#define		ECM_ECMDTMCFG2_DTME066_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME066_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME065		(BIT1)
	#define		ECM_ECMDTMCFG2_DTME065_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME065_ENABLE		(1)
#define		ECM_ECMDTMCFG2_DTME064		(BIT0)
	#define		ECM_ECMDTMCFG2_DTME064_DISABLE	(0)
	#define		ECM_ECMDTMCFG2_DTME064_ENABLE		(1)

/* ECMDTMCFG3 */
#define		ECM_ECMDTMCFG3_DTME127		(BIT31)
	#define		ECM_ECMDTMCFG3_DTME127_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME127_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME126		(BIT30)
	#define		ECM_ECMDTMCFG3_DTME126_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME126_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME125		(BIT29)
	#define		ECM_ECMDTMCFG3_DTME125_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME125_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME124		(BIT28)
	#define		ECM_ECMDTMCFG3_DTME124_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME124_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME123		(BIT27)
	#define		ECM_ECMDTMCFG3_DTME123_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME123_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME122		(BIT26)
	#define		ECM_ECMDTMCFG3_DTME122_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME122_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME121		(BIT25)
	#define		ECM_ECMDTMCFG3_DTME121_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME121_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME120		(BIT24)
	#define		ECM_ECMDTMCFG3_DTME120_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME120_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME119		(BIT23)
	#define		ECM_ECMDTMCFG3_DTME119_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME119_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME118		(BIT22)
	#define		ECM_ECMDTMCFG3_DTME118_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME118_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME117		(BIT21)
	#define		ECM_ECMDTMCFG3_DTME117_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME117_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME116		(BIT20)
	#define		ECM_ECMDTMCFG3_DTME116_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME116_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME115		(BIT19)
	#define		ECM_ECMDTMCFG3_DTME115_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME115_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME114		(BIT18)
	#define		ECM_ECMDTMCFG3_DTME114_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME114_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME113		(BIT17)
	#define		ECM_ECMDTMCFG3_DTME113_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME113_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME112		(BIT16)
	#define		ECM_ECMDTMCFG3_DTME112_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME112_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME111		(BIT15)
	#define		ECM_ECMDTMCFG3_DTME111_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME111_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME110		(BIT14)
	#define		ECM_ECMDTMCFG3_DTME110_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME110_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME109		(BIT13)
	#define		ECM_ECMDTMCFG3_DTME109_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME109_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME108		(BIT12)
	#define		ECM_ECMDTMCFG3_DTME108_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME108_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME107		(BIT11)
	#define		ECM_ECMDTMCFG3_DTME107_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME107_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME106		(BIT10)
	#define		ECM_ECMDTMCFG3_DTME106_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME106_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME105		(BIT9)
	#define		ECM_ECMDTMCFG3_DTME105_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME105_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME104		(BIT8)
	#define		ECM_ECMDTMCFG3_DTME104_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME104_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME103		(BIT7)
	#define		ECM_ECMDTMCFG3_DTME103_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME103_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME102		(BIT6)
	#define		ECM_ECMDTMCFG3_DTME102_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME102_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME101		(BIT5)
	#define		ECM_ECMDTMCFG3_DTME101_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME101_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME100		(BIT4)
	#define		ECM_ECMDTMCFG3_DTME100_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME100_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME099		(BIT3)
	#define		ECM_ECMDTMCFG3_DTME099_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME099_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME098		(BIT2)
	#define		ECM_ECMDTMCFG3_DTME098_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME098_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME097		(BIT1)
	#define		ECM_ECMDTMCFG3_DTME097_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME097_ENABLE		(1)
#define		ECM_ECMDTMCFG3_DTME096		(BIT0)
	#define		ECM_ECMDTMCFG3_DTME096_DISABLE	(0)
	#define		ECM_ECMDTMCFG3_DTME096_ENABLE		(1)

/* ECMDTMCFG4 */
#define		ECM_ECMDTMCFG4_DTME159		(BIT31)
	#define		ECM_ECMDTMCFG4_DTME159_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME159_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME158		(BIT30)
	#define		ECM_ECMDTMCFG4_DTME158_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME158_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME157		(BIT29)
	#define		ECM_ECMDTMCFG4_DTME157_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME157_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME156		(BIT28)
	#define		ECM_ECMDTMCFG4_DTME156_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME156_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME155		(BIT27)
	#define		ECM_ECMDTMCFG4_DTME155_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME155_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME154		(BIT26)
	#define		ECM_ECMDTMCFG4_DTME154_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME154_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME153		(BIT25)
	#define		ECM_ECMDTMCFG4_DTME153_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME153_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME152		(BIT24)
	#define		ECM_ECMDTMCFG4_DTME152_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME152_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME151		(BIT23)
	#define		ECM_ECMDTMCFG4_DTME151_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME151_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME150		(BIT22)
	#define		ECM_ECMDTMCFG4_DTME150_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME150_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME149		(BIT21)
	#define		ECM_ECMDTMCFG4_DTME149_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME149_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME148		(BIT20)
	#define		ECM_ECMDTMCFG4_DTME148_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME148_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME147		(BIT19)
	#define		ECM_ECMDTMCFG4_DTME147_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME147_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME146		(BIT18)
	#define		ECM_ECMDTMCFG4_DTME146_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME146_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME145		(BIT17)
	#define		ECM_ECMDTMCFG4_DTME145_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME145_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME144		(BIT16)
	#define		ECM_ECMDTMCFG4_DTME144_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME144_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME143		(BIT15)
	#define		ECM_ECMDTMCFG4_DTME143_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME143_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME142		(BIT14)
	#define		ECM_ECMDTMCFG4_DTME142_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME142_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME141		(BIT13)
	#define		ECM_ECMDTMCFG4_DTME141_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME141_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME140		(BIT12)
	#define		ECM_ECMDTMCFG4_DTME140_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME140_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME139		(BIT11)
	#define		ECM_ECMDTMCFG4_DTME139_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME139_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME138		(BIT10)
	#define		ECM_ECMDTMCFG4_DTME138_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME138_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME137		(BIT9)
	#define		ECM_ECMDTMCFG4_DTME137_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME137_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME136		(BIT8)
	#define		ECM_ECMDTMCFG4_DTME136_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME136_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME135		(BIT7)
	#define		ECM_ECMDTMCFG4_DTME135_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME135_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME134		(BIT6)
	#define		ECM_ECMDTMCFG4_DTME134_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME134_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME133		(BIT5)
	#define		ECM_ECMDTMCFG4_DTME133_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME133_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME132		(BIT4)
	#define		ECM_ECMDTMCFG4_DTME132_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME132_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME131		(BIT3)
	#define		ECM_ECMDTMCFG4_DTME131_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME131_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME130		(BIT2)
	#define		ECM_ECMDTMCFG4_DTME130_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME130_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME129		(BIT1)
	#define		ECM_ECMDTMCFG4_DTME129_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME129_ENABLE		(1)
#define		ECM_ECMDTMCFG4_DTME128		(BIT0)
	#define		ECM_ECMDTMCFG4_DTME128_DISABLE	(0)
	#define		ECM_ECMDTMCFG4_DTME128_ENABLE		(1)

/* ECMDTMCFG5 */
#define		ECM_ECMDTMCFG5_DTME191		(BIT31)
	#define		ECM_ECMDTMCFG5_DTME191_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME191_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME190		(BIT30)
	#define		ECM_ECMDTMCFG5_DTME190_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME190_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME189		(BIT29)
	#define		ECM_ECMDTMCFG5_DTME189_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME189_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME188		(BIT28)
	#define		ECM_ECMDTMCFG5_DTME188_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME188_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME187		(BIT27)
	#define		ECM_ECMDTMCFG5_DTME187_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME187_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME186		(BIT26)
	#define		ECM_ECMDTMCFG5_DTME186_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME186_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME185		(BIT25)
	#define		ECM_ECMDTMCFG5_DTME185_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME185_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME184		(BIT24)
	#define		ECM_ECMDTMCFG5_DTME184_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME184_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME183		(BIT23)
	#define		ECM_ECMDTMCFG5_DTME183_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME183_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME182		(BIT22)
	#define		ECM_ECMDTMCFG5_DTME182_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME182_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME181		(BIT21)
	#define		ECM_ECMDTMCFG5_DTME181_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME181_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME180		(BIT20)
	#define		ECM_ECMDTMCFG5_DTME180_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME180_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME179		(BIT19)
	#define		ECM_ECMDTMCFG5_DTME179_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME179_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME178		(BIT18)
	#define		ECM_ECMDTMCFG5_DTME178_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME178_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME177		(BIT17)
	#define		ECM_ECMDTMCFG5_DTME177_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME177_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME176		(BIT16)
	#define		ECM_ECMDTMCFG5_DTME176_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME176_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME175		(BIT15)
	#define		ECM_ECMDTMCFG5_DTME175_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME175_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME174		(BIT14)
	#define		ECM_ECMDTMCFG5_DTME174_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME174_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME173		(BIT13)
	#define		ECM_ECMDTMCFG5_DTME173_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME173_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME172		(BIT12)
	#define		ECM_ECMDTMCFG5_DTME172_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME172_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME171		(BIT11)
	#define		ECM_ECMDTMCFG5_DTME171_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME171_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME170		(BIT10)
	#define		ECM_ECMDTMCFG5_DTME170_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME170_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME169		(BIT9)
	#define		ECM_ECMDTMCFG5_DTME169_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME169_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME168		(BIT8)
	#define		ECM_ECMDTMCFG5_DTME168_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME168_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME167		(BIT7)
	#define		ECM_ECMDTMCFG5_DTME167_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME167_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME166		(BIT6)
	#define		ECM_ECMDTMCFG5_DTME166_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME166_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME165		(BIT5)
	#define		ECM_ECMDTMCFG5_DTME165_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME165_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME164		(BIT4)
	#define		ECM_ECMDTMCFG5_DTME164_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME164_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME163		(BIT3)
	#define		ECM_ECMDTMCFG5_DTME163_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME163_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME162		(BIT2)
	#define		ECM_ECMDTMCFG5_DTME162_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME162_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME161		(BIT1)
	#define		ECM_ECMDTMCFG5_DTME161_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME161_ENABLE		(1)
#define		ECM_ECMDTMCFG5_DTME160		(BIT0)
	#define		ECM_ECMDTMCFG5_DTME160_DISABLE	(0)
	#define		ECM_ECMDTMCFG5_DTME160_ENABLE		(1)

/* ECMDTMCFG6 */
#define		ECM_ECMDTMCFG6_DTME223		(BIT31)
	#define		ECM_ECMDTMCFG6_DTME223_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME223_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME222		(BIT30)
	#define		ECM_ECMDTMCFG6_DTME222_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME222_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME221		(BIT29)
	#define		ECM_ECMDTMCFG6_DTME221_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME221_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME220		(BIT28)
	#define		ECM_ECMDTMCFG6_DTME220_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME220_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME219		(BIT27)
	#define		ECM_ECMDTMCFG6_DTME219_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME219_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME218		(BIT26)
	#define		ECM_ECMDTMCFG6_DTME218_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME218_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME217		(BIT25)
	#define		ECM_ECMDTMCFG6_DTME217_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME217_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME216		(BIT24)
	#define		ECM_ECMDTMCFG6_DTME216_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME216_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME215		(BIT23)
	#define		ECM_ECMDTMCFG6_DTME215_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME215_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME214		(BIT22)
	#define		ECM_ECMDTMCFG6_DTME214_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME214_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME213		(BIT21)
	#define		ECM_ECMDTMCFG6_DTME213_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME213_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME212		(BIT20)
	#define		ECM_ECMDTMCFG6_DTME212_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME212_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME211		(BIT19)
	#define		ECM_ECMDTMCFG6_DTME211_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME211_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME210		(BIT18)
	#define		ECM_ECMDTMCFG6_DTME210_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME210_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME209		(BIT17)
	#define		ECM_ECMDTMCFG6_DTME209_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME209_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME208		(BIT16)
	#define		ECM_ECMDTMCFG6_DTME208_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME208_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME207		(BIT15)
	#define		ECM_ECMDTMCFG6_DTME207_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME207_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME206		(BIT14)
	#define		ECM_ECMDTMCFG6_DTME206_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME206_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME205		(BIT13)
	#define		ECM_ECMDTMCFG6_DTME205_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME205_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME204		(BIT12)
	#define		ECM_ECMDTMCFG6_DTME204_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME204_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME203		(BIT11)
	#define		ECM_ECMDTMCFG6_DTME203_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME203_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME202		(BIT10)
	#define		ECM_ECMDTMCFG6_DTME202_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME202_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME201		(BIT9)
	#define		ECM_ECMDTMCFG6_DTME201_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME201_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME200		(BIT8)
	#define		ECM_ECMDTMCFG6_DTME200_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME200_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME199		(BIT7)
	#define		ECM_ECMDTMCFG6_DTME199_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME199_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME198		(BIT6)
	#define		ECM_ECMDTMCFG6_DTME198_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME198_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME197		(BIT5)
	#define		ECM_ECMDTMCFG6_DTME197_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME197_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME196		(BIT4)
	#define		ECM_ECMDTMCFG6_DTME196_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME196_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME195		(BIT3)
	#define		ECM_ECMDTMCFG6_DTME195_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME195_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME194		(BIT2)
	#define		ECM_ECMDTMCFG6_DTME194_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME194_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME193		(BIT1)
	#define		ECM_ECMDTMCFG6_DTME193_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME193_ENABLE		(1)
#define		ECM_ECMDTMCFG6_DTME192		(BIT0)
	#define		ECM_ECMDTMCFG6_DTME192_DISABLE	(0)
	#define		ECM_ECMDTMCFG6_DTME192_ENABLE		(1)

/* ECMDTMCFG7 */
#define		ECM_ECMDTMCFG7_DTME255		(BIT31)
	#define		ECM_ECMDTMCFG7_DTME255_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME255_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME254		(BIT30)
	#define		ECM_ECMDTMCFG7_DTME254_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME254_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME253		(BIT29)
	#define		ECM_ECMDTMCFG7_DTME253_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME253_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME252		(BIT28)
	#define		ECM_ECMDTMCFG7_DTME252_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME252_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME251		(BIT27)
	#define		ECM_ECMDTMCFG7_DTME251_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME251_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME250		(BIT26)
	#define		ECM_ECMDTMCFG7_DTME250_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME250_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME249		(BIT25)
	#define		ECM_ECMDTMCFG7_DTME249_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME249_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME248		(BIT24)
	#define		ECM_ECMDTMCFG7_DTME248_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME248_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME247		(BIT23)
	#define		ECM_ECMDTMCFG7_DTME247_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME247_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME246		(BIT22)
	#define		ECM_ECMDTMCFG7_DTME246_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME246_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME245		(BIT21)
	#define		ECM_ECMDTMCFG7_DTME245_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME245_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME244		(BIT20)
	#define		ECM_ECMDTMCFG7_DTME244_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME244_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME243		(BIT19)
	#define		ECM_ECMDTMCFG7_DTME243_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME243_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME242		(BIT18)
	#define		ECM_ECMDTMCFG7_DTME242_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME242_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME241		(BIT17)
	#define		ECM_ECMDTMCFG7_DTME241_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME241_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME240		(BIT16)
	#define		ECM_ECMDTMCFG7_DTME240_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME240_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME239		(BIT15)
	#define		ECM_ECMDTMCFG7_DTME239_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME239_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME238		(BIT14)
	#define		ECM_ECMDTMCFG7_DTME238_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME238_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME237		(BIT13)
	#define		ECM_ECMDTMCFG7_DTME237_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME237_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME236		(BIT12)
	#define		ECM_ECMDTMCFG7_DTME236_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME236_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME235		(BIT11)
	#define		ECM_ECMDTMCFG7_DTME235_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME235_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME234		(BIT10)
	#define		ECM_ECMDTMCFG7_DTME234_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME234_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME233		(BIT9)
	#define		ECM_ECMDTMCFG7_DTME233_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME233_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME232		(BIT8)
	#define		ECM_ECMDTMCFG7_DTME232_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME232_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME231		(BIT7)
	#define		ECM_ECMDTMCFG7_DTME231_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME231_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME230		(BIT6)
	#define		ECM_ECMDTMCFG7_DTME230_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME230_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME229		(BIT5)
	#define		ECM_ECMDTMCFG7_DTME229_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME229_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME228		(BIT4)
	#define		ECM_ECMDTMCFG7_DTME228_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME228_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME227		(BIT3)
	#define		ECM_ECMDTMCFG7_DTME227_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME227_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME226		(BIT2)
	#define		ECM_ECMDTMCFG7_DTME226_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME226_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME225		(BIT1)
	#define		ECM_ECMDTMCFG7_DTME225_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME225_ENABLE		(1)
#define		ECM_ECMDTMCFG7_DTME224		(BIT0)
	#define		ECM_ECMDTMCFG7_DTME224_DISABLE	(0)
	#define		ECM_ECMDTMCFG7_DTME224_ENABLE		(1)

/* ECMDTMCFG8 */
#define		ECM_ECMDTMCFG8_DTME287		(BIT31)
	#define		ECM_ECMDTMCFG8_DTME287_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME287_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME286		(BIT30)
	#define		ECM_ECMDTMCFG8_DTME286_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME286_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME285		(BIT29)
	#define		ECM_ECMDTMCFG8_DTME285_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME285_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME284		(BIT28)
	#define		ECM_ECMDTMCFG8_DTME284_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME284_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME283		(BIT27)
	#define		ECM_ECMDTMCFG8_DTME283_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME283_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME282		(BIT26)
	#define		ECM_ECMDTMCFG8_DTME282_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME282_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME281		(BIT25)
	#define		ECM_ECMDTMCFG8_DTME281_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME281_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME280		(BIT24)
	#define		ECM_ECMDTMCFG8_DTME280_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME280_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME279		(BIT23)
	#define		ECM_ECMDTMCFG8_DTME279_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME279_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME278		(BIT22)
	#define		ECM_ECMDTMCFG8_DTME278_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME278_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME277		(BIT21)
	#define		ECM_ECMDTMCFG8_DTME277_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME277_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME276		(BIT20)
	#define		ECM_ECMDTMCFG8_DTME276_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME276_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME275		(BIT19)
	#define		ECM_ECMDTMCFG8_DTME275_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME275_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME274		(BIT18)
	#define		ECM_ECMDTMCFG8_DTME274_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME274_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME273		(BIT17)
	#define		ECM_ECMDTMCFG8_DTME273_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME273_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME272		(BIT16)
	#define		ECM_ECMDTMCFG8_DTME272_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME272_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME271		(BIT15)
	#define		ECM_ECMDTMCFG8_DTME271_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME271_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME270		(BIT14)
	#define		ECM_ECMDTMCFG8_DTME270_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME270_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME269		(BIT13)
	#define		ECM_ECMDTMCFG8_DTME269_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME269_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME268		(BIT12)
	#define		ECM_ECMDTMCFG8_DTME268_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME268_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME267		(BIT11)
	#define		ECM_ECMDTMCFG8_DTME267_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME267_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME266		(BIT10)
	#define		ECM_ECMDTMCFG8_DTME266_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME266_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME265		(BIT9)
	#define		ECM_ECMDTMCFG8_DTME265_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME265_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME264		(BIT8)
	#define		ECM_ECMDTMCFG8_DTME264_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME264_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME263		(BIT7)
	#define		ECM_ECMDTMCFG8_DTME263_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME263_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME262		(BIT6)
	#define		ECM_ECMDTMCFG8_DTME262_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME262_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME261		(BIT5)
	#define		ECM_ECMDTMCFG8_DTME261_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME261_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME260		(BIT4)
	#define		ECM_ECMDTMCFG8_DTME260_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME260_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME259		(BIT3)
	#define		ECM_ECMDTMCFG8_DTME259_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME259_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME258		(BIT2)
	#define		ECM_ECMDTMCFG8_DTME258_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME258_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME257		(BIT1)
	#define		ECM_ECMDTMCFG8_DTME257_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME257_ENABLE		(1)
#define		ECM_ECMDTMCFG8_DTME256		(BIT0)
	#define		ECM_ECMDTMCFG8_DTME256_DISABLE	(0)
	#define		ECM_ECMDTMCFG8_DTME256_ENABLE		(1)

/* ECMDTMCFG9 */
#define		ECM_ECMDTMCFG9_DTME319		(BIT31)
	#define		ECM_ECMDTMCFG9_DTME319_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME319_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME318		(BIT30)
	#define		ECM_ECMDTMCFG9_DTME318_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME318_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME317		(BIT29)
	#define		ECM_ECMDTMCFG9_DTME317_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME317_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME316		(BIT28)
	#define		ECM_ECMDTMCFG9_DTME316_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME316_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME315		(BIT27)
	#define		ECM_ECMDTMCFG9_DTME315_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME315_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME314		(BIT26)
	#define		ECM_ECMDTMCFG9_DTME314_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME314_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME313		(BIT25)
	#define		ECM_ECMDTMCFG9_DTME313_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME313_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME312		(BIT24)
	#define		ECM_ECMDTMCFG9_DTME312_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME312_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME311		(BIT23)
	#define		ECM_ECMDTMCFG9_DTME311_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME311_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME310		(BIT22)
	#define		ECM_ECMDTMCFG9_DTME310_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME310_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME309		(BIT21)
	#define		ECM_ECMDTMCFG9_DTME309_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME309_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME308		(BIT20)
	#define		ECM_ECMDTMCFG9_DTME308_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME308_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME307		(BIT19)
	#define		ECM_ECMDTMCFG9_DTME307_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME307_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME306		(BIT18)
	#define		ECM_ECMDTMCFG9_DTME306_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME306_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME305		(BIT17)
	#define		ECM_ECMDTMCFG9_DTME305_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME305_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME304		(BIT16)
	#define		ECM_ECMDTMCFG9_DTME304_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME304_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME303		(BIT15)
	#define		ECM_ECMDTMCFG9_DTME303_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME303_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME302		(BIT14)
	#define		ECM_ECMDTMCFG9_DTME302_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME302_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME301		(BIT13)
	#define		ECM_ECMDTMCFG9_DTME301_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME301_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME300		(BIT12)
	#define		ECM_ECMDTMCFG9_DTME300_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME300_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME299		(BIT11)
	#define		ECM_ECMDTMCFG9_DTME299_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME299_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME298		(BIT10)
	#define		ECM_ECMDTMCFG9_DTME298_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME298_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME297		(BIT9)
	#define		ECM_ECMDTMCFG9_DTME297_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME297_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME296		(BIT8)
	#define		ECM_ECMDTMCFG9_DTME296_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME296_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME295		(BIT7)
	#define		ECM_ECMDTMCFG9_DTME295_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME295_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME294		(BIT6)
	#define		ECM_ECMDTMCFG9_DTME294_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME294_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME293		(BIT5)
	#define		ECM_ECMDTMCFG9_DTME293_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME293_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME292		(BIT4)
	#define		ECM_ECMDTMCFG9_DTME292_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME292_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME291		(BIT3)
	#define		ECM_ECMDTMCFG9_DTME291_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME291_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME290		(BIT2)
	#define		ECM_ECMDTMCFG9_DTME290_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME290_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME289		(BIT1)
	#define		ECM_ECMDTMCFG9_DTME289_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME289_ENABLE		(1)
#define		ECM_ECMDTMCFG9_DTME288		(BIT0)
	#define		ECM_ECMDTMCFG9_DTME288_DISABLE	(0)
	#define		ECM_ECMDTMCFG9_DTME288_ENABLE		(1)

/* ECMDTMCFG10 */
#define		ECM_ECMDTMCFG10_DTME351		(BIT31)
	#define		ECM_ECMDTMCFG10_DTME351_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME351_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME350		(BIT30)
	#define		ECM_ECMDTMCFG10_DTME350_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME350_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME349		(BIT29)
	#define		ECM_ECMDTMCFG10_DTME349_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME349_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME348		(BIT28)
	#define		ECM_ECMDTMCFG10_DTME348_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME348_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME347		(BIT27)
	#define		ECM_ECMDTMCFG10_DTME347_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME347_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME346		(BIT26)
	#define		ECM_ECMDTMCFG10_DTME346_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME346_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME345		(BIT25)
	#define		ECM_ECMDTMCFG10_DTME345_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME345_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME344		(BIT24)
	#define		ECM_ECMDTMCFG10_DTME344_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME344_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME343		(BIT23)
	#define		ECM_ECMDTMCFG10_DTME343_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME343_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME342		(BIT22)
	#define		ECM_ECMDTMCFG10_DTME342_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME342_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME341		(BIT21)
	#define		ECM_ECMDTMCFG10_DTME341_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME341_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME340		(BIT20)
	#define		ECM_ECMDTMCFG10_DTME340_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME340_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME339		(BIT19)
	#define		ECM_ECMDTMCFG10_DTME339_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME339_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME338		(BIT18)
	#define		ECM_ECMDTMCFG10_DTME338_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME338_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME337		(BIT17)
	#define		ECM_ECMDTMCFG10_DTME337_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME337_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME336		(BIT16)
	#define		ECM_ECMDTMCFG10_DTME336_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME336_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME335		(BIT15)
	#define		ECM_ECMDTMCFG10_DTME335_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME335_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME334		(BIT14)
	#define		ECM_ECMDTMCFG10_DTME334_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME334_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME333		(BIT13)
	#define		ECM_ECMDTMCFG10_DTME333_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME333_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME332		(BIT12)
	#define		ECM_ECMDTMCFG10_DTME332_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME332_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME331		(BIT11)
	#define		ECM_ECMDTMCFG10_DTME331_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME331_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME330		(BIT10)
	#define		ECM_ECMDTMCFG10_DTME330_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME330_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME329		(BIT9)
	#define		ECM_ECMDTMCFG10_DTME329_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME329_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME328		(BIT8)
	#define		ECM_ECMDTMCFG10_DTME328_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME328_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME327		(BIT7)
	#define		ECM_ECMDTMCFG10_DTME327_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME327_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME326		(BIT6)
	#define		ECM_ECMDTMCFG10_DTME326_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME326_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME325		(BIT5)
	#define		ECM_ECMDTMCFG10_DTME325_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME325_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME324		(BIT4)
	#define		ECM_ECMDTMCFG10_DTME324_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME324_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME323		(BIT3)
	#define		ECM_ECMDTMCFG10_DTME323_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME323_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME322		(BIT2)
	#define		ECM_ECMDTMCFG10_DTME322_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME322_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME321		(BIT1)
	#define		ECM_ECMDTMCFG10_DTME321_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME321_ENABLE		(1)
#define		ECM_ECMDTMCFG10_DTME320		(BIT0)
	#define		ECM_ECMDTMCFG10_DTME320_DISABLE	(0)
	#define		ECM_ECMDTMCFG10_DTME320_ENABLE		(1)

/* ECMEOCCFG */
#define		ECM_ECMEOCCFG_EOCIEN		(BIT31)
	#define		ECM_ECMEOCCFG_EOCIEN_DISABLE	(0)
	#define		ECM_ECMEOCCFG_EOCIEN_ENABLE		(1)
#define		ECM_ECMEOCCFG_CMPW			(BIT24)
	#define		ECM_ECMEOCCFG_CMPW_NOEXECUTE	(0)
	#define		ECM_ECMEOCCFG_CMPW_EXECUTE		(1)
#define		ECM_ECMEOCCFG_ECMEOUTCLRT	(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* ECMETCCFG0 */
#define		ECM_ECMETCCFG0_ETCIEN		(BIT31)
	#define		ECM_ECMETCCFG0_ETCIEN_DISABLE	(0)
	#define		ECM_ECMETCCFG0_ETCIEN_ENABLE		(1)
#define		ECM_ECMETCCFG0_CMPW			(BIT24)
	#define		ECM_ECMETCCFG0_CMPW_NOEXECUTE	(0)
	#define		ECM_ECMETCCFG0_CMPW_EXECUTE		(1)
#define		ECM_ECMETCCFG0_ECMETRGCLRT	(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* ECMETCCFG1 */
#define		ECM_ECMETCCFG1_ETCIEN		(BIT31)
	#define		ECM_ECMETCCFG1_ETCIEN_DISABLE	(0)
	#define		ECM_ECMETCCFG1_ETCIEN_ENABLE		(1)
#define		ECM_ECMETCCFG1_CMPW			(BIT24)
	#define		ECM_ECMETCCFG1_CMPW_NOEXECUTE	(0)
	#define		ECM_ECMETCCFG1_CMPW_EXECUTE		(1)
#define		ECM_ECMETCCFG1_ECMETRGCLRT	(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* ECMETCCFG2 */
#define		ECM_ECMETCCFG2_ETCIEN		(BIT31)
	#define		ECM_ECMETCCFG2_ETCIEN_DISABLE	(0)
	#define		ECM_ECMETCCFG2_ETCIEN_ENABLE		(1)
#define		ECM_ECMETCCFG2_CMPW			(BIT24)
	#define		ECM_ECMETCCFG2_CMPW_NOEXECUTE	(0)
	#define		ECM_ECMETCCFG2_CMPW_EXECUTE		(1)
#define		ECM_ECMETCCFG2_ECMETRGCLRT	(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* ECMETCCFG3 */
#define		ECM_ECMETCCFG3_ETCIEN		(BIT31)
	#define		ECM_ECMETCCFG3_ETCIEN_DISABLE	(0)
	#define		ECM_ECMETCCFG3_ETCIEN_ENABLE		(1)
#define		ECM_ECMETCCFG3_CMPW			(BIT24)
	#define		ECM_ECMETCCFG3_CMPW_NOEXECUTE	(0)
	#define		ECM_ECMETCCFG3_CMPW_EXECUTE		(1)
#define		ECM_ECMETCCFG3_ECMETRGCLRT	(BIT23 + BIT22 + BIT21 + BIT20 + BIT19 + BIT18 + BIT17 + BIT16 + BIT15 + BIT14 + BIT13 + BIT12 + BIT11 + BIT10 + BIT9 + BIT8 + BIT7 + BIT6 + BIT5 + BIT4 + BIT3 + BIT2 + BIT1 + BIT0)

/* ECMPEM */
#define		ECM_ECMPEM_MSKM				(BIT1)
	#define		ECM_ECMPEM_MSKM_NOMASK			(0)
	#define		ECM_ECMPEM_MSKM_MASK			(1)
#define		ECM_ECMPEM_MSKC				(BIT0)
	#define		ECM_ECMPEM_MSKC_NOMASK			(0)
	#define		ECM_ECMPEM_MSKC_MASK			(1)


/*----------------------------------------------------------------------------------------------*/
/*	struct address definition																	*/
/*----------------------------------------------------------------------------------------------*/
#define		REG_ECMM			(*(volatile Reg_Ecm_EcmmType *)(0xFFD39000UL))
#define		REG_ECMC			(*(volatile Reg_Ecm_EcmmType *)(0xFFD3A000UL))
#define		REG_ECM				(*(volatile Reg_Ecm_EcmType  *)(0xFFD38000UL))


#endif /* REG_ECM_H */
/*-- End Of File -------------------------------------------------------------------------------*/
