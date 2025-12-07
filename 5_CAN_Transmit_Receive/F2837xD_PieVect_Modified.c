//###########################################################################
//
// FILE:   F2837xD_PieVect.c
//
// TITLE:  F2837xD Device PIE Vector Initialization Functions
//
//###########################################################################
//   $
// $Release Date:   $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

//
// Globals
//
const struct PIE_VECT_TABLE PieVectTableInit = {
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    PIE_RESERVED_ISR,	// Reserved
    NOTUSED_ISR,		// CPU Timer 1 Interrupt
    NOTUSED_ISR,		// CPU Timer 2 Interrupt
    NOTUSED_ISR,		// Data logging Interrupt
    NOTUSED_ISR,		// RTOS Interrupt
    NOTUSED_ISR,		// Emulation Interrupt
    NOTUSED_ISR,		// Non-Maskable Interrupt
    NOTUSED_ISR,		// Illegal Operation Trap
    NOTUSED_ISR,		// User Defined Trap 1
    NOTUSED_ISR,		// User Defined Trap 2
    NOTUSED_ISR,		// User Defined Trap 3
    NOTUSED_ISR,		// User Defined Trap 4
    NOTUSED_ISR,		// User Defined Trap 5
    NOTUSED_ISR,		// User Defined Trap 6
    NOTUSED_ISR,		// User Defined Trap 7
    NOTUSED_ISR,		// User Defined Trap 8
    NOTUSED_ISR,		// User Defined Trap 9
    NOTUSED_ISR,		// User Defined Trap 10
    NOTUSED_ISR,		// User Defined Trap 11
    NOTUSED_ISR,		// User Defined Trap 12
    NOTUSED_ISR,		// 1.1 - ADCA Interrupt 1
    NOTUSED_ISR,		// 1.2 - ADCB Interrupt 1
    NOTUSED_ISR,		// 1.3 - ADCC Interrupt 1
    NOTUSED_ISR,		// 1.4 - XINT1 Interrupt
    NOTUSED_ISR,		// 1.5 - XINT2 Interrupt
    NOTUSED_ISR,		// 1.6 - ADCD Interrupt 1
    NOTUSED_ISR,		// 1.7 - Timer 0 Interrupt
    NOTUSED_ISR,		// 1.8 - Standby and Halt Wakeup Interrupt
    NOTUSED_ISR,		// 2.1 - ePWM1 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.2 - ePWM2 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.3 - ePWM3 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.4 - ePWM4 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.5 - ePWM5 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.6 - ePWM6 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.7 - ePWM7 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.8 - ePWM8 Trip Zone Interrupt
    NOTUSED_ISR,		// 3.1 - ePWM1 Interrupt
    NOTUSED_ISR,		// 3.2 - ePWM2 Interrupt
    NOTUSED_ISR,		// 3.3 - ePWM3 Interrupt
    NOTUSED_ISR,		// 3.4 - ePWM4 Interrupt
    NOTUSED_ISR,		// 3.5 - ePWM5 Interrupt
    NOTUSED_ISR,		// 3.6 - ePWM6 Interrupt
    NOTUSED_ISR,		// 3.7 - ePWM7 Interrupt
    NOTUSED_ISR,		// 3.8 - ePWM8 Interrupt
    NOTUSED_ISR,		// 4.1 - eCAP1 Interrupt
    NOTUSED_ISR,		// 4.2 - eCAP2 Interrupt
    NOTUSED_ISR,		// 4.3 - eCAP3 Interrupt
    NOTUSED_ISR,		// 4.4 - eCAP4 Interrupt
    NOTUSED_ISR,		// 4.5 - eCAP5 Interrupt
    NOTUSED_ISR,		// 4.6 - eCAP6 Interrupt
    PIE_RESERVED_ISR,	// 4.7 - Reserved
    PIE_RESERVED_ISR,	// 4.8 - Reserved
    NOTUSED_ISR,		// 5.1 - eQEP1 Interrupt
    NOTUSED_ISR,		// 5.2 - eQEP2 Interrupt
    NOTUSED_ISR,		// 5.3 - eQEP3 Interrupt
    PIE_RESERVED_ISR,	// 5.4 - Reserved
    PIE_RESERVED_ISR,	// 5.5 - Reserved
    PIE_RESERVED_ISR,	// 5.6 - Reserved
    PIE_RESERVED_ISR,	// 5.7 - Reserved
    PIE_RESERVED_ISR,	// 5.8 - Reserved
    NOTUSED_ISR,		// 6.1 - SPIA Receive Interrupt
    NOTUSED_ISR,		// 6.2 - SPIA Transmit Interrupt
    NOTUSED_ISR,		// 6.3 - SPIB Receive Interrupt
    NOTUSED_ISR,		// 6.4 - SPIB Transmit Interrupt
    NOTUSED_ISR,		// 6.5 - McBSPA Receive Interrupt
    NOTUSED_ISR,		// 6.6 - McBSPA Transmit Interrupt
    NOTUSED_ISR,		// 6.7 - McBSPB Receive Interrupt
    NOTUSED_ISR,		// 6.8 - McBSPB Transmit Interrupt
    NOTUSED_ISR,		// 7.1 - DMA Channel 1 Interrupt
    NOTUSED_ISR,		// 7.2 - DMA Channel 2 Interrupt
    NOTUSED_ISR,		// 7.3 - DMA Channel 3 Interrupt
    NOTUSED_ISR,		// 7.4 - DMA Channel 4 Interrupt
    NOTUSED_ISR,		// 7.5 - DMA Channel 5 Interrupt
    NOTUSED_ISR,		// 7.6 - DMA Channel 6 Interrupt
    PIE_RESERVED_ISR,	// 7.7 - Reserved
    PIE_RESERVED_ISR,	// 7.8 - Reserved
    NOTUSED_ISR,		// 8.1 - I2CA Interrupt 1
    NOTUSED_ISR,		// 8.2 - I2CA Interrupt 2
    NOTUSED_ISR,		// 8.3 - I2CB Interrupt 1
    NOTUSED_ISR,		// 8.4 - I2CB Interrupt 2
    NOTUSED_ISR,		// 8.5 - SCIC Receive Interrupt
    NOTUSED_ISR,		// 8.6 - SCIC Transmit Interrupt
    NOTUSED_ISR,		// 8.7 - SCID Receive Interrupt
    NOTUSED_ISR,		// 8.8 - SCID Transmit Interrupt
    NOTUSED_ISR,		// 9.1 - SCIA Receive Interrupt
    NOTUSED_ISR,		// 9.2 - SCIA Transmit Interrupt
    NOTUSED_ISR,		// 9.3 - SCIB Receive Interrupt
    NOTUSED_ISR,		// 9.4 - SCIB Transmit Interrupt
    NOTUSED_ISR,		// 9.5 - CANA Interrupt 0
    NOTUSED_ISR,		// 9.6 - CANA Interrupt 1
    NOTUSED_ISR,		// 9.7 - CANB Interrupt 0
    NOTUSED_ISR,		// 9.8 - CANB Interrupt 1
    NOTUSED_ISR,		// 10.1 - ADCA Event Interrupt
    NOTUSED_ISR,		// 10.2 - ADCA Interrupt 2
    NOTUSED_ISR,		// 10.3 - ADCA Interrupt 3
    NOTUSED_ISR,		// 10.4 - ADCA Interrupt 4
    NOTUSED_ISR,		// 10.5 - ADCB Event Interrupt
    NOTUSED_ISR,		// 10.6 - ADCB Interrupt 2
    NOTUSED_ISR,		// 10.7 - ADCB Interrupt 3
    NOTUSED_ISR,		// 10.8 - ADCB Interrupt 4
    NOTUSED_ISR,		// 11.1 - CLA1 Interrupt 1
    NOTUSED_ISR,		// 11.2 - CLA1 Interrupt 2
    NOTUSED_ISR,		// 11.3 - CLA1 Interrupt 3
    NOTUSED_ISR,		// 11.4 - CLA1 Interrupt 4
    NOTUSED_ISR,		// 11.5 - CLA1 Interrupt 5
    NOTUSED_ISR,		// 11.6 - CLA1 Interrupt 6
    NOTUSED_ISR,		// 11.7 - CLA1 Interrupt 7
    NOTUSED_ISR,		// 11.8 - CLA1 Interrupt 8
    NOTUSED_ISR,		// 12.1 - XINT3 Interrupt
    NOTUSED_ISR,		// 12.2 - XINT4 Interrupt
    NOTUSED_ISR,		// 12.3 - XINT5 Interrupt
    PIE_RESERVED_ISR,	// 12.4 - Reserved
    PIE_RESERVED_ISR,	// 12.5 - Reserved
    NOTUSED_ISR,		// 12.6 - VCU Interrupt
    NOTUSED_ISR,		// 12.7 - FPU Overflow Interrupt
    NOTUSED_ISR,		// 12.8 - FPU Underflow Interrupt
    PIE_RESERVED_ISR,	// 1.9 - Reserved
    PIE_RESERVED_ISR,	// 1.10 - Reserved
    PIE_RESERVED_ISR,	// 1.11 - Reserved
    PIE_RESERVED_ISR,	// 1.12 - Reserved
    NOTUSED_ISR,		// 1.13 - IPC Interrupt 0
    NOTUSED_ISR,		// 1.14 - IPC Interrupt 1
    NOTUSED_ISR,		// 1.15 - IPC Interrupt 2
    NOTUSED_ISR,		// 1.16 - IPC Interrupt 3
    NOTUSED_ISR,		// 2.9 - ePWM9 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.10 - ePWM10 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.11 - ePWM11 Trip Zone Interrupt
    NOTUSED_ISR,		// 2.12 - ePWM12 Trip Zone Interrupt
    PIE_RESERVED_ISR,	// 2.13 - Reserved
    PIE_RESERVED_ISR,	// 2.14 - Reserved
    PIE_RESERVED_ISR,	// 2.15 - Reserved
    PIE_RESERVED_ISR,	// 2.16 - Reserved
    NOTUSED_ISR,		// 3.9 - ePWM9 Interrupt
    NOTUSED_ISR,		// 3.10 - ePWM10 Interrupt
    NOTUSED_ISR,		// 3.11 - ePWM11 Interrupt
    NOTUSED_ISR,		// 3.12 - ePWM12 Interrupt
    PIE_RESERVED_ISR,	// 3.13 - Reserved
    PIE_RESERVED_ISR,	// 3.14 - Reserved
    PIE_RESERVED_ISR,	// 3.15 - Reserved
    PIE_RESERVED_ISR,	// 3.16 - Reserved
    PIE_RESERVED_ISR,	// 4.9 - Reserved
    PIE_RESERVED_ISR,	// 4.10 - Reserved
    PIE_RESERVED_ISR,	// 4.11 - Reserved
    PIE_RESERVED_ISR,	// 4.12 - Reserved
    PIE_RESERVED_ISR,	// 4.13 - Reserved
    PIE_RESERVED_ISR,	// 4.14 - Reserved
    PIE_RESERVED_ISR,	// 4.15 - Reserved
    PIE_RESERVED_ISR,	// 4.16 - Reserved
    NOTUSED_ISR,		// 5.9 - SD1 Interrupt
    NOTUSED_ISR,		// 5.10 - SD2 Interrupt
    PIE_RESERVED_ISR,	// 5.11 - Reserved
    PIE_RESERVED_ISR,	// 5.12 - Reserved
    PIE_RESERVED_ISR,	// 5.13 - Reserved
    PIE_RESERVED_ISR,	// 5.14 - Reserved
    PIE_RESERVED_ISR,	// 5.15 - Reserved
    PIE_RESERVED_ISR,	// 5.16 - Reserved
    NOTUSED_ISR,		// 6.9 - SPIC Receive Interrupt
    NOTUSED_ISR,		// 6.10 - SPIC Transmit Interrupt
    PIE_RESERVED_ISR,	// 6.11 - Reserved
    PIE_RESERVED_ISR,	// 6.12 - Reserved
    PIE_RESERVED_ISR,	// 6.13 - Reserved
    PIE_RESERVED_ISR,	// 6.14 - Reserved
    PIE_RESERVED_ISR,	// 6.15 - Reserved
    PIE_RESERVED_ISR,	// 6.16 - Reserved
    PIE_RESERVED_ISR,	// 7.9 - Reserved
    PIE_RESERVED_ISR,	// 7.10 - Reserved
    PIE_RESERVED_ISR,	// 7.11 - Reserved
    PIE_RESERVED_ISR,	// 7.12 - Reserved
    PIE_RESERVED_ISR,	// 7.13 - Reserved
    PIE_RESERVED_ISR,	// 7.14 - Reserved
    PIE_RESERVED_ISR,	// 7.15 - Reserved
    PIE_RESERVED_ISR,	// 7.16 - Reserved
    PIE_RESERVED_ISR,	// 8.9 - Reserved
    PIE_RESERVED_ISR,	// 8.10 - Reserved
    PIE_RESERVED_ISR,	// 8.11 - Reserved
    PIE_RESERVED_ISR,	// 8.12 - Reserved
    PIE_RESERVED_ISR,	// 8.13 - Reserved
    PIE_RESERVED_ISR,	// 8.14 - Reserved
#ifdef CPU1    
    NOTUSED_ISR,		// 8.15 - uPPA Interrupt
    PIE_RESERVED_ISR,	// 8.16 - Reserved
#elif defined(CPU2)
    PIE_RESERVED_ISR,	// 8.15 - Reserved
    PIE_RESERVED_ISR,	// 8.16 - Reserved
#endif    
    PIE_RESERVED_ISR,	// 9.9 - Reserved
    PIE_RESERVED_ISR,	// 9.10 - Reserved
    PIE_RESERVED_ISR,	// 9.11 - Reserved
    PIE_RESERVED_ISR,	// 9.12 - Reserved
    PIE_RESERVED_ISR,	// 9.13 - Reserved
    PIE_RESERVED_ISR,	// 9.14 - Reserved
#ifdef CPU1    
    NOTUSED_ISR,		// 9.15 - USBA Interrupt
#elif defined(CPU2)
    PIE_RESERVED_ISR,	// 9.15 - Reserved
#endif    
    PIE_RESERVED_ISR,	// 9.16 - Reserved
    NOTUSED_ISR,		// 10.9 - ADCC Event Interrupt
    NOTUSED_ISR,		// 10.10 - ADCC Interrupt 2
    NOTUSED_ISR,		// 10.11 - ADCC Interrupt 3
    NOTUSED_ISR,		// 10.12 - ADCC Interrupt 4
    NOTUSED_ISR,		// 10.13 - ADCD Event Interrupt
    NOTUSED_ISR,		// 10.14 - ADCD Interrupt 2
    NOTUSED_ISR,		// 10.15 - ADCD Interrupt 3
    NOTUSED_ISR,		// 10.16 - ADCD Interrupt 4
    PIE_RESERVED_ISR,	// 11.9 - Reserved
    PIE_RESERVED_ISR,	// 11.10 - Reserved
    PIE_RESERVED_ISR,	// 11.11 - Reserved
    PIE_RESERVED_ISR,	// 11.12 - Reserved
    PIE_RESERVED_ISR,	// 11.13 - Reserved
    PIE_RESERVED_ISR,	// 11.14 - Reserved
    PIE_RESERVED_ISR,	// 11.15 - Reserved
    PIE_RESERVED_ISR,	// 11.16 - Reserved
    NOTUSED_ISR,		// 12.9 - EMIF Error Interrupt
    NOTUSED_ISR,		// 12.10 - RAM Correctable Error Interrupt
    NOTUSED_ISR,		// 12.11 - Flash Correctable Error Interrupt
    NOTUSED_ISR,		// 12.12 - RAM Access Violation Interrupt
    NOTUSED_ISR,		// 12.13 - System PLL Slip Interrupt
    NOTUSED_ISR,		// 12.14 - Auxiliary PLL Slip Interrupt
    NOTUSED_ISR,		// 12.15 - CLA Overflow Interrupt
    NOTUSED_ISR			// 12.16 - CLA Underflow Interrupt
};

//
// InitPieVectTable - This function initializes the PIE vector table to a
//                    known state and must be executed after boot time.
//
void InitPieVectTable(void)
{
    Uint16 i;
    Uint32 *Source = (void *) &PieVectTableInit;
    Uint32 *Dest = (void *) &PieVectTable;

    //
    // Do not write over first 3 32-bit locations (these locations are
    // initialized by Boot ROM with boot variables)
    //
    Source = Source + 3;
    Dest = Dest + 3;

    EALLOW;
    for(i = 0; i < 221; i++)
    {
    	*Dest++ = *Source++;
    }
    EDIS;

    //
    // Enable the PIE Vector Table
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
}

//
// End of file
//
