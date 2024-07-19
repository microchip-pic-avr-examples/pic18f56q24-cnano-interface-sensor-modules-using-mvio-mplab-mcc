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
uint8_t calibrateCommand[2] = {0x24, 0x00};
uint8_t clearCommand[2] = {0x30, 0x41};

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DEFINITIONS                       */
/*                                                                            */
/******************************************************************************/
void I2C_Application(void)
{
    uint16_t relativeHumidityValue = VARIABLE_INIT, relativeTemperatureValue = VARIABLE_INIT;
    uint8_t receiveData[RD_LENGTH] = {};
    bool dataValidityFlag;
    
    printf("\n\t\r Wait for Data to be received and processed... \n\t\r");
    
    __delay_ms(TRANSMIT_DELAY_MS);
    I2C_ClearCommand();
    __delay_ms(TRANSMIT_DELAY_MS);
    I2C_CalibrateMeasurement();
    __delay_ms(TRANSMIT_DELAY_MS);
    
    // Check if the sensor is connected
    dataValidityFlag = I2C1_Read(CLIENT_ADDRESS, receiveData, RD_LENGTH);
    __delay_ms(TRANSMIT_DELAY_MS);
    
    // If sensor is connected read the valid data
    if(receiveData[START_INDEX] != NULL)
    {
        relativeHumidityValue = Uint8ToUint16Converter(receiveData[HUMIDITY_MSB_INDEX], receiveData[HUMIDITY_LSB_INDEX]);
        relativeHumidityValue = (uint16_t)(HUM_CONV_FACTOR * (float)relativeHumidityValue);
    
        relativeTemperatureValue = Uint8ToUint16Converter(receiveData[TEMPERATURE_MSB_INDEX], receiveData[TEMPERATURE_LSB_INDEX]);
        relativeTemperatureValue = (uint16_t)((TEMP_CONV_FACTOR * (float)relativeTemperatureValue) - TEMP_COMPENSATION);
    
        printf("\n\t\r Value of relative temperature is: %d°C", relativeTemperatureValue);
        printf("\n\t\r Value of relative humidity is: %d%% \n\t\r", relativeHumidityValue);
    }
    
    // If the sensor is not connected
    else
    {
        printf("\n\t\r SENSOR NOT AVAILABLE... PLEASE CONNECT THE SENSOR...!!! \n\t\r");
    }
}

void I2C_ClearCommand(void)
{
    I2C1_Write(CLIENT_ADDRESS, clearCommand, WR_LENGTH);
}

void I2C_CalibrateMeasurement(void)
{
    I2C1_Write(CLIENT_ADDRESS, calibrateCommand, WR_LENGTH);
}

uint16_t Uint8ToUint16Converter(uint8_t msbData, uint8_t lsbData)
{
    uint16_t rawData = VARIABLE_INIT;
    
    rawData = (((rawData + msbData) << MSB_SHIFT) + (rawData + lsbData));
    
    return rawData;
}