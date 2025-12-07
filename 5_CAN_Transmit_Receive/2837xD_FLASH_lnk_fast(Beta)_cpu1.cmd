
MEMORY
{
PAGE 0 :	/* Program Memory */
			/* Memory (RAM/FLASH) blocks can be moved to PAGE1 for data allocation */
			/* BEGIN is used for the "boot to Flash" bootloader mode */

	BEGIN			: origin = 0x080000, length = 0x000002
	RAMM0			: origin = 0x000123, length = 0x0002DD
	RAMD0			: origin = 0x00B000, length = 0x000800
	RAMLS0_LS5		: origin = 0x008000, length = 0x003000
/*	RAMLS1			: origin = 0x008800, length = 0x000800
	RAMLS2			: origin = 0x009000, length = 0x000800
	RAMLS3			: origin = 0x009800, length = 0x000800
	RAMLS4			: origin = 0x00A000, length = 0x000800
	RAMLS5			: origin = 0x00A800, length = 0x000800 */
	
	RAMGS6_GS11		: origin = 0x012000, length = 0x005FF8
/*	RAMGS7			: origin = 0x013000, length = 0x001000
	RAMGS8			: origin = 0x014000, length = 0x001000
	RAMGS9			: origin = 0x015000, length = 0x001000
	RAMGS10			: origin = 0x016000, length = 0x001000
	RAMGS11         : origin = 0x017000, length = 0x000FF8 */	/* Uncomment for F28374D, F28376D devices */
																/* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
//	RAMGS11_RSVD    : origin = 0x017FF8, length = 0x000008  	/* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

	RESET			: origin = 0x3FFFC0, length = 0x000002

	/* Flash sectors */
	FLASHA			: origin = 0x080002, length = 0x001FFE
	FLASHBCD		: origin = 0x082000, length = 0x006000
/*	FLASHC			: origin = 0x084000, length = 0x002000
	FLASHD			: origin = 0x086000, length = 0x002000 */
	FLASHE			: origin = 0x088000, length = 0x008000
	FLASHF			: origin = 0x090000, length = 0x008000
	FLASHG			: origin = 0x098000, length = 0x008000
	FLASHH			: origin = 0x0A0000, length = 0x008000
	FLASHI			: origin = 0x0A8000, length = 0x008000
	FLASHJ			: origin = 0x0B0000, length = 0x008000
	FLASHK			: origin = 0x0B8000, length = 0x002000
	FLASHL			: origin = 0x0BA000, length = 0x002000
	FLASHM			: origin = 0x0BC000, length = 0x002000
	FLASHN			: origin = 0x0BE000, length = 0x001FF0
//	FLASHN_RSVD		: origin = 0x0BFFF0, length = 0x000010	/* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

PAGE 1 :	/* Data Memory */
			/* Memory (RAM/FLASH) blocks can be moved to PAGE0 for program allocation */

	BOOT_RSVD		: origin = 0x000002, length = 0x000121	/* Part of M0, BOOT rom will use this for stack */
	RAMM1			: origin = 0x000400, length = 0x0003F8	/* on-chip RAM block M1 */
//	RAMM1_RSVD		: origin = 0x0007F8, length = 0x000008	/* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
	RAMD1			: origin = 0x00B800, length = 0x000800

	RAMGS0			: origin = 0x00C000, length = 0x001000
	RAMGS1			: origin = 0x00D000, length = 0x001000
	RAMGS2			: origin = 0x00E000, length = 0x001000
	RAMGS3			: origin = 0x00F000, length = 0x001000
	RAMGS4			: origin = 0x010000, length = 0x001000
	RAMGS5			: origin = 0x011000, length = 0x001000

	RAMGS12         : origin = 0x018000, length = 0x001000  /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
	RAMGS13         : origin = 0x019000, length = 0x001000  /* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
	RAMGS14			: origin = 0x01A000, length = 0x001000	/* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
	RAMGS15			: origin = 0x01B000, length = 0x000FF8	/* Only Available on F28379D, F28377D, F28375D devices. Remove line on other devices. */
//	RAMGS15_RSVD	: origin = 0x01BFF8, length = 0x000008	/* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

	CPU2TOCPU1RAM	: origin = 0x03F800, length = 0x000400
	CPU1TOCPU2RAM	: origin = 0x03FC00, length = 0x000400
}

SECTIONS
{
	/*** User Defined Sections ***/
	codestart		: > BEGIN,			PAGE = 0, ALIGN(8)	/* Used by file CodeStartBranch.asm */
	wddisable		: > FLASHE,			PAGE = 0, ALIGN(8)
	copysections	: > FLASHE,			PAGE = 0, ALIGN(8)

#if defined(__TI_EABI__)

	rtslib { -l rts2800_fpu32_eabi.lib(.text) } > FLASHH, ALIGN(8)

	.cinit			:	LOAD = FLASHE,	PAGE = 0		/* can be FLASH */
	            		RUN = RAMD0,	PAGE = 0		/* must be CSM secured RAM */
	            		LOAD_START(cinit_loadstart),
	            		RUN_START(cinit_runstart),
	            		SIZE(cinit_size),
						ALIGN(8)
						
	.text			:	LOAD = FLASHBCD,	PAGE = 0	/* can be FLASH */
                		RUN = RAMGS6_GS11,	PAGE = 0	/* must be CSM secured RAM */
                		LOAD_START(text_loadstart),
                		RUN_START(text_runstart),
                		SIZE(text_size),
						ALIGN(8)

	.switch			:	LOAD = FLASHE,	PAGE = 0		/* can be FLASH */
						RUN = RAMD0,	PAGE = 0		/* must be CSM secured RAM */
						LOAD_START(switch_loadstart),
						RUN_START(switch_runstart),
						SIZE(switch_size),
						ALIGN(8)
#else
	.cinit			:	LOAD = FLASHE,	PAGE = 0		/* can be FLASH */
	            		RUN = RAMD0,	PAGE = 0		/* must be CSM secured RAM */
	            		LOAD_START(_cinit_loadstart),
	            		RUN_START(_cinit_runstart),
	            		SIZE(_cinit_size),
						ALIGN(8)
						
	.text			:	LOAD = FLASHBCD,	PAGE = 0	/* can be FLASH */
                		RUN = RAMGS6_GS11,	PAGE = 0	/* must be CSM secured RAM */
                		LOAD_START(_text_loadstart),
                		RUN_START(_text_runstart),
                		SIZE(_text_size),
						ALIGN(8)

	.switch			:	LOAD = FLASHE,	PAGE = 0		/* can be FLASH */
						RUN = RAMD0,	PAGE = 0		/* must be CSM secured RAM */
						LOAD_START(_switch_loadstart),
						RUN_START(_switch_runstart),
						SIZE(_switch_size),
						ALIGN(8)
#endif

	.stack				: > RAMM1,		PAGE = 1
	.reset				: > RESET,		PAGE = 0, TYPE = DSECT	/* not used */


#if defined(__TI_EABI__)
	.init_array			:	LOAD = FLASHE,	PAGE = 0			/* can be FLASH */
							RUN = RAMD0,	PAGE = 0			/* must be CSM secured RAM */
							LOAD_START(init_array_loadstart),
							RUN_START(init_array_runstart),
							SIZE(init_array_size),
							ALIGN(8)

	.bss				: > RAMGS0,		PAGE = 1
	.bss:output			: > RAMD0,		PAGE = 0
	.bss:cio			: > RAMGS0,		PAGE = 1
	.data				: > RAMGS0,		PAGE = 1
	.sysmem				: > RAMGS0,		PAGE = 1

	.const				:	LOAD = FLASHF,	PAGE = 0		/* can be FLASH */
							RUN = RAMGS0,	PAGE = 1		/* must be CSM secured RAM */
							LOAD_START(const_loadstart),
							RUN_START(const_runstart),
							SIZE(const_size),
							ALIGN(8)
#else
	.pinit				:	LOAD = FLASHE,	PAGE = 0		/* can be FLASH */
							RUN = RAMD0,	PAGE = 0		/* must be CSM secured RAM */
							LOAD_START(_pinit_loadstart),
							RUN_START(_pinit_runstart),
							SIZE(_pinit_size),
							ALIGN(8)

	.ebss				: > RAMGS0,			PAGE = 1
	.esysmem			: > RAMGS0,			PAGE = 1

	.econst				:	LOAD = FLASHF,					PAGE = 0	/* can be FLASH */
							RUN = RAMGS0,					PAGE = 1	/* must be CSM secured RAM */
							LOAD_START(_econst_loadstart),
							RUN_START(_econst_runstart),
							SIZE(_econst_size),
							ALIGN(8)
#endif

	Filter_RegsFile			: > RAMGS0,		PAGE = 1

	SHARERAMGS0				: > RAMGS0,		PAGE = 1
	SHARERAMGS1				: > RAMGS1,		PAGE = 1
	ramgs0					: > RAMGS0,		PAGE = 1
	ramgs1					: > RAMGS1,		PAGE = 1

#ifdef __TI_COMPILER_VERSION__
	#if __TI_COMPILER_VERSION__ >= 15009000
		#if defined(__TI_EABI__)
			.TI.ramfunc : {} LOAD = FLASHG,  	PAGE = 0        /* can be FLASH */
							 RUN = RAMD0, 		PAGE = 0        /* must be CSM secured RAM */
							 LOAD_START(ramfuncs_loadstart),
							 RUN_START(ramfuncs_runstart),
							 SIZE(ramfuncs_size),
							 ALIGN(8)
		#else
			.TI.ramfunc : {} LOAD = FLASHG,  	PAGE = 0        /* can be FLASH */
							 RUN = RAMD0, 		PAGE = 0        /* must be CSM secured RAM */
							 LOAD_START(_ramfuncs_loadstart),
							 RUN_START(_ramfuncs_runstart),
							 SIZE(_ramfuncs_size),
							 ALIGN(8)
		#endif
	#else
		ramfuncs		:	LOAD = FLASHG,  	PAGE = 0        /* can be FLASH */
							RUN = RAMD0, 		PAGE = 0        /* must be CSM secured RAM */
							LOAD_START(_ramfuncs_loadstart),
							RUN_START(_ramfuncs_runstart),
							SIZE(_ramfuncs_size),
							ALIGN(8)
	#endif
#endif

	/* The following section definitions are required when using the IPC API Drivers */
	GROUP	: > CPU1TOCPU2RAM,	PAGE = 1
	{
		PUTBUFFER
		PUTWRITEIDX
		GETREADIDX
	}

	GROUP	: > CPU2TOCPU1RAM,	PAGE = 1
	{
		GETBUFFER	:	TYPE = DSECT
		GETWRITEIDX	:	TYPE = DSECT
		PUTREADIDX	:	TYPE = DSECT
	}

	/* The following section definition are for SDFM examples */
	Filter1_RegsFile	: > RAMGS1,	PAGE = 1, fill=0x1111
	Filter2_RegsFile	: > RAMGS2,	PAGE = 1, fill=0x2222
	Filter3_RegsFile	: > RAMGS3,	PAGE = 1, fill=0x3333
	Filter4_RegsFile	: > RAMGS4,	PAGE = 1, fill=0x4444
	Difference_RegsFile	: > RAMGS5,	PAGE = 1, fill=0x3333
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
