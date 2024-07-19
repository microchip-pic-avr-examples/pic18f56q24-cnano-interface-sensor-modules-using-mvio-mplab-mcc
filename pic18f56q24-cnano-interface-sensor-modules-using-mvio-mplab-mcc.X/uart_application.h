#ifndef XC_UART_INTERFACE_H
#define	XC_UART_INTERFACE_H

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
#define GPS_DATA_LENGTH         (250)                                               // Length of GPRMC data 
#define PROCESSDELAY            (2100)
#define CLEARBUFFER             (0x00)
#define DESTBUFFERLENGTH        (512)
#define DATAIDENTIFIERIDX       (18)                                                // Location of the bitfield to verify if the data received is valid or not
#define SRCBUFFERLENGTH         (5)
#define STRINGLENGTH            (5)
#define INITIALINDEX            (0)
#define NEWLINECHAR             '\n'
#define VALIDDATA               'A'
#define INVALIDDATA             'V'

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DECLARATION                       */
/*                                                                            */
/******************************************************************************/

/**
 * void UART_Application(void)
 * 
 * @brief API to run the UART application. It is used for communication with the GPS3 Click via 
 *        UART Communication protocol. It provides the GPS data in form of GPS NMEA sentences.
 *        Here the sentence format used is GPRMC(Recommended minimum specific GPS/Transit data).
 * 
 * @param None.
 * @return None.
 */
void UART_Application(void);

/**
 * void UserInterruptHandler(void)
 * 
 * @brief User defined interrupt handler to disable DMA.
 * 
 * @param None.
 * @return None.
 */
void UserInterruptHandler(void);

/**
 * void StringCompare(uint8_t *src, uint8_t *destBuffer, uint16_t srcLength, uint16_t destLength)
 * 
 * @brief API to compare the string to check if the string is matching the NMEA packet.
 * 
 * @param *src          - value of source buffer.
 *        *destBuffer   - value of destination buffer.
 *        srcBufLength  - length of source buffer.
 *        destBufLength - length of destination buffer.
 * 
 * @return True - if the string is matched.
 */
bool StringCompare(uint8_t *src, uint8_t *dest, uint16_t srcLength, uint16_t destLength);
#endif	/* XC_UART_INTERFACE_H */

