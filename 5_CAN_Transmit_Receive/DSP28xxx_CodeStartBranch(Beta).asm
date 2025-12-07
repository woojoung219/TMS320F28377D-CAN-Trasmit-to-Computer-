;**********************************************************************
; 파일명		:	DSP28xxx_CodeStartBranch.asm
; 대상장치		:	TMS320F28X 프로세서
; 버전		:	1.10 (Beta)
; 갱신이력		:	2021-02-15, 버전 1.00, (TI 제공 코드)주석 한글화
;				2021-08-02, 버전 1.10, 일부 수정 (Beta)
;**********************************************************************

WD_DISABLE	.set	1		; [1 - 왓치독(Watchdog) 타이머 비-활성화] / [0 - 왓치독 타이머 활성화]

    .ref copy_sections
    .global code_start

***********************************************************************
* codestart 섹션 시작
***********************************************************************

    .sect "codestart"
    .retain

code_start:
    .if WD_DISABLE == 1
        LB wd_disable       ; 왓치독 타이머 비-활성화 코드로 분기
    .else
        LB copy_sections    ; 섹션 복사 코드로 분기 (DSP28xxx_SectionCopy_nonBIOS.asm)
    .endif

; codestart 끝.

***********************************************************************
* wddisable 섹션 시작 (왓치독 타이머 비-활성화 코드)
***********************************************************************
    .if WD_DISABLE == 1

    .sect "wddisable"
	.retain
	
wd_disable:
    SETC OBJMODE        ; ST1 레지스터의 OBJMODE 비트를 'C28x Mode'로 설정
    EALLOW              ; 중요 레지스터 보호 기능 해제
    MOVZ DP, #7029h>>6  ; WDCR 레지스터를 조작하기 위해 데이터 포인터 설정
    MOV @7029h, #0068h  ; WDCR 레지스터의 WDDIS 비트를 설정해서 왓치독 타이머 비-활성화
    EDIS                ; 중요 레지스터 보호 기능 재-설정
    LB copy_sections    ; 섹션 복사 코드로 분기 (DSP28xxx_SectionCopy_nonBIOS.asm)

    .endif

; wd_disable 끝.

	.end
	
; 파일 끝.
