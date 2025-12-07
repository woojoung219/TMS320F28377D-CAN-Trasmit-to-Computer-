;**********************************************************************
; 파일명		:	DSP28xxx_SectionCopy_nonBIOS.asm
; 대상장치		:	TMS320F28X 프로세서
; 버전		:	1.10 (Beta)
; 갱신이력		:	2021-02-15, 버전 1.00, (TI 제공 코드)주석 한글화, 일부 수정
;				2021-08-02, 버전 1.10, eabi(ELF) Output format 지원 관련 일부 수정 (Bata)
;**********************************************************************

		.ref _c_int00
	
	.if __TI_EABI__
		.asg cinit_loadstart, _cinit_loadstart
		.asg cinit_runstart, _cinit_runstart
		.asg cinit_size, _cinit_size
		.asg text_loadstart, _text_loadstart
		.asg text_runstart, _text_runstart
		.asg text_size, _text_size
		.asg switch_loadstart, _switch_loadstart
		.asg switch_runstart, _switch_runstart
		.asg switch_size, _switch_size
		.asg ramfuncs_loadstart, _ramfuncs_loadstart
		.asg ramfuncs_runstart, _ramfuncs_runstart
		.asg ramfuncs_size, _ramfuncs_size
		.asg init_array_loadstart, _init_array_loadstart
		.asg init_array_runstart, _init_array_runstart
		.asg init_array_size, _init_array_size
		.asg const_loadstart, _const_loadstart
		.asg const_runstart, _const_runstart
		.asg const_size, _const_size
	.endif
	
		.global copy_sections
		.global _cinit_loadstart, _cinit_runstart, _cinit_size
		.global _text_loadstart, _text_runstart, _text_size
		.global _switch_loadstart, _switch_runstart, _switch_size
		.global _ramfuncs_loadstart, _ramfuncs_runstart, _ramfuncs_size

	.if __TI_EABI__
		.global _init_array_loadstart, _init_array_runstart, _init_array_size
		.global _const_loadstart, _const_runstart, _const_size
	.else
		.global _pinit_loadstart, _pinit_runstart, _pinit_size
		.global _econst_loadstart, _econst_runstart, _econst_size
	.endif

	
***********************************************************************
* copysections 섹션 시작
* 플래시 메모리에 위치한 초기화(Initialized) 섹션들을 램으로 복사
***********************************************************************

	.sect "copysections"
	.retain

copy_sections:


	MOVL XAR5,#_cinit_size				; XAR5 레지스터에 복사할 섹션 크기 저장 - Store Section Size in XAR5
	MOVL ACC,@XAR5						; 어큐뮬레이터(ACC)에 복사할 섹션 크기 저장 - Move Section Size to ACC
	MOVL XAR6,#_cinit_loadstart			; 복사할 섹션의 시작 주소(플래시 메모리)를 XAR6 레지스터에 저장 - Store Load Starting Address in XAR6
	MOVL XAR7,#_cinit_runstart			; XAR7 레지스터에 섹션이 실행될 영역(램) 주소 저장 - Store Run Address in XAR7
	LCR  copy							; 섹션 복사 코드로 분기 - Branch to Copy

	MOVL XAR5,#_text_size               ; Store Section Size in XAR5
	MOVL ACC,@XAR5                      ; Move Section Size to ACC
	MOVL XAR6,#_text_loadstart          ; Store Load Starting Address in XAR6
	MOVL XAR7,#_text_runstart           ; Store Run Address in XAR7
	LCR  copy                           ; Branch to Copy

	.if __TI_EABI__
		MOVL XAR5,#_init_array_size			; Store Section Size in XAR5
		MOVL ACC,@XAR5						; Move Section Size to ACC
		MOVL XAR6,#_init_array_loadstart	; Store Load Starting Address in XAR6
		MOVL XAR7,#_init_array_runstart		; Store Run Address in XAR7
		LCR  copy							; Branch to Copy

		MOVL XAR5,#_const_size				; Store Section Size in XAR5
		MOVL ACC,@XAR5						; Move Section Size to ACC
		MOVL XAR6,#_const_loadstart			; Store Load Starting Address in XAR6
		MOVL XAR7,#_const_runstart			; Store Run Address in XAR7
		LCR  copy							; Branch to Copy
	.else
		MOVL XAR5,#_pinit_size				; Store Section Size in XAR5
		MOVL ACC,@XAR5						; Move Section Size to ACC
		MOVL XAR6,#_pinit_loadstart			; Store Load Starting Address in XAR6
		MOVL XAR7,#_pinit_runstart			; Store Run Address in XAR7
		LCR  copy							; Branch to Copy

		MOVL XAR5,#_econst_size				; Store Section Size in XAR5
		MOVL ACC,@XAR5						; Move Section Size to ACC
		MOVL XAR6,#_econst_loadstart		; Store Load Starting Address in XAR6
		MOVL XAR7,#_econst_runstart			; Store Run Address in XAR7
		LCR  copy							; Branch to Copy
	.endif

	MOVL XAR5,#_switch_size				; Store Section Size in XAR5
	MOVL ACC,@XAR5						; Move Section Size to ACC
	MOVL XAR6,#_switch_loadstart		; Store Load Starting Address in XAR6
	MOVL XAR7,#_switch_runstart			; Store Run Address in XAR7
	LCR  copy							; Branch to Copy

	MOVL XAR5,#_ramfuncs_size			; Store Section Size in XAR5
	MOVL ACC,@XAR5						; Move Section Size to ACC
	MOVL XAR6,#_ramfuncs_loadstart		; Store Load Starting Address in XAR6
	MOVL XAR7,#_ramfuncs_runstart		; Store Run Address in XAR7
	LCR  copy							; Branch to Copy

	   
	LB _c_int00				 			; Run-time Support(RTS) Library 코드 시작 위치로 분기 - Branch to start of boot.asm in RTS library

copy:	
	B return,EQ							; 어큘뮬레이터에 저장된 값이 0이 되면(복사할 섹션 내용이 없으면) Return - Return if ACC is Zero (No section to copy)

	SUBB ACC,#1

	RPT AL								; 섹션의 내용을 읽어서(플래시 메모리) 실행 영역(램)에 복사
	|| PWRITE  *XAR7, *XAR6++			; Copy Section From Load Address to Run Address

return:
	LRETR								; Return

; copysections 끝.

	.end
	
; 파일 끝.
