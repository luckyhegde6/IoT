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
//aes.c - Driver for the AES Module.
//
//*****************************************************************************
#include "inc/hw_regaccess.h"
#include "assert.h"
#include "aes256.h"
#ifdef  __IAR_SYSTEMS_ICC__
#include "deprecated/IAR/msp430xgeneric.h"
#else
#include "deprecated/CCS/msp430xgeneric.h"
#endif

//*****************************************************************************
//
//! Loads a 128, 192 or 256 bit cipher key to AES256 module.
//!
//! \param baseAddress is the base address of the AES module.
//! \param CipherKey is a pointer to an uint8_t array with a length of 16
//!      bytes that contains a 128 bit cipher key.
//! \param keyLength is the length of the key. Valid values are 
//!		\b AES256_KEYLENGTH_128BIT, \b AES256_KEYLENGTH_192BIT 
//!		\b AES256_KEYLENGTH_256BIT
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_setCipherKey (uint32_t baseAddress, 
	const uint8_t * CipherKey, 
	uint16_t keyLength)
{
	uint8_t i;
	uint16_t sCipherKey;

	HWREG16(baseAddress + OFS_AESACTL0) &= (~(AESKL_1 + AESKL_2));

	switch(keyLength)
	{
		case AES256_KEYLENGTH_128BIT :
			HWREG16(baseAddress + OFS_AESACTL0) |= AESKL__128;
			break;

		case AES256_KEYLENGTH_192BIT :
			HWREG16(baseAddress + OFS_AESACTL0) |= AESKL__192;
			break;

		case AES256_KEYLENGTH_256BIT :
			HWREG16(baseAddress + OFS_AESACTL0) |= AESKL__256;
			break;

		default :
			return STATUS_FAIL;
		}

		keyLength = keyLength / 8;

		for (i = 0; i < keyLength; i = i + 2)
		{
			sCipherKey = (uint16_t)(CipherKey[i]);
			sCipherKey = sCipherKey | ((uint16_t)(CipherKey[i + 1]) << 8);
			HWREG16(baseAddress + OFS_AESAKEY) = sCipherKey;
		}

	    // Wait until key is written
            while(0x00 == (HWREG16(baseAddress + OFS_AESASTAT) & AESKEYWR ));
	    return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Encrypts a block of data using the AES module.
//! The cipher key that is used for encryption should be loaded in advance
//! by using function \param AES256_setCipherKey().
//!
//! \param baseAddress is the base address of the AES module.
//! \param Data is a pointer to an uint8_t array with a length of 16
//!      bytes that contains data to be encrypted.
//! \param encryptedData is a pointer to an uint8_t array with a length
//!      of 16 bytes in that the encrypted data will be written.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_encryptData (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * encryptedData)
{
	uint8_t i;
	uint16_t tempData = 0;
	uint16_t tempVariable = 0;
	
	// Set module to encrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) &= ~AESOP_3;
	
			
	// Write data to encrypt to module
	for (i = 0; i < 16; i = i + 2)
	{
		tempVariable = (uint16_t)(Data[i]);
		tempVariable = tempVariable | ((uint16_t)(Data[i+1]) << 8);
		HWREG16(baseAddress + OFS_AESADIN) = tempVariable;
	}
	
	// Key that is already written shall be used
	// Encryption is initialized by setting AESKEYWR to 1
	HWREG16(baseAddress + OFS_AESASTAT) |= AESKEYWR;

	// Wait unit finished ~167 MCLK
	while(AESBUSY == (HWREG16(baseAddress + OFS_AESASTAT) & AESBUSY) );
	
	// Write encrypted data back to variable
	for (i = 0; i < 16; i = i + 2)
	{
		tempData = HWREG16(baseAddress + OFS_AESADOUT);
		*(encryptedData + i) = (uint8_t)tempData;
		*(encryptedData +i + 1) = (uint8_t)(tempData >> 8);


	}
	
    return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Decryptes a block of data using the AES module.
//! This function can be used to decrypt data by using the same key as used
//! for a previous performed encryption.
//! The decryption takes 214 MCLK.
//!
//! \param baseAddress is the base address of the AES module.
//! \param Data is a pointer to an uint8_t array with a length of 16
//!      bytes that contains encrypted data to be decrypted.
//! \param decryptedData is a pointer to an uint8_t array with a length
//!      of 16 bytes in that the decrypted data will be written.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_decryptDataUsingEncryptionKey (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * decryptedData)
{
	uint8_t i;
	uint16_t tempData = 0;
	uint16_t tempVariable = 0;
	
	// Set module to decrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) &= ~(AESOP1);
	HWREG16(baseAddress + OFS_AESACTL0) |= AESOP0;
	
	// Write data to decrypt to module
	for (i = 0; i < 16; i = i + 2)
	{
		tempVariable = (uint16_t)(Data[i+1]  << 8);
		tempVariable = tempVariable | ((uint16_t)(Data[i]));
		HWREG16(baseAddress + OFS_AESADIN) = tempVariable;
	}

	// Key that is already written shall be used
	// Now decryption starts
	HWREG16(baseAddress + OFS_AESASTAT) |= AESKEYWR;

	// Wait unit finished ~214 MCLK
	while(AESBUSY == (HWREG16(baseAddress + OFS_AESASTAT) & AESBUSY) );
	
	// Write encrypted data back to variable
	for (i = 0; i < 16; i = i + 2)
	{
		tempData = HWREG16(baseAddress + OFS_AESADOUT);
		*(decryptedData + i) = (uint8_t)tempData;
		*(decryptedData +i + 1) = (uint8_t)(tempData >> 8);
	}
	
	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Decryptes a block of data using the AES module.
//! This function requires a pregenerated decryption key. A key can be loaded
//! and pregenerated by using function \param AES256_generateFirstRoundKey() .
//! The decryption takes 167 MCLK.
//!
//! \param baseAddress is the base address of the AES module.
//! \param Data is a pointer to an uint8_t array with a length of 16
//!      bytes that contains encrypted data to be decrypted.
//! \param decryptedData is a pointer to an uint8_t array with a length
//!      of 16 bytes in that the decrypted data will be written.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_decryptData (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * decryptedData)
{
	uint8_t i;
	uint16_t tempData = 0;
	uint16_t tempVariable = 0;
	
	// Set module to decrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) |= (AESOP_3);
		
	// Write data to decrypt to module
	for (i = 0; i < 16; i = i + 2)
	{
		tempVariable = (uint16_t)(Data[i+1]  << 8);
		tempVariable = tempVariable | ((uint16_t)(Data[i]));
		HWREG16(baseAddress + OFS_AESADIN) = tempVariable;
	}
	
	// Key that is already written shall be used
	// Now decryption starts
	HWREG16(baseAddress + OFS_AESASTAT) |= AESKEYWR;

	// Wait unit finished ~167 MCLK
	while(AESBUSY == (HWREG16(baseAddress + OFS_AESASTAT) & AESBUSY ));
	
	// Write encrypted data back to variable
	for (i = 0; i < 16; i = i + 2)
	{
		tempData = HWREG16(baseAddress + OFS_AESADOUT);
		*(decryptedData + i) = (uint8_t)tempData;
		*(decryptedData +i + 1) = (uint8_t)(tempData >> 8);
	}
	
	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Loads and generates first round key required for decryption
//!
//! \param baseAddress is the base address of the AES module.
//! \param CipherKey is a pointer to an uint8_t array with a length of 16
//!      bytes that contains the initial AES key.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_generateFirstRoundKey (uint32_t baseAddress,
	const uint8_t * CipherKey)
{
	uint8_t i;
	uint16_t tempVariable = 0;
	uint16_t keyLength = 0;
	
	// Set module to decrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) &= ~(AESOP0);
	HWREG16(baseAddress + OFS_AESACTL0) |= AESOP1;
	
	switch((HWREG16(baseAddress + OFS_AESACTL0)) & (AESKL0_L + AESKL1_L))
	{
		case AESKL__128 :
			keyLength = AES256_KEYLENGTH_128BIT;
			break;

		case AESKL__192 :
			keyLength = AES256_KEYLENGTH_192BIT;
			break;

		case AESKL__256 :
			keyLength = AES256_KEYLENGTH_256BIT;
			break;

		default :
			return STATUS_FAIL;
	}

	keyLength = keyLength / 8;
	
	
	// Write cipher key to key register
	for (i = 0; i < keyLength; i = i + 2)
	{
		tempVariable = (uint16_t)(CipherKey[i]);
		tempVariable = tempVariable | ((uint16_t)(CipherKey[i + 1]) << 8);
		HWREG16(baseAddress + OFS_AESAKEY) = tempVariable;
	}
	
	// Wait until key is processed ~52 MCLK
	while((HWREG16(baseAddress + OFS_AESASTAT) & AESBUSY) == AESBUSY);
	
	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Clears the AES ready interrupt flag.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! Modified bit is \b AESRDYIFG of \b AESACTL0 register.
//!
//! \return None
//
//*****************************************************************************
void AES256_clearInterruptFlag (uint32_t baseAddress )
{
	HWREG16(baseAddress + OFS_AESACTL0) &=  ~AESRDYIFG;
}


//*****************************************************************************
//
//! Gets the AES ready interrupt flag status.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! \return uint32_t - AES256_READY_INTERRUPT or 0x00.
//
//*****************************************************************************
uint32_t AES256_getInterruptFlagStatus (uint32_t baseAddress)
{
    return ((HWREG16(baseAddress + OFS_AESACTL0) & AESRDYIFG) << 0x04);
}
//*****************************************************************************
//
//! Enables AES ready interrupt.
//!
//! \param baseAddress is the base address of the AES module.
//! Modified bit is \b AESRDYIE of \b AESACTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void AES256_enableInterrupt (uint32_t baseAddress)
{
	HWREG16(baseAddress + OFS_AESACTL0) |=  AESRDYIE;
}

//*****************************************************************************
//
//! Disables AES ready interrupt.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! Modified bit is \b AESRDYIE of \b AESACTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void AES256_disableInterrupt (uint32_t baseAddress)
{
	HWREG16(baseAddress + OFS_AESACTL0) &=  ~AESRDYIE;
}

//*****************************************************************************
//
//! Resets AES Module immediately.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! Modified bit is \b AESSWRST of \b AESACTL0 register.
//!
//! \return None.
//
//*****************************************************************************
void AES256_reset (uint32_t baseAddress)
{
	HWREG16(baseAddress + OFS_AESACTL0) |=  AESSWRST;
}

//*****************************************************************************
//
//! Starts an encryption process on the AES module.
//! The cipher key that is used for decryption should be loaded in advance
//! by using function \param AES256_setCipherKey().
//! This is the non-blocking equivalant of AES256_encryptData.
//!
//! \param baseAddress is the base address of the AES module.
//! \param Data is a pointer to an uint8_t array with a length of 16
//!      bytes that contains data to be encrypted.
//! \param encryptedData is a pointer to an uint8_t array with a length
//!      of 16 bytes in that the encrypted data will be written.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_startEncryptData (uint32_t baseAddress,
	const uint8_t * Data, 
	uint8_t * encryptedData)
{
	uint8_t i;
	uint16_t tempVariable = 0;
	
	// Set module to encrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) &= ~AESOP_3;
	

	// Write data to encrypt to module
	for (i = 0; i < 16; i = i + 2)
	{
		tempVariable = (uint16_t)(Data[i]);
		tempVariable = tempVariable | ((uint16_t)(Data[i+1 ]) << 8);
		HWREG16(baseAddress + OFS_AESADIN) = tempVariable;
	}
	
	// Key that is already written shall be used
	// Encryption is initialized by setting AESKEYWR to 1
	HWREG16(baseAddress + OFS_AESASTAT) |= AESKEYWR;

	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Starts an decryption process on the AES module.
//! This is the non-blocking equivalant of AES256_decryptDataUsingEncryptionKey.
//! This function can be used to decrypt data by using the same key as used
//! for a previous performed encryption.
//! The decryption takes 214 MCLK.
//!
//! \param baseAddress is the base address of the AES module.
//! \param Data is a pointer to an uint8_t array with a length of 16
//!      bytes that contains encrypted data to be decrypted.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_startDecryptDataUsingEncryptionKey (
	uint32_t baseAddress, 
	const uint8_t * Data)
{
	uint8_t i;
	uint16_t tempVariable = 0;
	
	// Set module to decrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) &= ~(AESOP1);
	HWREG16(baseAddress + OFS_AESACTL0) |= AESOP0;
	
	// Write data to decrypt to module
	for (i = 0; i < 16; i = i + 2)
	{
		tempVariable = (uint16_t)(Data[i+1]  << 8);
		tempVariable = tempVariable | ((uint16_t)(Data[i]));
		HWREG16(baseAddress + OFS_AESADIN) = tempVariable;
	}

	// Key that is already written shall be used
	// Now decryption starts
	HWREG16(baseAddress + OFS_AESASTAT) |= AESKEYWR;
	
	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Decryptes a block of data using the AES module.
//! This is the non-blocking equivalant of AES256_decryptData.
//! This function requires a pregenerated decryption key. A key can be loaded
//! and pregenerated by using function \param AES256_generateFirstRoundKey() .
//! The decryption takes 167 MCLK.
//!
//! \param baseAddress is the base address of the AES module.
//! \param Data is a pointer to an uint8_t array with a length of 16
//!      bytes that contains encrypted data to be decrypted.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_startDecryptData (uint32_t baseAddress,
	const uint8_t * Data)
{
	uint8_t i;
	uint16_t tempVariable = 0;
	
	// Set module to decrypt mode
	HWREG16(baseAddress + OFS_AESACTL0) |= (AESOP_3);

	// Write data to decrypt to module
	for (i = 0; i < 16; i = i + 2)
	{
		tempVariable = (uint16_t)(Data[i+1]  << 8);
		tempVariable = tempVariable | ((uint16_t)(Data[i]));
		HWREG16(baseAddress + OFS_AESADIN) = tempVariable;
	}
	
	// Key that is already written shall be used
	// Now decryption starts
	HWREG16(baseAddress + OFS_AESASTAT) |= AESKEYWR;


	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Loads and generates first round key required for decryption
//! This is the non-blocking equivalant of AES256_generateFirstRoundKey.
//!
//! \param baseAddress is the base address of the AES module.
//! \param CipherKey is a pointer to an uint8_t array with a length of 16
//!      bytes that contains the initial AES key.
//!
//! \return STATUS_SUCCESS
//
//*****************************************************************************
uint8_t AES256_startGenerateFirstRoundKey (uint32_t baseAddress,
	const uint8_t * CipherKey)
{
	uint8_t i;
	uint16_t tempVariable = 0;
	uint16_t keyLength = 0;
	
	// Set module to generate first round key required for decryption
	HWREG16(baseAddress + OFS_AESACTL0) &= ~(AESOP0);
	HWREG16(baseAddress + OFS_AESACTL0) |= AESOP1;
	
	switch((HWREG16(baseAddress + OFS_AESACTL0)) & (AESKL0_L + AESKL1_L))
	{
		case AESKL__128 :
			keyLength = AES256_KEYLENGTH_128BIT;
			break;

		case AESKL__192 :
			keyLength = AES256_KEYLENGTH_192BIT;
			break;

		case AESKL__256 :
			keyLength = AES256_KEYLENGTH_256BIT;
			break;

		default :
			return STATUS_FAIL;
	}

	keyLength = keyLength / 8;
	
	// Write cipher key to key register
	for (i = 0; i < keyLength; i = i + 2)
	{
		tempVariable = (uint16_t)(CipherKey[i]);
		tempVariable = tempVariable | ((uint16_t)(CipherKey[i+1]) << 8);
		HWREG16(baseAddress + OFS_AESAKEY) = tempVariable;
	}
	
	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Reads back the output data from AES module.
//! This function is meant to use after an encryption or decryption process
//! that was started and finished by initiating an interrupt.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! \return  is a pointer to an uint8_t array with a length of 16
//!      bytes in which the output data of the AES module is available.
//!		If AES module is busy returns NULL
//
//*****************************************************************************
uint8_t  AES256_getDataOut(uint32_t baseAddress,
							uint8_t *OutputData
							)
{
	uint8_t i;
	uint16_t tempData = 0;

	// If module is busy, exit and return failure
	if( AESBUSY == (HWREG16(baseAddress + OFS_AESASTAT) & AESBUSY)) 
		return STATUS_FAIL;
	
	// Write encrypted data back to variable
	for (i = 0; i < 16; i = i + 2)
	{
		tempData = HWREG16(baseAddress + OFS_AESADOUT);
		*(OutputData + i ) = (uint8_t)tempData;
		*(OutputData +i + 1) = (uint8_t)(tempData >> 8);
	}
	
	return STATUS_SUCCESS;
}

//*****************************************************************************
//
//! Gets the AES module busy status.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! \return uint8_t \b AES256_BUSY or \b AES256_NOT_BUSY
//
//*****************************************************************************
uint8_t AES256_isBusy (uint32_t baseAddress)
{
    return (HWREG16(baseAddress + OFS_AESASTAT) & AESBUSY);
}

//*****************************************************************************
//
//! Clears the AES error flag.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! Modified bit is \b AESERRFG of \b AESACTL0 register.
//!
//! \return None
//
//*****************************************************************************
void AES256_clearErrorFlag (uint32_t baseAddress )
{
	HWREG16(baseAddress + OFS_AESACTL0) &=  ~AESERRFG;
}

//*****************************************************************************
//
//! Gets the AES error flag status.
//!
//! \param baseAddress is the base address of the AES module.
//!
//! \return uint32_t - AES256_ERROR_OCCURRED or AES256_NO_ERROR.
//
//*****************************************************************************
uint32_t AES256_getErrorFlagStatus (uint32_t baseAddress)
{
    return (HWREG16(baseAddress + OFS_AESACTL0) & AESERRFG);
}
