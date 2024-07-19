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
volatile uint8_t receivedData[RECDATA_LENGTH] = {};
volatile uint16_t finalDataSum = VARIABLE_INIT, finalDataAvg = VARIABLE_INIT;
uint8_t dataReadCycles = VARIABLE_INIT;
float finalResult = VARIABLE_INIT;

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DEFINITIONS                       */
/*                                                                            */
/******************************************************************************/
void SPI_Application(void)
{
    finalDataAvg = VARIABLE_RESET;
    
    printf("\n\t\r Wait for Data to be received and processed... \n\t\r");
            
    for(dataReadCycles = 0; dataReadCycles < NUMBER_OF_CYCLES; dataReadCycles++)
    {        
        // Initialize HOST Config and Pull the CS Pin Low
        SPI2_Open(HOST_CONFIG);
        SPI_CS_SetLow();
        
        // Receive the 4 bytes of data from the sensor (First 2 bytes of data are considered for calculations)
        SPI2_BufferRead(receivedData,REC_DATALENGTH);
        
        finalDataSum = VARIABLE_RESET;
        
        // Save the UV Raw data in a temporary register
        finalDataSum += Uint8ToUint16Converter(receivedData[UVDATA_MSB_INDEX], receivedData[UVDATA_LSB_INDEX]);                     
        finalDataSum = finalDataSum >> 1;
        
        // Add up the raw data for 10 cycles and accumulate in finalDataAvg  variable
        finalDataAvg  += finalDataSum;
        
        SPI2_Close();
        SPI_CS_SetHigh(); 
        __delay_ms(DATA_PROCESSTIME);
    }
    
    // Calculate the average data of 10 samples accumulated
    finalDataAvg /= NUMBER_OF_CYCLES;
    
    if((finalDataAvg > LOWER_THRESHOLD) && (finalDataAvg < UPPER_THRESHOLD))
    {
        finalResult = (float)finalDataAvg;
    }
    printf("\n\t\r UV CLICK OUTPUT VALUE IS = %.2f \n\t\r", finalResult);
    
}