/******************************************************************************/
/*                                                                            */
/*                               HEADER FILES                                 */
/*                                                                            */
/******************************************************************************/
#include "application.h"

/******************************************************************************/
/*                                                                            */
/*                           USER DEFINED VARIABLES                           */
/*                                                                            */
/******************************************************************************/
const uint8_t srcBuffer[SRCBUFFERLENGTH] = {'G','P','R','M','C'};
uint8_t* finalDataptr = NULL;
bool compareStatusFlag = false;

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DEFINITIONS                       */
/*                                                                            */
/******************************************************************************/
void UART_Application(void)
{    
    printf("\n\t\r Wait for Data to be received and processed... \n\t\r");
    
    // Clear the buffer before receiving the new set of data
    for(uint16_t i=0; i<DESTBUFFERLENGTH; i++)
    {
        destinationBuffer[i] = CLEARBUFFER;
    }

    // Enable DMA to accept the data from serial port & store in local buffer
    DMAnCON0bits.EN = 1;    
    
    DMA1_TransferWithTriggerStart();        
    __delay_ms(PROCESSDELAY);
    
    // Disable DMA
    DMAnCON0bits.EN = 0;
    
    // Verify if the received string is matching the source string
    compareStatusFlag = StringCompare(srcBuffer,destinationBuffer,SRCBUFFERLENGTH,DESTBUFFERLENGTH);    
    
    // Print the output if the comparison is true
    if(compareStatusFlag == true)
    {
        // Check if the received data is valid
        if(*(finalDataptr + DATAIDENTIFIERIDX) == VALIDDATA)
        {
            while(*finalDataptr != NEWLINECHAR)
            {
               printf("%c", *finalDataptr++);
            }
        }
        
        // Print the message if the received data is invalid
        if(*(finalDataptr+18 )== INVALIDDATA)
        {
            printf("\n\t\r GPS RECEIVER IS NOT IN THE RANGE OF ANTENNAS...");
            printf("\n\t\r PLEASE KEEP THE SENSOR IN OPEN TO AIR SPACE... \n\t\r");
        }
    }
    
    // If the sensor is not connected or not available
    else
    {
        printf("\n\t\r SENSOR NOT AVAILABLE... PLEASE CONNECT THE SENSOR...!!! \n\t\r");
    }
}

void UserInterruptHandler(void)
{
    DMAnCON0bits.EN = 0;
}

bool StringCompare(uint8_t* src, uint8_t* destBuffer, uint16_t srcLength, uint16_t destLength)
{
    uint16_t bufferindex = VARIABLE_RESET;
    uint16_t loopcount = VARIABLE_RESET;
    finalDataptr = destBuffer;
	
    while(loopcount <= destLength)
	{
        loopcount++;
        
        // Check if the characters are matching
		if(*src == *destBuffer)
		{			
			bufferindex++;
            src++;
		}
        else
        {
            src = &srcBuffer[INITIALINDEX];
            bufferindex = VARIABLE_RESET;
        }
		
        // Check if all the characters are matching as per source buffer
		if(bufferindex >= srcLength)
		{
		    finalDataptr = (destBuffer-STRINGLENGTH);
		    bufferindex = VARIABLE_RESET;
            loopcount = VARIABLE_RESET;
		    return true;
		}
        destBuffer++;
	}
    return false;
}