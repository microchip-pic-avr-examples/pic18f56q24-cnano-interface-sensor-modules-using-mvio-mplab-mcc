/**
  * SPI2 Generated Driver File
  *
  * @file spi2.c
  *
  * @ingroup spi2
  *
  * @brief This file contains the driver code for the SPI2 module.
  *
  * @version SPI2 Driver Version v3.1.0.
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <xc.h>
#include "../spi_interface.h"
#include "../spi2.h"
#include "../spi_polling_types.h"

/**
 * @ingroup spi2
 * @struct SPI_INTERFACE SPI2
 * @brief Defines an object for SPI_INTERFACE functions.
 */ 
 
const struct SPI_INTERFACE SPI2_Host = {
    .Initialize = SPI2_Initialize,
    .Deinitialize = SPI2_Deinitialize,
    .Open = SPI2_Open,
    .Close = SPI2_Close,
    .BufferExchange = SPI2_BufferExchange,
    .BufferWrite = SPI2_BufferWrite,
    .BufferRead = SPI2_BufferRead,	
    .ByteExchange = SPI2_ByteExchange,
    .ByteWrite = SPI2_ByteWrite,
    .ByteRead = SPI2_ByteRead,
    .IsTxReady = SPI2_IsTxReady,
    .IsRxReady = SPI2_IsRxReady,
    .RxCompleteCallbackRegister = NULL,
    .TxCompleteCallbackRegister = NULL
};

//con0 == SPI2CON0, con1 == SPI2CON1, con2 == SPI2CON2, baud == SPI2BAUD, clksel == SPI2CLKSEL
static const spi_configuration_t spi2_configuration[] = {   
    { 0x2, 0x40, 0x0, 0xf, 0x1 },
    { 0x2, 0x40, 0x0, 0x0, 0x0 }
};

void SPI2_Initialize(void)
{
    //Disable the interrupts
    PIE11bits.SPI2IE 		= 0U;
    PIE11bits.SPI2TXIE 	= 0U;
    PIE11bits.SPI2RXIE 	= 0U;
	
	//Clear all registers to reset value
    SPI2CON0 = 0x00U;
    SPI2CON1 = 0x00U;
    SPI2CON2 = 0x00U;
    SPI2BAUD = 0x00U;
    SPI2CLK = 0x00U;
}

void SPI2_Deinitialize(void)
{
    SPI2CON0bits.EN = 0U;
}

bool SPI2_Open(uint8_t spiConfigIndex)
{
	bool returnValue = false; 
	if(false == SPI2CON0bits.EN)
	{
        SPI2CON0 = spi2_configuration[spiConfigIndex].con0;
        SPI2CON1 = spi2_configuration[spiConfigIndex].con1;
        SPI2CON2 = spi2_configuration[spiConfigIndex].con2 & ~(_SPI2CON2_SPI2RXR_MASK) & ~(_SPI2CON2_SPI2TXR_MASK);
        SPI2BAUD = spi2_configuration[spiConfigIndex].baud;        
        SPI2CLK = spi2_configuration[spiConfigIndex].clksel;        
		TRISCbits.TRISC3 = 0;
        SPI2CON0bits.EN = 1U;
		
		returnValue = true;
	}
	else
	{
		returnValue = false;
	}
	return returnValue;
}

void SPI2_Close(void)
{
	SPI2CON0bits.EN = 0U;
}

void SPI2_BufferExchange(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

	//Load the transfer count register
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);	
	
	//Set both SPI as full duplex mode for buffer exchange operation
    SPI2CON2 = ((SPI2CON2) | (_SPI2CON2_SPI2RXR_MASK) | (_SPI2CON2_SPI2TXR_MASK));
	
	while(0U == SPI2INTFbits.TCZIF)
	{
		//Write input data to SPI transmit buffer register
		SPI2TXB = *bufferInput;
		while(!PIR11bits.SPI2RXIF)
		{
			//Wait on receive interrupt flag to be set
        };
		
		//Store received data  from receive buffer register 
		*bufferInput = SPI2RXB;		
		bufferInput++;
	}
	//Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;
}

void SPI2_BufferWrite(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

	//Load the transfer count register
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);

	//Set both SPI as transmit only mode for buffer write operation
    SPI2CON2 = (SPI2CON2 & ~(_SPI2CON2_SPI2RXR_MASK)) | (_SPI2CON2_SPI2TXR_MASK);
   
	while(0U == SPI2INTFbits.TCZIF)
	{
		//Write input data to SPI transmit buffer register
		SPI2TXB = *bufferInput;
		while(!PIR11bits.SPI2TXIF)
		{
			//Wait on transmit interrupt flag to be set
        };
		bufferInput++;
	}	
	//Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;
}

void SPI2_BufferRead(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;
	
	//Load the transfer count register
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);

	//Set both SPI as receive only mode for buffer read operation
    SPI2CON2 = (SPI2CON2 | (_SPI2CON2_SPI2RXR_MASK)) & ~(_SPI2CON2_SPI2TXR_MASK);
	while(0U == SPI2INTFbits.TCZIF)
	{
		//Write dummy data to SPI transmit buffer register
		SPI2TXB = 0x00U;
		while(!PIR11bits.SPI2RXIF)
		{
            //Wait on receive interrupt flag to be set
        };
		//Store received data  from receive buffer register 
		*bufferInput = SPI2RXB;
		bufferInput++;
	}
	//Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;
}

uint8_t SPI2_ByteExchange(uint8_t byteData)
{
    SPI2CON2 = SPI2CON2 | _SPI2CON2_SPI2RXR_MASK | _SPI2CON2_SPI2TXR_MASK;
    uint8_t returnValue = 0U;
	SPI2TCNTL = 1;
	//Write input data to SPI transmit buffer register
	SPI2TXB = byteData;
	while(!PIR11bits.SPI2RXIF)
	{
		//Wait on receive interrupt flag to be set
    };	
	
	//Store received data  from receive buffer register 
	returnValue = SPI2RXB;
	
	return returnValue;
}

void SPI2_ByteWrite(uint8_t byteData)
{	
	SPI2CON2 = SPI2CON2 | _SPI2CON2_SPI2RXR_MASK | _SPI2CON2_SPI2TXR_MASK;
	SPI2TCNTL = 1;
	//Write input data to SPI transmit buffer register
	SPI2TXB = byteData;
}

uint8_t SPI2_ByteRead(void)
{
	uint8_t returnValue = 0x00U;
    SPI2CON2 = SPI2CON2 | _SPI2CON2_SPI2RXR_MASK | _SPI2CON2_SPI2TXR_MASK;

	//Store received data  from receive buffer register 
	returnValue = SPI2RXB;	
	return returnValue;
}


bool SPI2_IsTxReady(void)
{
	bool returnValue = false;
	if(true == SPI2CON0bits.EN)
	{
		returnValue = PIR11bits.SPI2TXIF;
	}
	else 
	{
		returnValue = false;
	}
	return returnValue;
}

bool SPI2_IsRxReady(void)
{
	bool returnValue = false;
	
	if(true == SPI2CON0bits.EN)
    {
		returnValue = PIR11bits.SPI2RXIF;
    }
    else 
    {
        returnValue = false;
    }
    return returnValue;
}
