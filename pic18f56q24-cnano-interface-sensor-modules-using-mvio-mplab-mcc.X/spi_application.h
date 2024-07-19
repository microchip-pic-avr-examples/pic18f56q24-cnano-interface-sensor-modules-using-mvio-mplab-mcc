#ifndef XC_SPI_INTERFACE_H
#define	XC_SPI_INTERFACE_H

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
#define LOWER_THRESHOLD     (800)                                                   // Lower Threshold of UV operatable range
#define UPPER_THRESHOLD     (4096)                                                  // Upper Threshold of UV operatable range
#define RECDATA_LENGTH      (2)
#define REC_DATALENGTH      (4)                                                     // Length of data received from the UV sensor
#define VARIABLE_RESET      (0)                                                     // Re-initialize the variable to zero
#define VARIABLE_INIT       (0)
#define UVDATA_MSB_INDEX    (0)                                                     // MSB Byte of Raw UV Data
#define UVDATA_LSB_INDEX    (1)                                                     // LSB Byte of Raw UV Data
#define BYTE_SHIFT          (8)                                                     // Shift of byte position from LSB to MSB
#define NUMBER_OF_CYCLES    (10)                                                    // Number of cycles for capturing UV Data

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DECLARATION                       */
/*                                                                            */
/******************************************************************************/

/**
 * void SPI_Application(void)
 * 
 * @brief API to run the SPI application. It is used for communication with the UV Click via 
 *        SPI Communication protocol. It provides the raw UV data which is printed on the
 *        terminal window.
 * 
 * @param None.
 * @return None.
 */
void SPI_Application(void);

///**
// * uint16_t CalculateRawUVData(uint8_t msbData, uint8_t lsbData)
// * 
// * @brief API to convert raw relative humidity or temperature data to user understandable data.
// * 
// * @param msbData - MSB of raw data.
// *        lsbData - LSB of raw data.
// * @return calculated combined relative humidity or temperature data.
// */
//uint16_t CalculateRawUVData(uint8_t msbData, uint8_t lsbData);

#endif	/* XC_SPI_INTERFACE_H */