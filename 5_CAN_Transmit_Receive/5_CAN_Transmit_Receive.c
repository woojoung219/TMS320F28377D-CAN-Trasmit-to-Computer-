// # TMS320F28377D-CAN-Trasmit-to-Computer-
//This is TMS320F28377D CAN Trasmit to Computer exmaple.(5_CAN_Transmit_Receive)
//
//1)driverlib를 활용하였습니다.
//2)CAN 메시지 하나당 8byte 데이터(txMsgData[8])를 전송합니다.CAN 메시지를 MSGCOUNT(8)번 전송합니다.
//3)CAN메시지 하나 전송 완료 후 CAN A Tx interrupt가 발생합니다.인터럽트 발생시 실행되는 CanaISR함수에서 데이터 송신 횟수 파악용 카운터 변수(txMsgCount)를 증가시키고 데이터 송신 진행도를 트레이닝 키트 Red LED 8개로 표시합니다.
//4)CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x15555555,
//CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
//CAN_MSG_OBJ_TX_INT_ENABLE, MSG_DATA_LENGTH); 에서 obejct id number와 msg id를 매핑합니ㅏㄷ.
//message identifier : CAN 메시지의 고유 ID입니다.실제 CAN 버스를 통해 전송되는 프레임의** ID 필드(11 - bit or 29 - bit)** 에 해당합니다.->0x15555555
//obejct id number : TI의 CAN 모듈 내부에 존재하는 메시지 객체 번호입니다.F28377D의 CAN 모듈은 최대 32개의 메시지 객체를 가질 수 있다.->TX_MSG_OBJ_ID(1)
//
//5) CAN통신 관련 인터럽트 종류
//CAN_INT_ERROR : 에러 인터럽트(에러 발생 시)),
//CAN_INT_STATUS	: 상태 변화 인터럽트(예 : bus - off, warning, 송신 실패 횟수 증가, 수신 오버런 등)
//CAN_INT_IE0 : 메시지 송수신 이벤트 발생 시 발생하는 인터럽트(IE0)
//
//HW 구성 : TR2837xD 트레이닝 키트 + CAN 통신 트랜시버(TCAN1044V)--연결--CAN 통신 트랜시버 + 컴퓨터
//
//* 싱크웍스의 TR2837xD 트레이닝 키트를 대상으로 한 5_CAN_Transmit_Receive예제를 참고하였습니다.
//
//
//************************************************************************************************************************************************************************


// 헤더 파일들
#include "F28x_Project.h"	// TI 제공 칩-지원 헤더 통합 Include 용 헤더파일 (bit-field)
#include "driverlib.h"		// TI 제공 Driver API Library 헤더파일 (driverlib)
#include "device.h"


// 전처리 구문 정의

// 본 예제가 실행되는 F2837xD 칩 기반 장치를 CAN 수신장치로 운용하려면, 아래의 'TRANSMIT' 전처리 구문을 주석으로 처리하세요.
#define TRANSMIT

#ifdef TRANSMIT
	#define TX_MSG_OBJ_ID	1	// CAN 모듈의 32개 메시지 오브젝트들 중 1번 MSG_OBJ를 TX용으로 사용
#else
	#define RX_MSG_OBJ_ID	1	// CAN 모듈의 32개 메시지 오브젝트들 중 1번 MSG_OBJ를 RX용으로 사용
#endif

#define MSG_DATA_LENGTH		8	// 테스트용 송수신 메시지 길이 (Bytes)
#define MSGCOUNT			8	// 테스트 데이터 송수신 횟수 (회)


// 함수 원형 선언
__interrupt void CanaISR(void);
void InitLedGpioPorts(void);


// 전역 변수 선언
#ifdef TRANSMIT
	volatile uint32_t txMsgCount = 0;
	uint32_t txMsgSuccessful = 1;
	uint16_t txMsgData[MSG_DATA_LENGTH];
#else
	volatile uint32_t rxMsgCount = MSGCOUNT;
	uint16_t rxMsgData[MSG_DATA_LENGTH];
#endif

volatile uint32_t i;
volatile uint32_t errorFlag = 0;

Uint32	errorCounter = 0;
Uint32	LedIndicator = 0;


// 메인 함수
void main(void)
{

	// 시스템 및 주변회로 클럭 설정
	Device_init();

	// GPIO 포트 초기화 및 CANA 모듈용 RX, TX 포트 설정
	Device_initGPIO();
	GPIO_setPinConfig(GPIO_70_CANRXA);
	GPIO_setPinConfig(GPIO_71_CANTXA);

	// 트레이닝 키트 LED 조작용 범용 입출력 포트(GPIO) 설정
	InitLedGpioPorts();

	// CAN 컨트롤러 초기화 (CANA)
	CAN_initModule(CANA_BASE);

	// CANA 모듈의 비트 전송률을 1000kHz로 설정
	CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 1000000, 20);

	// CANA 모듈의 인터럽트 활성화
	CAN_enableInterrupt(CANA_BASE, CAN_INT_IE0 | CAN_INT_ERROR | CAN_INT_STATUS);

	// 주변회로 인터럽트 확장 회로(PIE) 및 관련 레지스터 초기화 / CPU 인터럽트 비-활성화
	Interrupt_initModule();

	// PIE 벡터 테이블 초기화 및 기본 인터럽트 서비스 루틴 연결
	Interrupt_initVectorTable();

	// 실시간 디버깅 활성화, 전역 인터럽트 스위치 ON
	ERTM;	// Debug Enable Mask 비트 설정 (실시간 디버깅이 가능하도록 ST1 레지스터의 /DBGM 비트를 0으로 클리어)
	EINT;	// 전역 인터럽트 스위치 ON (/INTM ON)

	// 인터럽트 벡터와 인터럽트 서비스 루틴 재-연결, 인터럽트 벡터 활성화
	Interrupt_register(INT_CANA0, &CanaISR);	// INT_CANA0 인터럽트 벡터에 CanaISR( ) 함수 연결

	// CANA 모듈 인터럽트 활성화
    Interrupt_enable(INT_CANA0);

    // CANA 모듈 인터럽트 신호 라인 CANINT0 활성화
    CAN_enableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

#ifdef TRANSMIT
	// CAN 테스트 데이터를 송신하기 위한, 송신 메시지 오브젝트 초기화
	// 메시지 오브젝트 파라미터 설정 :
	// CAN 모듈 : A (CANA)
	// 메시지 오브젝트 선택 (Message Object ID Number) : 1
	// CAN 메시지 ID (Message Identifier) : 0x15555555
	// 메시지 프레임 (Message Frame) : 확장 CAN (Extended)
	// 메시지 타입 (Message Type) : 송신 (Transmit)
	// 메시지 ID 마스크 (Message ID Mask) : 0x0 (don't care / ID Mask를 설정하지 않음)
	// 메시지 오브젝트 설정 (Message Object Flags) : 송신 인터럽트 활성화 (Transmit Interrupt)
	// 메시지 데이터 길이 (Message Data Length) : 8 Bytes
	CAN_setupMessageObject(	CANA_BASE, TX_MSG_OBJ_ID, 0x15555555,
							CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
							CAN_MSG_OBJ_TX_INT_ENABLE, MSG_DATA_LENGTH	);

    // 테스트 송신할 데이터 버퍼 초기화 (txMsgData[ ])
	txMsgData[0] = 0x12;
	txMsgData[1] = 0x34;
	txMsgData[2] = 0x56;
	txMsgData[3] = 0x78;
	txMsgData[4] = 0x9A;
	txMsgData[5] = 0xBC;
	txMsgData[6] = 0xED;
	txMsgData[7] = 0xF0;
#else
	// CAN 테스트 데이터를 수신하기 위한, 수신 메시지 오브젝트 초기화
	// 메시지 오브젝트 파라미터 설정 :
	// CAN 모듈 : A (CANA)
	// 메시지 오브젝트 선택 (Message Object ID Number) : 1
	// CAN 메시지 ID (Message Identifier) : 0x15555555
	// 메시지 프레임 (Message Frame) : 확장 CAN (Extended)
	// 메시지 타입 (Message Type) : 수신 (Receive)
	// 메시지 ID 마스크 (Message ID Mask) : 0x0 (don't care / ID Mask를 설정하지 않음)
	// 메시지 오브젝트 설정 (Message Object Flags) : 수신 인터럽트 활성화 (Receive Interrupt)
	// 메시지 데이터 길이 (Message Data Length) : 8 Bytes (Note that DLC field is a "don't care" for a Receive mailbox)
	CAN_setupMessageObject(	CANA_BASE, RX_MSG_OBJ_ID, 0x15555555,
							CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0,
							CAN_MSG_OBJ_RX_INT_ENABLE, MSG_DATA_LENGTH	);
#endif

	// CAN-A 모듈 활성화 (Start operations)
	CAN_startModule(CANA_BASE);

#ifdef TRANSMIT
	// CAN-A 모듈을 이용해서 테스트 데이터 송신
	for(i = 0 ; i < MSGCOUNT ; i++)
	{
		// 오류 Flag 확인
		if(errorFlag)
		{
			asm("	ESTOP0"); // 에뮬레이션 정지 (Embedded Breakpoint)
		}

		// 테스트 데이터 송신 (Transmit Message)
		CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH, txMsgData);

		// 1초 지연 (1,000,000usec)
		DEVICE_DELAY_US(1000000L);

		while(txMsgSuccessful);

		// 송신 버퍼 값 갱신
		txMsgData[0] += 0x01;
		txMsgData[1] += 0x01;
		txMsgData[2] += 0x01;
		txMsgData[3] += 0x01;
		txMsgData[4] += 0x01;
		txMsgData[5] += 0x01;
		txMsgData[6] += 0x01;
		txMsgData[7] += 0x01;

		if(txMsgData[0] > 0xFF)
		{
			txMsgData[0] = 0;
		}
		if(txMsgData[1] > 0xFF)
		{
			txMsgData[1] = 0;
		}
		if(txMsgData[2] > 0xFF)
		{
			txMsgData[2] = 0;
		}
		if(txMsgData[3] > 0xFF)
		{
			txMsgData[3] = 0;
		}
		if(txMsgData[4] > 0xFF)
		{
			txMsgData[4] = 0;
		}
		if(txMsgData[5] > 0xFF)
		{
			txMsgData[5] = 0;
		}
		if(txMsgData[6] > 0xFF)
		{
			txMsgData[6] = 0;
		}
		if(txMsgData[7] > 0xFF)
		{
			txMsgData[7] = 0;
		}

		// 메시지 송신 완료 Flag Set
		txMsgSuccessful  = 1;
	}
#else
	// CAN 데이터 수신까지, 대기
	while(rxMsgCount)
	{
		asm("  NOP"); // No Operation
	}
#endif

	// 오류 발생 횟수에 따라, 트레이닝 키트 Green LED 상태 변경 (오류 없음 : Green LED ON)
	GpioDataRegs.GPADAT.bit.GPIO31 = (errorCounter > 0)? 0 : 1;

	// 테스트 데이터 송신(혹은 수신) 완료 후, 프로그램 정지 (Suspend, Embedded Breakpoint)
	asm("	ESTOP0");
	for(;;);
}


// FLASH 메모리에서 코드 실행 시, 램 영역으로 복사해서 고속 실행하도록 함
#ifdef _FLASH
	#pragma CODE_SECTION(CanaISR, ".TI.ramfunc");
#endif

__interrupt void CanaISR(void)
{
	uint32_t status;

	// 인터럽트 발생 원인을 파악하기 위해 CAN-A 모듈의 인터럽트 상태(Interrupt Status) 확인
	status = CAN_getInterruptCause(CANA_BASE);

	// (메시지 수신이 아닌) CAN 컨트롤러 상태 변화에 따른 인터럽트 발생이라면, 해당 상태 확인
	if(status == CAN_INT_INT0ID_STATUS)
	{
		// 컨트롤러 상태 확인 (Read the CAN controller status)
		// 본 예제에는 코드 복잡성을 피하기 위해 각 오류나 상태 변화에 따른 대응 코드는 포함되어 있지 않음
		status = CAN_getStatus(CANA_BASE);

		// 오류(Error)가 발생했는지 확인
#ifdef TRANSMIT
		if(	((status & ~(CAN_STATUS_TXOK)) != CAN_STATUS_LEC_MSK) && ((status & ~(CAN_STATUS_TXOK)) != CAN_STATUS_LEC_NONE))
#else
		if(	((status & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_MSK) && ((status & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_NONE))
#endif
		{
			// 오류가 발생했음을 알리기 위해 Flag 변수를 1로 설정하고 오류 발생 횟수 누적
			errorFlag = 1;
			errorCounter++;
		}
	}
#ifdef TRANSMIT
	else if(status == TX_MSG_OBJ_ID)
	{
		// 이곳에 프로그램 카운터가 위치했다는 것은, 메시지 오브젝트 1에 의한 TX 인터럽트가 발생했고, 이는 곧 테스트 메시지 송신(TX)이 완료되었음을 의미합니다.
		// Message Object interrupt Clear를 수행합니다.
		CAN_clearInterruptStatus(CANA_BASE, TX_MSG_OBJ_ID);

		// 테스트 데이터 송신 횟수 파악용 카운터 변수 증가
		txMsgCount++;

		// 테스트 데이터 송신 진행도를 트레이닝 키트 Red LED 8개로 표시
		GpioDataRegs.GPBCLEAR.all = 0x000000FF;
		LedIndicator = (0x000000FF & (0x000000FF <<txMsgCount));
		GpioDataRegs.GPBSET.all = LedIndicator;

		// 메시지 송신이 완료되었으므로, 오류 Flag Clear
		errorFlag = 0;

		// 메시지 송신 완료 Flag Clear
		txMsgSuccessful  = 0;
	}
#else
	else if(status == RX_MSG_OBJ_ID)
	{
		// 수신된 데이터 확인
		CAN_readMessage(CANA_BASE, RX_MSG_OBJ_ID, rxMsgData);

		// Message Object interrupt Clear
		CAN_clearInterruptStatus(CANA_BASE, RX_MSG_OBJ_ID);

		// 테스트 데이터 수신 횟수 파악용 카운터 변수 감소
		rxMsgCount--;
		
		// 테스트 데이터 수신 진행도를 트레이닝 키트 Red LED 8개로 표시
		GpioDataRegs.GPBCLEAR.all = 0x000000FF;
		LedIndicator = (0x000000FF & (0x000000FF >>rxMsgCount));
		GpioDataRegs.GPBSET.all = LedIndicator;

		// 메시지 수신이 완료되었으므로, 오류 Flag Clear
		errorFlag = 0;
	}
#endif
	// 예상되지 않은 일로 인터럽트 발생 시, 이곳에서 처리
	else
	{
		asm("  NOP"); // No Operation
	}

	// CAN 전역(Global) 인터럽트 Flag Clear
	CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

	// INT_CANA0 인터럽트 벡터가 포함된 CPU 인터럽트 확장그룹 9번의 Acknowledge 비트 클리어
	Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}


void InitLedGpioPorts(void)    // 트레이닝 키트 LED 조작용 GPIO 포트 초기화 함수
{
	EALLOW;

	// GPIO 31번을 범용 출력 포트로 설정 (트레이닝 키트 Green LED 제어용)
	GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;   // GPIO 31번을 범용 입출력 포트로 설정 (녹색 LED)
	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;     // GPIO 31번을 범용 출력 포트로 설정 (신호 방향 : 출력)
	GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;   // 녹색 LED OFF

	// 트레이닝 키트 범용 LED(8개) 제어용 GPIO 포트 초기화
	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;		// GPIO 32 ~ 39번의 내부 풀-업 비-활성화
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO35 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO37 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO38 = 1;
	GpioCtrlRegs.GPBPUD.bit.GPIO39 = 1;

	GpioCtrlRegs.GPBGMUX1.bit.GPIO32 = 0;	// GPIO 32 ~ 39번을 범용 입출력 포트로 설정
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO33 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO35 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO36 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO37 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO38 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;
	GpioCtrlRegs.GPBGMUX1.bit.GPIO39 = 0;
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;

	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;		// GPIO 32 ~ 39번을 범용 출력 포트로 설정
	GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO35 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO36 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO37 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO38 = 1;
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;

	EDIS;

#ifdef TRANSMIT
	GpioDataRegs.GPBSET.all = 0x000000FF;	// GPIO 32 ~ 39번의 상태를 모두 High 로 초기화
#else
	GpioDataRegs.GPBCLEAR.all = 0x000000FF;	// GPIO 32 ~ 39번의 상태를 모두 Low 로 초기화
#endif

}


// 파일 끝.
