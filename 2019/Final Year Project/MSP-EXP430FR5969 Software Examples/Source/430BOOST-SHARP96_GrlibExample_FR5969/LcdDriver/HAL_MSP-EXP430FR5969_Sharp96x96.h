/* --COPYRIGHT--,BSD
 * Copyright (c) 2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

 //*****************************************************************************
//
// HAL_MSP-EXP430FR5969_Sharp96x96.h - Prototypes for the Sharp96x96 LCD display driver.
//									   There is no output from Sharp96x96 LCD.
//
//                 MSP430FR5969                    LCD Sharp96x96
//                -----------------             -----------------
//               |     UCB0CLK/P2.2|---------> |SCLK     EXTCOMIN|-- 0
//            /|\|                 |           |            	 |
//             | |    UCB0SIMO/P1.6|---------> |SI        EXTMODE|-- 0
//             --|RST              |           |              	 |
//               |             P2.4|---------> |SCS              |
//               |             	   |		   |         	     |
//               |             P4.3|---------> |DISP             |
//               |                 |		   |                 |
//               |                 | 	       |                 |
//               |                 |            -----------------
//
//*****************************************************************************


#ifndef __HAL_MSP-EXP430FR5969_SHARPLCD_H__
#define __HAL_MSP-EXP430FR5969_SHARPLCD_H__

//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************

// Ports from MSP430 connected to LCD
#define LCD_MOSI_PORT                       GPIO_PORT_P1
#define LCD_SCLK_PORT                       GPIO_PORT_P2
#define LCD_DISP_PORT                       GPIO_PORT_P4
#define LCD_POWER_PORT                      GPIO_PORT_P4
#define LCD_SCS_PORT	                    GPIO_PORT_P2


// Pins from MSP430 connected to LCD
#define LCD_MOSI_PIN                        GPIO_PIN6
#define LCD_MOSI_PIN_FUNCTION               GPIO_SECONDARY_MODULE_FUNCTION
#define LCD_SCLK_PIN                        GPIO_PIN2
#define LCD_SCLK_PIN_FUNCTION               GPIO_SECONDARY_MODULE_FUNCTION
#define LCD_POWER_PIN                       GPIO_PIN2
#define LCD_DISP_PIN                        GPIO_PIN3
#define LCD_SCS_PIN                         GPIO_PIN4

// LCD Screen Dimensions
#define LCD_VERTICAL_MAX                   96
#define LCD_HORIZONTAL_MAX                 96

// Non-volatile Memory used to store DisplayBuffer
#define NON_VOLATILE_MEMORY_BUFFER
#ifdef NON_VOLATILE_MEMORY_BUFFER
//#define USE_FLASH_BUFFER
#define NON_VOLATILE_MEMORY_ADDRESS			0xf400
#endif //NON_VOLATILE_MEMORY_BUFFER

//*****************************************************************************
//
// Clears CS line
//
// This macro allows to clear the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************

#define ClearCS()  GPIO_setOutputLowOnPin(LCD_SCS_PORT, LCD_SCS_PIN)

//*****************************************************************************
//
// Set CS line
//
// This macro allows to set the Chip Select (CS) line
//
// \return None
//
//*****************************************************************************

#define SetCS()    GPIO_setOutputHighOnPin(LCD_SCS_PORT, LCD_SCS_PIN)


//*****************************************************************************
//
// Waits until the SPI communication with the LCD is finished a command to
// the LCD Driver
//
// \param None
//
// \return None
//*****************************************************************************

#define WaitUntilLcdWriteFinished()                \
        while  (EUSCI_B_SPI_isBusy(EUSCI_B0_BASE))



//*****************************************************************************
//
// Writes command or data to the LCD Driver
//
// \param ucCmdData is the 8 or 16 bit command to send to the LCD driver
// Uses the SET_LCD_DATA macro
//
// \return None
//
//*****************************************************************************

#define WriteCmdData(ucCmdData)                    	                 \
        do                                         	                 \
        {                                                            \
			while (!EUSCI_B_SPI_getInterruptStatus(EUSCI_B0_BASE,    \
                    EUSCI_B_SPI_TRANSMIT_INTERRUPT));                \
            	EUSCI_B_SPI_transmitData(EUSCI_B0_BASE,ucCmdData);   \
        }                                                            \
        while(0)

//*****************************************************************************
//
// Prepare to write memory
//
// This macro unlocks flash memory controller and
// sets access right on flash controller
//
// \return None
//
//*****************************************************************************
#define PrepareMemoryWrite()					\
	__no_operation();

//*****************************************************************************
//
// Finish memory writing
//
// This macro removes access rights on flash controller and
// locks flash memory controller.
//
// \return None
//
//*****************************************************************************
#define FinishMemoryWrite()						\
	__no_operation();

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void LCDInit(void);
#endif // __HAL_MSP-EXP430FR5969_SHARPLCD_H__
