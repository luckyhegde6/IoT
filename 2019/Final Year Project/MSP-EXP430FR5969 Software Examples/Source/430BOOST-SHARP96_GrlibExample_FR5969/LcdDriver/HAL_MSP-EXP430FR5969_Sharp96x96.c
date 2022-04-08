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
// HAL_MSP-EXP430FR5969_Sharp96x96.c
//
//*****************************************************************************
//
//! \addtogroup display_api
//! @{
//
//*****************************************************************************

#include "grlib.h"
#include "HAL_MSP-EXP430FR5969_Sharp96x96.h"
#include "../driverlibHeaders.h"
#include "inc/hw_memmap.h"



//*****************************************************************************
//
//! Initializes the display driver.
//!
//! This function initializes the Sharp96x96 display. This function
//! configures the GPIO pins used to control the LCD display when the basic
//! GPIO interface is in use. On exit, the LCD has been reset and is ready to
//! receive command and data writes.
//!
//! \return None.
//
//*****************************************************************************
void LCDInit(void)
{
    // Configure LCD_SCLK_PIN for SPI_CLK mode
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_SCLK_PORT,
                LCD_SCLK_PIN , LCD_SCLK_PIN_FUNCTION);

    // Configure LCD_MOSI_PIN for SPI_MOSI mode
    GPIO_setAsPeripheralModuleFunctionOutputPin(LCD_MOSI_PORT,
    		LCD_MOSI_PIN , LCD_MOSI_PIN_FUNCTION);

    // Provide power to LCD
	GPIO_setAsOutputPin(LCD_POWER_PORT,
	        LCD_POWER_PIN);
	
	GPIO_setOutputHighOnPin(LCD_POWER_PORT,
            LCD_POWER_PIN);
				
	// Turn on DISP
	GPIO_setAsOutputPin(LCD_DISP_PORT,
	        LCD_DISP_PIN);
	
	GPIO_setOutputHighOnPin(LCD_DISP_PORT,
            LCD_DISP_PIN);		
	
			
	// Configure LCD_SCS_PIN as output pin
    GPIO_setAsOutputPin(LCD_SCS_PORT,
    		LCD_SCS_PIN);
			
	ClearCS();


    EUSCI_B_SPI_masterInit(EUSCI_B0_BASE,
                    EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
                    8000000,
                    1000000,
                    EUSCI_B_SPI_MSB_FIRST,
                    EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,
                    EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW,
                    EUSCI_B_SPI_3PIN);

    EUSCI_B_SPI_enable(EUSCI_B0_BASE);

}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
