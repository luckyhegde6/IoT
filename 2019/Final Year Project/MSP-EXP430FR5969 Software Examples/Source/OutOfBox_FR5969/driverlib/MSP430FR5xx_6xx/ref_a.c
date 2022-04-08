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
// ref_a.c - Driver for the ref_a Module.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup ref_a_api
//! @{
//
//*****************************************************************************

#include "inc/hw_regaccess.h"
#include "inc/hw_memmap.h"

#ifdef __MSP430_HAS_REF_A__
#include "ref_a.h"

#include <assert.h>

//*****************************************************************************
//
//! \brief Sets the reference voltage for the voltage generator.
//!
//! This function sets the reference voltage generated by the voltage generator
//! to be used by other peripherals. This reference voltage will only be valid
//! while the REF module is in control. Please note, if the
//! REF_A_isRefGenBusy() returns REF_A_BUSY, this function will have no effect.
//!
//! \param baseAddress is the base address of the REF module.
//! \param referenceVoltageSelect is the desired voltage to generate for a
//!        reference voltage.
//!        Valid values are:
//!        - \b REF_A_VREF1_2V [Default]
//!        - \b REF_A_VREF2_0V
//!        - \b REF_A_VREF2_5V
//!        \n Modified bits are \b REFVSEL of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_setReferenceVoltage(uint32_t baseAddress,
                               uint8_t referenceVoltageSelect)
{
        assert(referenceVoltageSelect <= REF_A_VREF2_5V);

        HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFVSEL_3);
        HWREG8(baseAddress + OFS_REFCTL0_L) |= referenceVoltageSelect;
}

//*****************************************************************************
//
//! \brief Disables the internal temperature sensor to save power consumption.
//!
//! This function is used to turn off the internal temperature sensor to save
//! on power consumption. The temperature sensor is enabled by default. Please
//! note, that giving ADC12 module control over the REF module, the state of
//! the temperature sensor is dependent on the controls of the ADC12 module.
//! Please note, if the REF_A_isRefGenBusy() returns REF_A_BUSY, this function
//! will have no effect.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFTCOFF of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_disableTempSensor(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) |= REFTCOFF;
}

//*****************************************************************************
//
//! \brief Enables the internal temperature sensor.
//!
//! This function is used to turn on the internal temperature sensor to use by
//! other peripherals. The temperature sensor is enabled by default. Please
//! note, if the REF_A_isRefGenBusy() returns REF_A_BUSY, this function will
//! have no effect.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFTCOFF of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_enableTempSensor(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFTCOFF);
}

//*****************************************************************************
//
//! \brief Outputs the reference voltage to an output pin.
//!
//! This function is used to output the reference voltage being generated to an
//! output pin. Please note, the output pin is device specific. Please note,
//! that giving ADC12 module control over the REF module, the state of the
//! reference voltage as an output to a pin is dependent on the controls of the
//! ADC12 module. Please note, if the REF_A_isRefGenBusy() returns REF_A_BUSY,
//! this function will have no effect.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFOUT of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_enableReferenceVoltageOutput(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) |= REFOUT;
}

//*****************************************************************************
//
//! \brief Disables the reference voltage as an output to a pin.
//!
//! This function is used to disables the reference voltage being generated to
//! be given to an output pin. Please note, if the REF_A_isRefGenBusy() returns
//! REF_A_BUSY, this function will have no effect.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFOUT of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_disableReferenceVoltageOutput(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFOUT);
}

//*****************************************************************************
//
//! \brief Enables the reference voltage to be used by peripherals.
//!
//! This function is used to enable the generated reference voltage to be used
//! other peripherals or by an output pin, if enabled. Please note, that giving
//! ADC12 module control over the REF module, the state of the reference
//! voltage is dependent on the controls of the ADC12 module. Please note, if
//! the REF_A_isRefGenBusy() returns REF_A_BUSY, this function will have no
//! effect.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFON of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_enableReferenceVoltage(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) |= REFON;
}

//*****************************************************************************
//
//! \brief Disables the reference voltage.
//!
//! This function is used to disable the generated reference voltage. Please
//! note, if the REF_A_isRefGenBusy() returns REF_A_BUSY, this function will
//! have no effect.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFON of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_disableReferenceVoltage(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) &= ~(REFON);
}

//*****************************************************************************
//
//! \brief Returns the bandgap mode of the REF module.
//!
//! This function is used to return the bandgap mode of the REF module,
//! requested by the peripherals using the bandgap. If a peripheral requests
//! static mode, then the bandgap mode will be static for all modules, whereas
//! if all of the peripherals using the bandgap request sample mode, then that
//! will be the mode returned. Sample mode allows the bandgap to be active only
//! when necessary to save on power consumption, static mode requires the
//! bandgap to be active until no peripherals are using it anymore.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! \return One of the following:
//!         - \b REF_A_STATICMODE if the bandgap is operating in static mode
//!         - \b REF_A_SAMPLEMODE if the bandgap is operating in sample mode
//!         \n indicating the bandgap mode of the module
//
//*****************************************************************************
uint16_t REF_A_getBandgapMode(uint32_t baseAddress)
{
        return HWREG16((baseAddress) + OFS_REFCTL0) & BGMODE;
}

//*****************************************************************************
//
//! \brief Returns the active status of the bandgap in the REF module.
//!
//! This function is used to return the active status of the bandgap in the REF
//! module. If the bandgap is in use by a peripheral, then the status will be
//! seen as active.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! \return One of the following:
//!         - \b REF_A_ACTIVE if active
//!         - \b REF_A_INACTIVE if not active
//!         \n indicating the bandgap active status of the module
//
//*****************************************************************************
bool REF_A_isBandgapActive(uint32_t baseAddress)
{
        if (HWREG16((baseAddress) + OFS_REFCTL0) & REFBGACT)
                return REF_A_ACTIVE;
        else
                return REF_A_INACTIVE;
}

//*****************************************************************************
//
//! \brief Returns the busy status of the reference generator in the REF
//! module.
//!
//! This function is used to return the busy status of the reference generator
//! in the REF module. If the ref. generator is in use by a peripheral, then
//! the status will be seen as busy.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! \return One of the following:
//!         - \b REF_A_NOTBUSY if the reference generator is not being used
//!         - \b REF_A_BUSY if the reference generator is being used,
//!         disallowing changes to be made to the REF module controls
//!         \n indicating the reference generator busy status of the module
//
//*****************************************************************************
uint16_t REF_A_isRefGenBusy(uint32_t baseAddress)
{
        return HWREG16((baseAddress) + OFS_REFCTL0) & REFGENBUSY;
}

//*****************************************************************************
//
//! \brief Returns the active status of the reference generator in the REF
//! module.
//!
//! This function is used to return the active status of the reference
//! generator in the REF module. If the ref. generator is on and ready to use,
//! then the status will be seen as active.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! \return One of the following:
//!         - \b REF_A_ACTIVE if active
//!         - \b REF_A_INACTIVE if not active
//!         \n indicating the reference generator active status of the module
//
//*****************************************************************************
bool REF_A_isRefGenActive(uint32_t baseAddress)
{
        if (HWREG16((baseAddress) + OFS_REFCTL0) & REFGENACT)
                return REF_A_ACTIVE;
        else
                return REF_A_INACTIVE;
}

//*****************************************************************************
//
//! \brief Returns the busy status of the reference generator in the REF
//! module.
//!
//! This function is used to return the buys status of the buffered bandgap
//! voltage in the REF module. If the ref. generator is on and ready to use,
//! then the status will be seen as active.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! \return One of the following:
//!         - \b REF_A_NOTREADY if NOT ready to be used
//!         - \b REF_A_READY if ready to be used
//!         \n indicating the the busy status of the reference generator in the
//!         module
//
//*****************************************************************************
bool REF_A_getBufferedBandgapVoltageStatus(uint32_t baseAddress)
{
        if (HWREG16((baseAddress) + OFS_REFCTL0) & REFBGRDY)
                return REF_A_READY;
        else
                return REF_A_NOTREADY;
}

//*****************************************************************************
//
//! \brief Returns the busy status of the variable reference voltage in the REF
//! module.
//!
//! This function is used to return the busy status of the variable reference
//! voltage in the REF module. If the ref. generator is on and ready to use,
//! then the status will be seen as active.
//!
//! \param baseAddress is the base address of the REF module.
//!
//! \return One of the following:
//!         - \b REF_A_NOTREADY if NOT ready to be used
//!         - \b REF_A_READY if ready to be used
//!         \n indicating the the busy status of the variable reference voltage
//!         in the module
//
//*****************************************************************************
bool REF_A_getVariableReferenceVoltageStatus(uint32_t baseAddress)
{
        if (HWREG16((baseAddress) + OFS_REFCTL0) & REFGENRDY)
                return REF_A_READY;
        else
                return REF_A_NOTREADY;
}

//*****************************************************************************
//
//! \brief Enables the one-time trigger of the reference voltage.
//!
//! Triggers the one-time generation of the variable reference voltage. Once
//! the reference voltage request is set, this bit is cleared by hardware
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFGENOT of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_setReferenceVoltageOneTimeTrigger(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) |= REFGENOT;
}

//*****************************************************************************
//
//! \brief Enables the one-time trigger of the buffered bandgap voltage.
//!
//! Triggers the one-time generation of the buffered bandgap voltage. Once the
//! buffered bandgap voltage request is set, this bit is cleared by hardware
//!
//! \param baseAddress is the base address of the REF module.
//!
//! Modified bits are \b REFBGOT of \b REFCTL0 register.
//!
//! \return None
//
//*****************************************************************************
void REF_A_setBufferedBandgapVoltageOneTimeTrigger(uint32_t baseAddress)
{
        HWREG8(baseAddress + OFS_REFCTL0_L) |= REFBGOT;
}

#endif
//*****************************************************************************
//
//! Close the doxygen group for ref_a_api
//! @}
//
//*****************************************************************************
