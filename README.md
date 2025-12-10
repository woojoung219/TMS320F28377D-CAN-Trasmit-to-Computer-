# TMS320F28377D-CAN-Trasmit-to-Computer-
This is TMS320F28377D CAN Trasmit to Computer exmaple.(5_CAN_Transmit_Receive)

1)driverlib를 활용하였습니다. 
2)CAN 메시지 하나당 8byte 데이터(txMsgData[8])를 전송합니다. CAN 메시지를 MSGCOUNT(8)번 전송합니다. 
3)CAN메시지 하나 전송 완료 후 CAN A Tx interrupt가 발생합니다.  인터럽트 발생시 실행되는 CanaISR함수에서 데이터 송신 횟수 파악용 카운터 변수(txMsgCount)를 증가시키고 데이터 송신 진행도를 트레이닝 키트 Red LED 8개로 표시합니다. 
4)CAN_setupMessageObject(	CANA_BASE, TX_MSG_OBJ_ID, 0x15555555,
						CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
						CAN_MSG_OBJ_TX_INT_ENABLE, MSG_DATA_LENGTH);에서 obejct id number와 msg id를 매핑합니ㅏㄷ. 
message identifier: CAN 메시지의 고유 ID입니다. 실제 CAN 버스를 통해 전송되는 프레임의 **ID 필드 (11-bit or 29-bit)**에 해당합니다.->0x15555555
obejct id number: TI의 CAN 모듈 내부에 존재하는 메시지 객체 번호입니다. F28377D의 CAN 모듈은 최대 32개의 메시지 객체를 가질 수 있다.-> TX_MSG_OBJ_ID(1)

5) CAN통신 관련 인터럽트 종류 
CAN_INT_ERROR: 에러 인터럽트 (에러 발생 시)), 
CAN_INT_STATUS	: 상태 변화 인터럽트 (예: bus-off, warning, 송신 실패 횟수 증가, 수신 오버런 등) 
CAN_INT_IE0:메시지 송수신 이벤트 발생 시 발생하는 인터럽트 (IE0)

HW 구성: TR2837xD 트레이닝 키트+CAN 통신 트랜시버(TCAN1044V)--연결--CAN 통신 트랜시버+컴퓨터

*싱크웍스의 TR2837xD 트레이닝 키트를 대상으로 한 5_CAN_Transmit_Receive예제를 참고하였습니다.