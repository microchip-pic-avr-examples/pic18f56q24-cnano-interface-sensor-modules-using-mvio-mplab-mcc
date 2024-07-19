#ifndef I2C_APPLICATION_H_
#define	I2C_APPLICATION_H_

/******************************************************************************/
/*                                                                            */
/*                               HEADER FILES                                 */
/*                                                                            */
/******************************************************************************/
#include "application.h"

/******************************************************************************/
/*                                                                            */
/*                            USER DEFINED MACROS                             */
/*                                                                            */
/******************************************************************************/

// Generic Macros
#define CLIENT_ADDRESS        (0x44)                                                // I2C Client Address
#define WR_LENGTH             (2)                                                   // Length of commands for SHT Click
#define RD_LENGTH             (6)                                                   // Length of data received from SHT Click
#define TRANSMIT_DELAY_MS     (500)                                                 // Delay for I2C to process
#define MSB_SHIFT             (8)                                                   // Shifting the uint8 data from LSB to MSB
#define START_INDEX           (0)
#define CLEAR                 (0)                                                   // Reset the value of the variables

// I2C Communication Macros
#define I2C_Open()            do { I2C1CON0bits.EN = 1; } while(0)
#define I2C_Close()           do { I2C1CON0bits.EN = 0; } while(0)

// Sensor Data Macros
#define HUM_CONV_FACTOR       (0.001525)                                            // Relative Humidity = 100*(RawData/(2^16 - 1))
#define TEMP_CONV_FACTOR      (0.002670)                                            // Relative Temperature = 175*(RawData/(2^16 - 1)) - TEMP_COMPENSATION
#define TEMP_COMPENSATION     (45)                                                  // Compensation to convert temperature to Celcius
#define HUMIDITY_MSB_INDEX    (3)                                                   // MSB Bytes of Humidity Data
#define HUMIDITY_LSB_INDEX    (4)                                                   // LSB Bytes of Humidity Data
#define TEMPERATURE_MSB_INDEX (0)                                                   // MSB Bytes of Temperature Data
#define TEMPERATURE_LSB_INDEX (1)                                                   // LSB Bytes of Temperature Data

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DECLARATION                       */
/*                                                                            */
/******************************************************************************/

/**
 * void I2C_Application(void)
 * 
 * @brief API to run the I2C application. It is used for communication with the SHT Click 
 *        via I2C Communication protocol. It provides the relative humidity and temperature
 *        which is printed on the terminal window.
 * 
 * @param None.
 * @return None.
 */
void I2C_Application(void);

/**
 * void I2C_ClearCommand(void)
 * 
 * @brief API to send command to clear the status register.
 * 
 * @param None.
 * @return None.
 */
void I2C_ClearCommand(void);

/**
 * void I2C_CalibrateMeasurement(void)
 * 
 * @brief API to send measurement commands for periodic data acquisition mode for 
 *        setting the  repeatability mps - measurement per second.
 * 
 * @param None.
 * @return None.
 */
void I2C_CalibrateMeasurement(void);

/**
 * uint16_t Uint8ToUint16Converter(uint8_t msbData, uint8_t lsbData)
 * 
 * @brief API to convert raw relative humidity or temperature data to user understandable data.
 * 
 * @param msbData - MSB of raw data.
 *        lsbData - LSB of raw data.
 * @return calculated combined relative humidity or temperature data.
 */
uint16_t Uint8ToUint16Converter(uint8_t msbData, uint8_t lsbData);

#endif /* I2C_APPLICATION_H_ */